// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ProtoMessageWidget.hpp
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

#ifndef PROTOSIM_PROTOMESSAGEWIDGET_HPP
#define PROTOSIM_PROTOMESSAGEWIDGET_HPP

#include <QtGui>
#include <protosim/protobuf_fwd.hpp>

namespace protosim 
{
namespace qt 
{

class ProtoMessageWidget : public QWidget
{
    Q_OBJECT
public:
    ProtoMessageWidget(const google::protobuf::Descriptor * descriptor,
            QWidget * parent = 0);
    virtual ~ProtoMessageWidget();

protected:
    const google::protobuf::Descriptor * m_descriptor;
};

} // namespace qt
} // namespace protosim

#endif /* PROTOSIM_PROTOMESSAGEWIDGET_HPP */

