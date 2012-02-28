// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * InstanceModel.cpp
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

#include "InstanceModel.hpp"

using namespace metasim::gui;

InstanceModel::InstanceModel(QObject * parent) :
    QObject(parent)
{
}

InstanceModel::~InstanceModel()
{
}

const QList< metasim::core::instance_ptr >& 
InstanceModel::getInstances() const
{
    return m_instances;
}

void InstanceModel::addInstance(metasim::core::instance_ptr i)
{
    if (m_instances.indexOf(i) == -1)
    {
        m_instances.push_back(i);
        emit addedInstance(i);
    }
}

void InstanceModel::removeInstance(metasim::core::instance_ptr i)
{
    if (m_instances.removeAll(i) > 0)
    {
        emit removedInstance(i);
    }
}

