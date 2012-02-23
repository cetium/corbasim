// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ReflectiveGUI.hpp
 * Copyright (C) Cátedra SAES-UMU 2011 <catedra-saes-umu@listas.um.es>
 *
 * METASIM is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * METASIM is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef METASIM_GUI_REFLECTIVEGUI_HPP
#define METASIM_GUI_REFLECTIVEGUI_HPP

#include <QtGui>
#include <metasim/core/reflective_fwd.hpp>
//#include <metasim/qt/MultiFileSelectionWidget.hpp>

namespace metasim 
{
namespace gui 
{

class ReflectiveWidgetBase
{
protected:

    ReflectiveWidgetBase(core::reflective_base const * reflective);

public:

    virtual ~ReflectiveWidgetBase();

    core::reflective_base const * getReflective() const;

    virtual void toHolder(core::holder& holder) = 0;
    virtual void fromHolder(core::holder& holder) = 0;

protected:

    core::reflective_base const * m_reflective;
};

class AlternativesWidget : public QWidget, public ReflectiveWidgetBase
{
    Q_OBJECT
public:
    AlternativesWidget(core::reflective_base const * reflective,
            QWidget * parent = 0);
    virtual ~AlternativesWidget();
 
    virtual void toHolder(core::holder& holder);
    virtual void fromHolder(core::holder& holder);

    void addAlternative(const QString& id,
            const QString& toolTip,
            ReflectiveWidgetBase * widget);

protected slots:

    void changeWidget(int);

protected:

    QButtonGroup m_group;
    QStackedWidget * m_stack;
    QVBoxLayout * m_btnLayout;

    std::vector< ReflectiveWidgetBase * > m_widgets;
};

class FloatWidget : public QDoubleSpinBox, public ReflectiveWidgetBase
{
    Q_OBJECT
public:
    FloatWidget(core::reflective_base const * reflective,
            QWidget * parent = 0);
    virtual ~FloatWidget();
 
    virtual void toHolder(core::holder& holder);
    virtual void fromHolder(core::holder& holder);
};

class IntegerWidget : public QSpinBox, public ReflectiveWidgetBase
{
    Q_OBJECT
public:
    IntegerWidget(core::reflective_base const * reflective,
            QWidget * parent = 0);
    virtual ~IntegerWidget();

    virtual void toHolder(core::holder& holder);
    virtual void fromHolder(core::holder& holder);
};

class StringWidget : public QLineEdit, public ReflectiveWidgetBase
{
    Q_OBJECT
public:
    StringWidget(core::reflective_base const * reflective,
            QWidget * parent = 0);
    virtual ~StringWidget();

    virtual void toHolder(core::holder& holder);
    virtual void fromHolder(core::holder& holder);
};

class EnumWidget : public QComboBox, public ReflectiveWidgetBase
{
    Q_OBJECT
public:
    EnumWidget(core::reflective_base const * reflective,
            QWidget * parent = 0);
    virtual ~EnumWidget();

    virtual void toHolder(core::holder& holder);
    virtual void fromHolder(core::holder& holder);
};

class BoolWidget : public QCheckBox, public ReflectiveWidgetBase
{
    Q_OBJECT
public:
    BoolWidget(core::reflective_base const * reflective,
            QWidget * parent = 0);
    virtual ~BoolWidget();
 
    virtual void toHolder(core::holder& holder);
    virtual void fromHolder(core::holder& holder);
};

class StructWidget : public QWidget, public ReflectiveWidgetBase
{
    Q_OBJECT
public:
    StructWidget(core::reflective_base const * reflective,
            QWidget * parent = 0);
    virtual ~StructWidget();
 
    virtual void toHolder(core::holder& holder);
    virtual void fromHolder(core::holder& holder);

protected:

    std::vector< ReflectiveWidgetBase * > m_widgets;
};

class SequenceWidget : public QWidget, public ReflectiveWidgetBase
{
    Q_OBJECT
public:
    SequenceWidget(core::reflective_base const * reflective,
            QWidget * parent = 0);
    virtual ~SequenceWidget();

    virtual void toHolder(core::holder& holder);
    virtual void fromHolder(core::holder& holder);

protected slots:

    void lengthChanged(int);
    void indexChanged(int);

protected:

    int m_old_idx;

    QSpinBox * m_sbLength;
    QSpinBox * m_sbCurrentIndex;

    ReflectiveWidgetBase * m_slice;
    QWidget * m_slice_widget;

    core::holder m_holder;
};

#if 0
class FilesWidget : public qt::MultiFileSelectionWidget, 
    public ReflectiveWidgetBase
{
    Q_OBJECT
public:
    FilesWidget(core::reflective_base const * reflective,
            QWidget * parent = 0);
    virtual ~FilesWidget();
 
    virtual void toHolder(core::holder& holder);
    virtual void fromHolder(core::holder& holder);
};
#endif

} // namespace gui
} // namespace metasim

#endif /* METASIM_GUI_REFLECTIVEGUI_HPP */

