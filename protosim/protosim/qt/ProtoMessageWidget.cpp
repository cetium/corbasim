// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ProtoMessageWidget.cpp
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

#include "ProtoMessageWidget.hpp"

using namespace protosim::qt;

ProtoMessageWidget::ProtoMessageWidget(
        const google::protobuf::Descriptor * descriptor,
        QWidget * parent) :
    QWidget(parent), m_descriptor(descriptor)
{
    QGridLayout * layout = new QGridLayout;

    int count = m_descriptor->field_count();

    for (int i = 0; i < count; i++) 
    {
        const google::protobuf::FieldDescriptor * field = 
            m_descriptor->field(i);

        layout->addWidget(new QLabel(field->name().c_str()), i, 0);
    }

    setLayout(layout);
}

ProtoMessageWidget::~ProtoMessageWidget()
{
}

