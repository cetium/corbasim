// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * FieldWidget.hpp
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

#ifndef PROTOSIM_QT_FIELDWIDGET_HPP
#define PROTOSIM_QT_FIELDWIDGET_HPP

#include <protosim/protobuf_fwd.hpp>
#include <QtGui>

namespace protosim 
{
namespace qt 
{

class FieldWidget;

class RequiredFieldWidget;
class OptionalFieldWidget;
class RepeatedFieldWidget;

class ProtoMessageWidget;

class FieldWidget
{
public:

    virtual void getWidgetValue(google::protobuf::Message * msg) = 0;

protected:

    FieldWidget(const google::protobuf::FieldDescriptor *);

    const google::protobuf::FieldDescriptor * m_descriptor;
};

class RequiredFieldWidget : public QWidget, public FieldWidget
{
    Q_OBJECT
public:

    RequiredFieldWidget(const google::protobuf::FieldDescriptor * field, 
            QWidget * parent = 0);
    virtual ~RequiredFieldWidget();
    
    void getWidgetValue(google::protobuf::Message * msg);
};

class OptionalFieldWidget : public QWidget, public FieldWidget
{
    Q_OBJECT
public:

    OptionalFieldWidget(const google::protobuf::FieldDescriptor * field, 
            QWidget * parent = 0);
    virtual ~OptionalFieldWidget();
    
    void getWidgetValue(google::protobuf::Message * msg);
};

class RepeatedFieldWidget : public QWidget, public FieldWidget
{
    Q_OBJECT
public:

    RepeatedFieldWidget(const google::protobuf::FieldDescriptor * field, 
            QWidget * parent = 0);
    virtual ~RepeatedFieldWidget();
    
    void getWidgetValue(google::protobuf::Message * msg);
};

} // namespace qt
} // namespace protosim

#endif /* PROTOSIM_QT_FIELDWIDGET_HPP */

