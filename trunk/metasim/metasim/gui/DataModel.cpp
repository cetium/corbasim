// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * DataModel.cpp
 * Copyright (C) Cátedra SAES-UMU 2011 <catedra-saes-umu@listas.um.es>
 *
 * METASIM is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * METASIM is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "DataModel.hpp"
#include <QStyle>
#include <QApplication>
#include <QDateTime>
#include <QMimeData>

#include <metasim/gui/qvariant.hpp>

//#include <metasim/json/reflective.hpp>

#include <metasim/core/reflective_fwd.hpp>

#include <iostream>
#include <sstream>

using namespace metasim::gui;

DataModel::DataModel(QObject * parent) :
    QAbstractItemModel(parent), m_instance(NULL)
{
    m_outputIcon = qApp->style()->standardIcon(QStyle::SP_ArrowLeft);

    setSupportedDragActions(Qt::CopyAction);
}

DataModel::~DataModel()
{
}

QMimeData * DataModel::mimeData(const QModelIndexList& indexes) const
{
#if 0
    if (indexes.size() == 2) // both columns
    {
        int pos = indexToPosition(indexes.at(0));

        std::ostringstream oss;

        const ModelEntry& entry = m_entries.at(pos);

        core::operation_reflective_base const * reflective = 
            entry.reflective;

        core::holder holder = reflective->get_holder(entry.req);

        json::write(oss, reflective, holder);

        QMimeData *mimeData = new QMimeData;
        mimeData->setText(oss.str().c_str());

        return mimeData;
    }
#endif
    return NULL;
}

int DataModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 2;
}

int DataModel::indexToPosition(const QModelIndex& index) const
{
    if (!index.isValid())
        return -1;

    QModelIndex parent = index;

    while (parent.parent().isValid())
        parent = parent.parent();

    return parent.row();
}

void DataModel::deletePosition(int pos)
{
    beginRemoveRows(QModelIndex(), pos, pos);

    m_entries.removeAt(pos);
    m_nodes.removeAt(pos);

    endRemoveRows();
}

namespace  
{
    QString getNodeName(Node const * node)
    {
        if (node->parent && node->parent->reflective->is_repeated())
        {
            return QString("[%1]").arg(node->index);
        }
        else if (node->parent && node->parent->reflective->get_type() ==
                metasim::core::TYPE_STRUCT)
        {
            return node->parent->reflective->get_child_name(
                    node->index);
        }

        return "Error!";
    }
} // namespace 

QVariant DataModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();
#if 0
    // Background
    if (role == Qt::BackgroundRole)
    {
        QModelIndex parent = index;
        while(parent.parent().isValid())
        {
            parent = parent.parent();
        }

        // std::cout << parent.row() << std::endl;
        const ModelEntry& entry = m_entries.at(parent.row());

        // return QVariant();
        return entry.color;
    }
    else 
#endif
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        Node * node = static_cast< Node * >(index.internalPointer());
        node->check_for_initialized();

        // First level item
        if (!index.parent().isValid())
        {
            // Value
            if (index.column())
                return QVariant();

            return m_entries[index.row()].text;
        }
        else
        {
            // Value
            if (index.column())
                return toQVariant(node->reflective, node->holder);

            // Name
            return getNodeName(node);
        }
    }

#if 0
    else if (!index.parent().isValid() && index.column() == 0
            && role == Qt::DecorationRole)
    {
        const ModelEntry& entry = m_entries.at(index.row());
        return *(entry.icon);
    }
#endif

    return QVariant();
}

bool DataModel::setData(const QModelIndex & index, 
        const QVariant& value, int role)
{
    Node * node = static_cast< Node * >(index.internalPointer());
    
    if (!node) return false;

    node->check_for_initialized();

    bool res = fromQVariant(node->reflective, node->holder, value);

    if (res)
    {
        emit dataChanged(index, index);
    }

    return res;
}

Qt::ItemFlags DataModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    // Value is editable by default
    if (index.column())
        return Qt::ItemIsEnabled 
            | Qt::ItemIsSelectable 
            | Qt::ItemIsEditable
            | Qt::ItemIsDragEnabled;

    return Qt::ItemIsEnabled | 
        Qt::ItemIsSelectable | 
        Qt::ItemIsDragEnabled;
}

QVariant DataModel::headerData(int section, 
        Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section)
        {
        case 0:
            return QString("Message");
        case 1:
            return QString("Value");
        default:
            break;
        }
    }

    return QVariant();
}

QModelIndex DataModel::index(int row, int column, 
        const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (!parent.isValid())
    {
        return createIndex(row, column, (void *) m_nodes[row].get());
    }

    Node * node = static_cast< Node * >(parent.internalPointer());
    node->check_for_initialized();

    if (row < (int) node->children.size())
    {
        return createIndex(row, column, 
                (void *) node->children[row].get());
    }

    return QModelIndex();
}

QModelIndex DataModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    Node * node = static_cast< Node * >(index.internalPointer());

    if (!node || !node->parent)
        return QModelIndex();

    // parent is first level item
    if (!node->parent->parent)
    {
        // index could be changed
        int row = 0;
        bool found = false;

        for (; row < m_nodes.size() && !found; row++) 
            if (m_nodes.at(row).get() == node->parent)
                return createIndex(row, 0, (void *) node->parent);

        return QModelIndex();
    }

    return createIndex(node->index, 0, (void *) node->parent);
}

int DataModel::rowCount(const QModelIndex &parent) const
{
    /**
     * Los hijos son de la columna cero.
     */
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        return m_entries.size();

    Node * node = static_cast< Node * >(parent.internalPointer());
    node->check_for_initialized();

    return node->children.size();
}

metasim::event::request_ptr DataModel::getRequest(int pos)
{
    return m_entries.at(pos).req;
}

void DataModel::initialize(core::interface_reflective_base const * instance)
{
    m_instance = instance;
}

void DataModel::clearLog()
{
    beginResetModel();
    reset();
    resetInternalData();
    endResetModel();
}

void DataModel::resetInternalData()
{
    m_entries.clear();
    m_nodes.clear();
}

void DataModel::addEntry(metasim::core::reflective_base const * reflective;
	metasim::core::holder holder, int pos)
{
    if (pos == -1)
        pos = m_entries.size();

    ModelEntry entry;

    entry.reflective = reflective;

    beginInsertRows(QModelIndex(), pos, pos);

    Node_ptr node(new Node(op, holder));
    m_nodes.insert(pos, node);

    // List
    entry.req = req;

    // entry.text = QString("Outgoing call ") + op->get_name();

    m_entries.insert(pos, entry);

    endInsertRows();
}

