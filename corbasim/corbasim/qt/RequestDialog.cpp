// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * RequestDialog.cpp
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

#include "RequestDialog.hpp"
#include <corbasim/gui/dialogs.hpp>
#include <corbasim/qt/initialize.hpp>

#include <iostream>

#ifdef CORBASIM_USE_QTSCRIPT
#include <corbasim/qt/private/ScriptEditor.hpp>
#endif

using namespace corbasim;
using namespace corbasim::qt;

RequestDialog::RequestDialog(dialogs::input_base* dlg, 
        QWidget * parent) :
    QDialog(parent), m_dlg(dlg)
{
    corbasim::qt::initialize();

    QVBoxLayout * layout = new QVBoxLayout;

    QScrollArea * scroll = new QScrollArea;
    scroll->setObjectName("scroll");
    scroll->setWidgetResizable(true);
    m_dlg->get_qwidget()->setObjectName("form");
    scroll->setWidget(m_dlg->get_qwidget());
    layout->addWidget(scroll); 

    QHBoxLayout * periodicLayout = new QHBoxLayout;

    periodicLayout->addWidget(new QLabel("Period (ms)"));
    m_sbPeriod = new QSpinBox;
    m_sbPeriod->setRange(0, 999999);
    m_sbPeriod->setValue(100);
    periodicLayout->addWidget(m_sbPeriod);

    periodicLayout->addWidget(new QLabel("Times"));
    m_sbTimes = new QSpinBox;
    m_sbTimes->setRange(-1, 999999);
    m_sbTimes->setValue(-1);
    periodicLayout->addWidget(m_sbTimes);

    periodicLayout->addWidget(new QLabel("Use stored value"));
    m_cbUseStored = new QCheckBox;
    m_cbUseStored->setChecked(true);
    periodicLayout->addWidget(m_cbUseStored);

    layout->addLayout(periodicLayout);
   
    // Botones 
    QHBoxLayout * btnsLayout = new QHBoxLayout;

    // Start stop
    m_pbStartStop = new QPushButton("S&tart/Stop");
    m_pbStartStop->setCheckable(true);
    QObject::connect(m_pbStartStop, SIGNAL(toggled(bool)), 
            this, SLOT(startStopChecked(bool)));
    btnsLayout->addWidget(m_pbStartStop);

    // Update
    m_pbUpdate = new QPushButton("&Update");
    m_pbUpdate->setObjectName("updateButton");
    QObject::connect(m_pbUpdate, SIGNAL(clicked()), 
            this, SLOT(storeRequest()));
    btnsLayout->addWidget(m_pbUpdate);

    // Send button
    QPushButton * btn = new QPushButton("&Send");
    btn->setObjectName("sendButton");
    QObject::connect(btn, SIGNAL(clicked()), 
            this, SLOT(sendClicked())); 
    btnsLayout->addWidget(btn);

#ifdef CORBASIM_USE_QTSCRIPT
    // Reload script button
    btn = new QPushButton("&Reload script");
    btn->setObjectName("reloadButton");
    QObject::connect(btn, SIGNAL(clicked()), 
            this, SLOT(reloadScript())); 
    btnsLayout->addWidget(btn);
#endif /* CORBASIM_USE_QTSCRIPT*/

    // Close button
    btn = new QPushButton("&Close");
    btn->setObjectName("closeButton");
    QObject::connect(btn, SIGNAL(clicked()), 
            this, SLOT(hide())); 
    btnsLayout->addWidget(btn);

    layout->addLayout(btnsLayout);
   
    // Timer
    QObject::connect(&m_timer, SIGNAL(timeout()), 
            this, SLOT(sendStored()));

#ifdef CORBASIM_USE_QTSCRIPT
    QVBoxLayout * mainLayout = new QVBoxLayout;
    m_tabs = new QTabWidget;
    QWidget * w = new QWidget;
    w->setLayout(layout);
    m_tabs->addTab(w, "Form");

    m_code = new qt::priv::ScriptEditor;
    m_tabs->addTab(m_code, "Script");

    mainLayout->addWidget(m_tabs);
    setLayout(mainLayout);
#else
    setLayout(layout);
#endif


#ifdef CORBASIM_USE_QTSCRIPT

    m_thisObject = m_engine.newQObject(this);

    reloadScript();

#endif /* CORBASIM_USE_QTSCRIPT*/

}

