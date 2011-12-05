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
#include "model/Objref.hpp"
#include "model/Servant.hpp"

#include <map>
#include <corbasim/event.hpp>

namespace corbasim 
{
namespace app 
{

class AppController;

struct AppModelData;

class AppModel
{
public:
    AppModel();
    virtual ~AppModel();

    void setController(AppController * controller);

    void createObjref(const corbasim::app::ObjrefConfig& cfg);
    void deleteObjref(const QString& id);

    void createServant(const corbasim::app::ServantConfig& cfg);
    void deleteServant(const QString& id);

    void sendRequest(const QString& id,
            corbasim::event::request_ptr req);

    void saveFile(const QString& file);
    void loadFile(const QString& file);
    
    void clearConfig();

    void updateReference(const QString& id,
            const CORBA::Object_var& ref);

protected:

    AppModelData * m_data;

    AppController * m_controller;

    typedef std::map< QString, model::Objref_ptr > objrefs_t;
    objrefs_t m_objrefs;

    typedef std::map< QString, model::Servant_ptr > servants_t;
    servants_t m_servants;

    typedef std::map< QString, void * > libraries_t;
    libraries_t m_libraries;

    typedef std::map< QString, const gui::gui_factory_base * > 
        factories_t;
    factories_t m_factories;

    const gui::gui_factory_base * getFactory(const QString& fqn);
};

} // namespace app
} // namespace corbasim

#endif /* CORBASIM_APP_APPMODEL_HPP */
