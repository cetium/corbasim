// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * FilteredLogView.hpp
 * Copyright (C) Cátedra SAES-UMU 2011 <catedra-saes-umu@listas.um.es>
 *
 * CORBASIM is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CORBASIM is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CORBASIM_REFLECTIVE_GUI_FILTEREDLOGVIEW_HPP
#define CORBASIM_REFLECTIVE_GUI_FILTEREDLOGVIEW_HPP

#include <QWidget>
#include <corbasim/qt/FilterModel.hpp>
#include <corbasim/reflective_gui/LogModel.hpp>

namespace corbasim 
{
namespace reflective_gui 
{

class FilteredLogView : public QWidget
{
    Q_OBJECT
public:
    FilteredLogView(QWidget * parent = 0);
    virtual ~FilteredLogView();

    void save(QVariant& settings);
    void load(const QVariant& settings);

public slots:

    void registerInstance(const QString& name,
            const corbasim::core::interface_reflective_base * reflective);

    void unregisterInstance(const QString& name);
  
    void setLogModel(QAbstractItemModel * model);

protected:
    qt::FilterModel m_filterModel;
    FilteredLogModel m_model;

};

} // namespace reflective_gui
} // namespace corbasim

#endif /* CORBASIM_REFLECTIVE_GUI_FILTEREDLOGVIEW_HPP */