RequestDialog::~RequestDialog()
{
    delete m_dlg;
}

void RequestDialog::stopTimer()
{
    m_pbStartStop->setChecked(false);
}

#ifdef CORBASIM_USE_QTSCRIPT
void RequestDialog::reloadScript()
{
    /*
    QFile file(QString(m_dlg->get_name())+ ".js");

    if (!file.exists() || 
            !file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cerr << "Could not open program file!" << std::endl;
        return;
    }

    QString strProgram = file.readAll();
    */
    const QString strProgram (m_code->toPlainText());
    if (!m_engine.canEvaluate(strProgram))
    {
        std::cerr << "Could not evaluate program!" << std::endl;
        return;
    }

    m_engine.evaluate(strProgram, QString(m_dlg->get_name())+ ".js");

    if (m_engine.hasUncaughtException())
    {
        QString error = QString("%1\n\n%2")
            .arg(m_engine.uncaughtException().toString())
            .arg(m_engine.uncaughtExceptionBacktrace().join("\n"));

        QMessageBox::critical(this, "Error", error);
        return;
    }

    m_initFunc = m_engine.evaluate("init");
    m_preFunc = m_engine.evaluate("pre");
    m_postFunc = m_engine.evaluate("post");
    
    m_engine.evaluate(
            "function to_json() { return JSON.stringify(this); }");
    m_jsonFunc = m_engine.evaluate("to_json");

    if (m_initFunc.isFunction())
        m_initFunc.call(m_thisObject);

}
#endif /* CORBASIM_USE_QTSCRIPT*/

void RequestDialog::sendClicked()
{

#ifdef CORBASIM_USE_QTSCRIPT
    if (m_preFunc.isFunction())
    {
        // Convierte el contenido del diálogo a JSON
        std::string str;
        m_dlg->to_json(str);

        // Evalua la cadena y la asigna como propiedad
        QScriptValue json_value = m_engine.evaluate(
                QString('(') + str.c_str() + ')');
        m_thisObject.setProperty("request", json_value);

        m_preFunc.call(m_thisObject);

        // property -> JSON
        QScriptValue val = m_jsonFunc.call(json_value);

        // JSON -> dialog
        str = val.toString().toStdString();
        m_dlg->from_json(str);
    }
#endif /* CORBASIM_USE_QTSCRIPT*/

    emit sendRequest(event::request_ptr(m_dlg->create_request()));

#ifdef CORBASIM_USE_QTSCRIPT
    if (m_postFunc.isFunction())
    {
        m_postFunc.call(m_thisObject);

        // property -> JSON
        QScriptValue json_value = m_thisObject.property("request");

        if (json_value.isObject())
        {
            QScriptValue val = m_jsonFunc.call(json_value);

            // JSON -> dialog
            const std::string str = val.toString().toStdString();
            m_dlg->from_json(str);
        }
    }
#endif /* CORBASIM_USE_QTSCRIPT*/
}

void RequestDialog::startStopChecked(bool chk)
{
    if (chk)
    {
        storeRequest();
        m_currentPeriodicRequest = 0;
        m_timer.start(m_sbPeriod->value());
    }
    else
    {
        m_timer.stop();
    }
}

void RequestDialog::storeRequest()
{
    m_storedRequest = event::request_ptr(m_dlg->create_request());
}

void RequestDialog::sendStored()
{
    if (m_cbUseStored->isChecked())
        emit sendRequest(m_storedRequest);
    else
        sendClicked();
        // emit sendRequest(event::request_ptr(m_dlg->create_request()));

    ++m_currentPeriodicRequest;
    if (m_sbTimes->value() >= 0 && 
            m_currentPeriodicRequest >= m_sbTimes->value())
        m_pbStartStop->setChecked(false);
}

void RequestDialog::hideEvent(QHideEvent * event)
{
    QWidget * parent = parentWidget();

    if (parent && dynamic_cast< QMdiSubWindow* >(parent))
        parent->hide();

    event->accept();
}

