// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * InstanceModel.hpp
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

#ifndef METASIM_GUI_INSTANCEMODEL_HPP
#define METASIM_GUI_INSTANCEMODEL_HPP

#include <QObject>
#include <metasim/gui/export.hpp>
#include <metasim/core/reflective_fwd.hpp>

namespace metasim 
{
namespace gui 
{

class METASIM_GUI_DECLSPEC InstanceModel : public QObject
{
    Q_OBJECT
public:
    InstanceModel(QObject * parent = 0);
    virtual ~InstanceModel();

    const QList< metasim::core::instance_ptr >& getInstances() const;

public slots:

    void addInstance(metasim::core::instance_ptr);
    void removeInstance(metasim::core::instance_ptr);

signals:
    
    void addedInstance(metasim::core::instance_ptr);
    void removedInstance(metasim::core::instance_ptr);

protected:

    QList< metasim::core::instance_ptr > m_instances;
};

} // namespace gui
} // namespace metasim

#endif /* METASIM_GUI_INSTANCEMODEL_HPP */

