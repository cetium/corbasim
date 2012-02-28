// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * DataModel.hpp
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

#ifndef METASIM_GUI_SCRIPTMODEL_HPP
#define METASIM_GUI_SCRIPTMODEL_HPP

#include <QAbstractItemModel>

#include <metasim/gui/export.hpp>
#include <metasim/core/reflective_fwd.hpp>
#include <metasim/gui/types.hpp>
#include <metasim/gui/ModelNode.hpp>

namespace metasim 
{
namespace gui
{

class METASIM_GUI_DECLSPEC DataModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    DataModel(QObject * parent = 0);
    virtual ~DataModel();

    QVariant data(const QModelIndex& index, 
            int role = Qt::DisplayRole) const; 
    bool setData(const QModelIndex & index, 
            const QVariant& value, int role = Qt::EditRole);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QMimeData *	mimeData(const QModelIndexList& indexes) const;

    int indexToPosition(const QModelIndex& index) const;

    void deletePosition(int pos);

    struct ModelEntry
    {
        QString text;
        core::reflective_base const * reflective;
        core::holder holder;
    };

public slots:

    void clearModel();

    void addEntry(metasim::core::reflective_base const * reflective,
        metasim::core::holder holder, int pos = -1);

private slots:

    void resetInternalData();

protected:

    QList< ModelEntry > m_entries;
    QList< Node_ptr > m_nodes;
};

} // namespace gui
} // namespace metasim

#endif /* METASIM_GUI_SCRIPTMODEL_HPP */

