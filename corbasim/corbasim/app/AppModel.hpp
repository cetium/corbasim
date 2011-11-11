// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * AppModel.hpp
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

#ifndef CORBASIM_APP_APPMODEL_HPP
#define CORBASIM_APP_APPMODEL_HPP

#include "appC.h"

namespace corbasim 
{
namespace app 
{

class AppController;

class AppModel
{
public:
    AppModel();
    virtual ~AppModel();

    void setController(AppController * controller);

    void createObjref(const corbasim::app::ObjrefConfig& cfg);

protected:
    AppController * m_controller;
};

} // namespace app
} // namespace corbasim

#endif /* CORBASIM_APP_APPMODEL_HPP */

