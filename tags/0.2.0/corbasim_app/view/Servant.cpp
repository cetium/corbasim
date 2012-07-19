// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Servant.cpp
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

#include "Servant.hpp"
#include <corbasim/core/reflective_fwd.hpp>

using namespace corbasim::app::view;

Servant::Servant(QMdiArea * area,
				 const QString& id, const corbasim::core::interface_reflective_base* factory,
        QObject * parent) :
    QObject(parent), m_mdi_area(area), m_id(id), m_factory(factory),
    m_sub_script(NULL), m_script(NULL)
{
    QString menu_entry = QString("%1 (%2)")
        .arg(m_id).arg(factory->get_fqn());

    m_menu = new QMenu(menu_entry);
    // TODO
    m_menu->addAction("Self-stimulator", this, SLOT(showSelfStimulator()));
    m_menu->addSeparator();
    m_menu->addAction("&Delete", this, SLOT(deleteServant()));
}

Servant::~Servant()
{
    delete m_menu;
    delete m_script;
    delete m_sub_script;
}

QMenu * Servant::getMenu() const
{
    return m_menu;
}

const corbasim::core::interface_reflective_base * Servant::getFactory() const
{
    return m_factory;
}

void Servant::deleteServant()
{
    emit deleteServant(m_id);
}

void Servant::showSelfStimulator()
{
    if (!m_sub_script)
    {
        m_script = new reflective_gui::SimpleScriptEditor();
        m_script->initialize(m_factory);

        m_sub_script = new QMdiSubWindow;
        m_sub_script->setWidget(m_script);
        m_sub_script->setWindowTitle(QString("%1: Self-stimulator").arg(m_id));
        m_mdi_area->addSubWindow(m_sub_script);

        QObject::connect(m_script,
            SIGNAL(sendRequest(corbasim::event::request_ptr)),
            this, 
            SLOT(sendRequest(corbasim::event::request_ptr)));
    }
    m_sub_script->showNormal();
    m_script->show();
    m_mdi_area->setActiveSubWindow(m_sub_script);
}

void Servant::sendRequest(corbasim::event::request_ptr req)
{
    emit sendRequest(m_id, req);
}

// Settings
void Servant::save(QSettings& settings) {}
void Servant::load(QSettings& settings) {}

