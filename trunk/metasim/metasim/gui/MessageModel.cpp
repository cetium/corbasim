// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * MessageModel.cpp
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

#include "MessageModel.hpp"
#include <QStyle>
#include <QApplication>
#include <QDateTime>
#include <QMimeData>

#include <metasim/gui/qvariant.hpp>

#include <metasim/json/reflective.hpp>

#include <metasim/core/reflective_fwd.hpp>

#include <iostream>
#include <sstream>

using namespace metasim::gui;

MessageModel::MessageModel(QObject * parent) :
    QAbstractItemModel(parent), m_model(NULL)
{
}

MessageModel::~MessageModel()
{
}

int MessageModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 1;
}

QVariant MessageModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || !m_model)
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        // TODO
    }

    return QVariant();
}

Qt::ItemFlags MessageModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    // Value is editable by default
    if (index.column())
        return Qt::ItemIsEnabled 
            | Qt::ItemIsSelectable;

    return Qt::ItemIsEnabled | 
        Qt::ItemIsSelectable;
}

QVariant MessageModel::headerData(int section, 
        Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return QString("Instance");
    }

    return QVariant();
}

QModelIndex MessageModel::index(int row, int column, 
        const QModelIndex &parent) const
{
#if 0
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
#endif
}

QModelIndex MessageModel::parent(const QModelIndex &index) const
{
#if 0
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
#endif
}

int MessageModel::rowCount(const QModelIndex &parent) const
{
    /**
     * Los hijos son de la columna cero.
     */
    if (parent.column() > 0 || !m_model)
        return 0;

    if (!parent.isValid())
        return m_model->getInstances().size();

    if (!parent.parent().isValid())
    {
        metasim::core::instance_ptr instance = 
            m_model->getInstances().at(parent.row());

        return instance->get_reflective()->get_reflective_count();
    }

    return 0;
}

void MessageModel::setSourceModel(InstanceModel * m)
{
    beginResetModel();

    if (m_model)
    {
        QObject::disconnect(m_model, 
                SIGNAL(addedInstance(metasim::core::instance_ptr)),
                this,
                SLOT(addedInstance(metasim::core::instance_ptr)));

        QObject::disconnect(m_model, 
                SIGNAL(removedInstance(metasim::core::instance_ptr)),
                this,
                SLOT(removedInstance(metasim::core::instance_ptr)));
    }

    m_model = m;

    if (m_model)
    {
        QObject::connect(m_model, 
                SIGNAL(addedInstance(metasim::core::instance_ptr)),
                this,
                SLOT(addedInstance(metasim::core::instance_ptr)));

        QObject::connect(m_model, 
                SIGNAL(removedInstance(metasim::core::instance_ptr)),
                this,
                SLOT(removedInstance(metasim::core::instance_ptr)));
    }

    endResetModel();
}

void MessageModel::addedInstance(metasim::core::instance_ptr i)
{
}

void MessageModel::removedInstance(metasim::core::instance_ptr i)
{
}

