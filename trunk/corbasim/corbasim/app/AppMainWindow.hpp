// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * AppMainWindow.hpp
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

#ifndef CORBASIM_APP_APPMAINWINDOW_HPP
#define CORBASIM_APP_APPMAINWINDOW_HPP

#include <map>
#include <QtGui>
#include <corbasim/gui/gui_factory_fwd.hpp>
#include "view/Objref.hpp"

namespace corbasim 
{
namespace app 
{

class AppController;

class AppMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    AppMainWindow(QWidget * parent = 0);
    virtual ~AppMainWindow();

    void setController(AppController * controller);

public slots:

    void showCreateObjref();
    void showCreateServant();

    void showLoad();
    void showSave();

    void showLog();

    // Notificaciones del controlador

    void objrefCreated(const QString& id,
        corbasim::gui::gui_factory_base * factory);
    void objrefDeleted(const QString& id);

    void requestSent(const QString& id, 
            corbasim::event::request_ptr req,
            corbasim::event::event_ptr resp);
    void requestReceived(const QString& id, 
            corbasim::event::request_ptr req,
            corbasim::event::event_ptr resp);

    void displayError(const QString& err);

signals:

    void saveFile(QString);
    void loadFile(QString);

protected:
    AppController * m_controller;
    QMdiArea * m_mdi_area;

    typedef std::map< QString, view::Objref_ptr > objrefs_t;
    objrefs_t m_objrefs;

    QMenu * m_menuObjects;
    QMenu * m_menuServants;

    QStatusBar * m_statusBar;

    // Subwindows
    QMdiSubWindow * m_sub_create_objref;
    QMdiSubWindow * m_sub_create_servant;
    QMdiSubWindow * m_sub_log;
    
    // Subwindows widgets
    QDialog * m_create_objref;
    QDialog * m_create_servant;
    QTreeWidget * m_log;

    void appendToLog(QTreeWidgetItem * item);
};

} // namespace app
} // namespace corbasim

#endif /* CORBASIM_APP_APPMAINWINDOW_HPP */
