// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * widgets.hpp
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

#ifndef PROTOSIM_QT_WIDGETS_HPP
#define PROTOSIM_QT_WIDGETS_HPP

#include <protosim/protobuf_fwd.hpp>

class QWidget;

namespace protosim 
{
namespace qt 
{

class FieldWidget;

FieldWidget * create_widget_by_label(
        const google::protobuf::FieldDescriptor * field);

QWidget * create_widget_by_type(
        const google::protobuf::FieldDescriptor * field);

bool is_groupbox_widget(
        const google::protobuf::FieldDescriptor * field);

} // namespace qt
} // namespace protosim

#endif /* PROTOSIM_QT_WIDGETS_HPP */

