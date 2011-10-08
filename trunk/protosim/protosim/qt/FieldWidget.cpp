// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * FieldWidget.cpp
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

#include "FieldWidget.hpp"
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>

using namespace protosim::qt;

FieldWidget::FieldWidget(const google::protobuf::FieldDescriptor * desc) :
    m_descriptor(desc)
{
}

RequiredFieldWidget::RequiredFieldWidget(
        const google::protobuf::FieldDescriptor * desc,
        QWidget * parent) :
    QWidget(parent), FieldWidget(desc)
{
}

RequiredFieldWidget::~RequiredFieldWidget()
{
}

void RequiredFieldWidget::getWidgetValue(google::protobuf::Message * msg)
{
}

OptionalFieldWidget::OptionalFieldWidget(
        const google::protobuf::FieldDescriptor * desc,
        QWidget * parent) :
    QWidget(parent), FieldWidget(desc)
{
}

OptionalFieldWidget::~OptionalFieldWidget()
{
}

void OptionalFieldWidget::getWidgetValue(google::protobuf::Message * msg)
{
}

RepeatedFieldWidget::RepeatedFieldWidget(
        const google::protobuf::FieldDescriptor * desc,
        QWidget * parent) :
    QWidget(parent), FieldWidget(desc)
{
}

RepeatedFieldWidget::~RepeatedFieldWidget()
{
}

void RepeatedFieldWidget::getWidgetValue(google::protobuf::Message * msg)
{
}

