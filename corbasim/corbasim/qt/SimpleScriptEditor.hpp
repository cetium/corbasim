// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * SimpleScriptEditor.hpp
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

#ifndef CORBASIM_QT_SIMPLESCRIPTEDITOR_HPP
#define CORBASIM_QT_SIMPLESCRIPTEDITOR_HPP

#include <QtGui>
#include <list>
#include <corbasim/event.hpp>
#include <corbasim/gui/gui_factory.hpp> // TODO fwd

namespace corbasim 
{
namespace qt 
{

class MultiInputWidget;

class SimpleScriptEditor : public QMainWindow
{
    Q_OBJECT
public:
    SimpleScriptEditor(QWidget * parent = 0);
    virtual ~SimpleScriptEditor();

    void initialize(gui::gui_factory_base * factory);

public slots:
    void appendRequest();
    void appendOneRequest();
    void sendNextRequest();
    void playClicked();
    void playFromSelected();
    void sendCurrent();
    void clearClicked();
    void stopClicked();
    void deleteSelected();
    
    void copySelected();
    void doSave();
    void doLoad();
    
    void moveUp();
    void moveDown();

signals:
    void sendRequest(corbasim::event::request_ptr);

protected:

    typedef std::list< corbasim::event::request_ptr > requests_t;

    void doAppendRequest(corbasim::event::request_ptr, 
            bool beforeSelected = false);
    int getSelected();

    QTimer m_timer;
    unsigned int m_current_request;
    requests_t::iterator m_current_iterator;

    QComboBox * m_selector;
    MultiInputWidget * m_multi;
    QSpinBox * m_diff; 
    QSpinBox * m_how_many; 
    QTreeWidget * m_tree;
    QCheckBox * m_cbInsertAtEnd;
    
    requests_t m_requests;

    gui::gui_factory_base * m_factory;

    core::request_serializer_base * m_request_serializer;
};

} // namespace qt
} // namespace corbasim

#endif /* CORBASIM_QT_SIMPLESCRIPTEDITOR_HPP */

