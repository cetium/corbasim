// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * widgets.cpp
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

#include "widgets.hpp"
#include <protosim/qt/ProtoMessageWidget.hpp>
#include <protosim/qt/FieldWidget.hpp>

#include <google/protobuf/descriptor.h>

namespace protosim 
{
namespace qt
{

QWidget * create_widget_by_label(
        const google::protobuf::FieldDescriptor * field)
{
    namespace pb = google::protobuf;

    switch(field->label())
    {
        case pb::FieldDescriptor::LABEL_OPTIONAL:
            return new OptionalFieldWidget(field);
        case pb::FieldDescriptor::LABEL_REQUIRED:
            return new RequiredFieldWidget(field);
        case pb::FieldDescriptor::LABEL_REPEATED:
            return new RepeatedFieldWidget(field);
        default:
            break;
    }
    return NULL;
}

QWidget * create_widget_by_type(
        const google::protobuf::FieldDescriptor * field)
{
    namespace pb = google::protobuf;

    switch(field->cpp_type())
    {
        case pb::FieldDescriptor::CPPTYPE_MESSAGE:
            return new ProtoMessageWidget(field->message_type());
        case pb::FieldDescriptor::CPPTYPE_STRING:
            return new QLineEdit;
        case pb::FieldDescriptor::CPPTYPE_INT32:
        case pb::FieldDescriptor::CPPTYPE_UINT32:
        case pb::FieldDescriptor::CPPTYPE_INT64:
        case pb::FieldDescriptor::CPPTYPE_UINT64:
            return new QSpinBox;
        case pb::FieldDescriptor::CPPTYPE_ENUM:
            {
                QComboBox * cb = new QComboBox;
                const pb::EnumDescriptor * en = field->enum_type();
                int count = en->value_count();

                for (int i = 0; i < count; i++) 
                {
                    const pb::EnumValueDescriptor * value = en->value(i);
                    cb->addItem(value->name().c_str());
                }
                return cb;
            }
        default:
            return new QSpinBox;
    }
    return NULL;
}

} // namespace qt
} // namespace protosim

