// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ReflectiveGUI.cpp
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

#include "ReflectiveGUI.hpp"
#include <cassert>
#include <limits>
//#include <metasim/qt/MultiFileSelectionWidget.hpp>

#include <iostream>
#include <sstream>
//#include <metasim/json/reflective.hpp>

using namespace metasim::gui;

namespace 
{

// should be a singleton instance of a factory
QWidget * createWidget(metasim::core::reflective_base const * reflective,
        QWidget * parent)
{
    using namespace metasim::core;

    if (!reflective)
        return new QLabel("Null reflective type!", parent);

    const reflective_type type = reflective->get_type();

    switch(type)
    {
        case TYPE_BOOL:
            return new BoolWidget(reflective, parent);

            // Integer types
        case TYPE_INT8:
        case TYPE_UINT8:
        case TYPE_INT16:
        case TYPE_UINT16:
        case TYPE_INT32:
        case TYPE_UINT32:
        case TYPE_INT64:
        case TYPE_UINT64:
            return new IntegerWidget(reflective, parent);
        
        case TYPE_STRING:
        case TYPE_WSTRING:
            return new StringWidget(reflective, parent);

        case TYPE_UNION:
            break;

        case TYPE_ARRAY:
        case TYPE_VECTOR:
#if 0
            if (reflective->get_slice()->is_primitive())
            {
                AlternativesWidget * alt = 
                    new AlternativesWidget(reflective, parent);

                alt->addAlternative("W", "", 
                        new SequenceWidget(reflective, parent));

                alt->addAlternative("F", "", 
                        new FilesWidget(reflective, parent));

                return alt;
            }
#endif
            return new SequenceWidget(reflective, parent);

        case TYPE_DOUBLE:
        case TYPE_FLOAT:
            return new FloatWidget(reflective, parent);
        case TYPE_STRUCT:
            return new StructWidget(reflective, parent);
        case TYPE_ENUM:
            return new EnumWidget(reflective, parent);
        default:
            break;
    }

    return new QLabel("Unsupported item!", parent);
}

} // namespace

ReflectiveWidgetBase::ReflectiveWidgetBase(
        core::reflective_base const * reflective) :
    m_reflective(reflective)
{
}

ReflectiveWidgetBase::~ReflectiveWidgetBase()
{
}

metasim::core::reflective_base const * 
ReflectiveWidgetBase::getReflective() const
{
    return m_reflective;
}

AlternativesWidget::AlternativesWidget(
        core::reflective_base const * reflective,
        QWidget * parent) :
    QWidget(parent), ReflectiveWidgetBase(reflective), m_group(this)
{
    m_group.setExclusive(true);

    QHBoxLayout * layout = new QHBoxLayout();

    m_stack = new QStackedWidget();
    layout->addWidget(m_stack);

    m_btnLayout = new QVBoxLayout();
    QSpacerItem * spacer = new QSpacerItem(20, 20, 
            QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_btnLayout->addSpacerItem(spacer);
    layout->addLayout(m_btnLayout);

    setLayout(layout);

    QObject::connect(&m_group, SIGNAL(buttonClicked(int)), 
            this, SLOT(changeWidget(int)));
}

AlternativesWidget::~AlternativesWidget()
{
}

void AlternativesWidget::toHolder(core::holder& holder) 
{
    if (!m_widgets.empty())
        m_widgets[m_stack->currentIndex()]->toHolder(holder);
}

void AlternativesWidget::fromHolder(core::holder& holder)
{
    for (unsigned int i = 0; i < m_widgets.size(); i++) 
    {
        m_widgets[i]->fromHolder(holder);
    }    
}

void AlternativesWidget::addAlternative(const QString& id,
        const QString& toolTip,
        ReflectiveWidgetBase * widget)
{
    QPushButton * btn = new QPushButton(id);

    btn->setToolTip(toolTip);
    btn->setCheckable(true);
    btn->setMaximumSize(20, 20);
    btn->setFlat(true);

    // before the spacer
    m_btnLayout->insertWidget(m_btnLayout->count() - 1, btn);

    if (m_widgets.empty()) btn->setChecked(true);

    m_group.addButton(btn, m_widgets.size());

    m_stack->addWidget(dynamic_cast< QWidget * >(widget));
    m_widgets.push_back(widget);
}

void AlternativesWidget::changeWidget(int idx)
{
    m_stack->setCurrentIndex(idx);
}

FloatWidget::FloatWidget(core::reflective_base const * reflective,
        QWidget * parent) :
    QDoubleSpinBox(parent), ReflectiveWidgetBase(reflective)
{
    using namespace metasim::core;

    const reflective_type type = reflective->get_type();

    switch(type)
    {
        case TYPE_DOUBLE:
            setRange(-std::numeric_limits< double >::max(),
                    std::numeric_limits< double >::max());
            break;
        case TYPE_FLOAT:
            setRange(-std::numeric_limits< float >::max(),
                    std::numeric_limits< float >::max());
            break;
        default:
            break;
    }
}

FloatWidget::~FloatWidget()
{
}

void FloatWidget::toHolder(core::holder& holder) 
{
    using namespace metasim::core;

    const reflective_type type = m_reflective->get_type();

    double value_ = value();

    switch(type)
    {
        case TYPE_DOUBLE:
            holder.to_value< double >() = (double) value_;
            break;
        case TYPE_FLOAT:
            holder.to_value< float >() = (float) value_;
            break;
        default:
            break;
    }
}

void FloatWidget::fromHolder(core::holder& holder)
{
    using namespace metasim::core;

    const reflective_type type = m_reflective->get_type();

    switch(type)
    {
        case TYPE_DOUBLE:
            setValue(holder.to_value< double >());
            break;
        case TYPE_FLOAT:
            setValue(holder.to_value< float >());
            break;
        default:
            break;
    }
}

IntegerWidget::IntegerWidget(core::reflective_base const * reflective,
        QWidget * parent) :
    QSpinBox(parent), ReflectiveWidgetBase(reflective)
{
    using namespace metasim::core;

    const reflective_type type = reflective->get_type();

    switch(type)
    {
        case TYPE_UINT8:
            setRange(std::numeric_limits< unsigned char >::min(),
                    std::numeric_limits< unsigned char >::max());
            break;
        case TYPE_CHAR:
            setRange(std::numeric_limits< char >::min(),
                    std::numeric_limits< char >::max());
            break;
        case TYPE_INT16:
            setRange(std::numeric_limits< short >::min(),
                    std::numeric_limits< short >::max());
            break;
        case TYPE_UINT16:
            setRange(std::numeric_limits< unsigned short >::min(),
                    std::numeric_limits< unsigned short >::max());
            break;
        case TYPE_INT32:
            setRange(std::numeric_limits< int32_t >::min(),
                    std::numeric_limits< int32_t >::max());
            break;
            // TODO custom widget
        case TYPE_UINT32:
            setRange(std::numeric_limits< uint32_t >::min(),
                    std::numeric_limits< int32_t >::max());
            break;
        case TYPE_INT64:
            setRange(std::numeric_limits< int32_t >::min(),
                    std::numeric_limits< int32_t >::max());
            break;
        case TYPE_UINT64:
            setRange(std::numeric_limits< uint32_t >::min(),
                    std::numeric_limits< int32_t >::max());
            break;
        default:
            break;
    }
}

IntegerWidget::~IntegerWidget()
{
}

void IntegerWidget::toHolder(core::holder& holder) 
{
    using namespace metasim::core;

    const reflective_type type = m_reflective->get_type();

    int value_ = value();

    switch(type)
    {
        case TYPE_UINT8:
            holder.to_value< unsigned char >() = (unsigned char) value_;
            break;
        case TYPE_CHAR:
            holder.to_value< char >() = (char) value_;
            break;
        case TYPE_INT16:
            holder.to_value< short >() = (short) value_;
            break;
        case TYPE_UINT16:
            holder.to_value< unsigned short >() = (unsigned short) value_;
            break;
        case TYPE_INT32:
            holder.to_value< int32_t >() = (int32_t) value_;
            break;
        case TYPE_UINT32:
            holder.to_value< uint32_t >() = (uint32_t) value_;
            break;
        case TYPE_INT64:
            holder.to_value< int64_t >() = (int64_t) value_;
            break;
        case TYPE_UINT64:
            holder.to_value< uint64_t >() = (uint64_t) value_;
            break;
        default:
            break;
    }
}

void IntegerWidget::fromHolder(core::holder& holder)
{
    using namespace metasim::core;

    const reflective_type type = m_reflective->get_type();

    switch(type)
    {
        case TYPE_UINT8:
            setValue(holder.to_value< unsigned char >());
            break;
        case TYPE_CHAR:
            setValue(holder.to_value< char >());
            break;
        case TYPE_INT16:
            setValue(holder.to_value< short >());
            break;
        case TYPE_UINT16:
            setValue(holder.to_value< unsigned short >());
            break;
        case TYPE_INT32:
            setValue(holder.to_value< int32_t >());
            break;
        case TYPE_UINT32:
            setValue(holder.to_value< uint32_t >());
            break;
        case TYPE_INT64:
            setValue(holder.to_value< int64_t >());
            break;
        case TYPE_UINT64:
            setValue(holder.to_value< uint64_t >());
            break;
        default:
            break;
    }
}

StringWidget::StringWidget(core::reflective_base const * reflective,
        QWidget * parent) :
    QLineEdit(parent), ReflectiveWidgetBase(reflective)
{
}

StringWidget::~StringWidget()
{
}

void StringWidget::toHolder(core::holder& holder)
{
    m_reflective->from_string(holder, text().toStdString());
}

void StringWidget::fromHolder(core::holder& holder)
{
    std::string str(m_reflective->to_string(holder));
    setText(str.c_str());
}

EnumWidget::EnumWidget(core::reflective_base const * reflective,
        QWidget * parent) :
    QComboBox(parent), ReflectiveWidgetBase(reflective)
{
    assert(reflective->is_enum());

    unsigned int count = reflective->get_children_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        addItem(reflective->get_child_name(i));
    }
}

EnumWidget::~EnumWidget()
{
}

void EnumWidget::toHolder(core::holder& holder) 
{
    holder.to_value< int32_t >() = currentIndex();
}

void EnumWidget::fromHolder(core::holder& holder)
{
    int idx = holder.to_value< int32_t >();

    if (idx > -1 && idx < count())
    {
        setCurrentIndex(idx);
    }
}

BoolWidget::BoolWidget(core::reflective_base const * reflective,
        QWidget * parent) :
    QCheckBox(parent), ReflectiveWidgetBase(reflective)
{
}

BoolWidget::~BoolWidget()
{
}

void BoolWidget::toHolder(core::holder& holder) 
{
    using namespace metasim::core;

    const reflective_type type = m_reflective->get_type();

    switch(type)
    {
        case TYPE_BOOL:
            holder.to_value< bool >() = isChecked();
            break;
        default:
            break;
    }
}

void BoolWidget::fromHolder(core::holder& holder)
{
    using namespace metasim::core;

    const reflective_type type = m_reflective->get_type();

    switch(type)
    {
        case TYPE_BOOL:
            setChecked(holder.to_value< bool >());
            break;
        default:
            break;
    }
}

StructWidget::StructWidget(core::reflective_base const * reflective,
        QWidget * parent) :
    QWidget(parent), ReflectiveWidgetBase(reflective)
{
    assert(reflective->get_type() == core::TYPE_STRUCT);

    QGridLayout * layout = new QGridLayout(this);

    unsigned int count = reflective->get_children_count();

    m_widgets.resize(count, NULL);

    for (unsigned int i = 0; i < count; i++) 
    {
        core::reflective_base const * child = 
            reflective->get_child(i);

        const char * child_name = reflective->get_child_name(i);

        QWidget * child_widget = createWidget(child, this);

        m_widgets[i] = dynamic_cast< ReflectiveWidgetBase* >(
                child_widget);

        child_widget->setObjectName(child_name);

        if (child->is_primitive() || child->is_enum())
        {
            QLabel * label = new QLabel(child_name, this);

            label->setObjectName(QString(child_name) + "_label");

            layout->addWidget(label, i, 0);
            layout->addWidget(child_widget, i, 1);
        }
        else
        {
            QGroupBox * gb = new QGroupBox(child_name, this);
            gb->setObjectName(QString(child_name) + "_group");

            QHBoxLayout * cLayout = new QHBoxLayout(gb);

            cLayout->addWidget(child_widget);

            gb->setLayout(cLayout);
            layout->addWidget(gb, i, 0, 1, 2);
        }
    }

    setLayout(layout);
}

StructWidget::~StructWidget()
{
}

void StructWidget::toHolder(core::holder& holder) 
{
    const unsigned int count = m_reflective->get_children_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        if (m_widgets[i])
        {
            core::holder child_holder(
                    m_reflective->get_child_value(holder, i));
            m_widgets[i]->toHolder(child_holder);
        }
    }
}

void StructWidget::fromHolder(core::holder& holder)
{
    const unsigned int count = m_reflective->get_children_count();

    for (unsigned int i = 0; i < count; i++) 
    {
        if (m_widgets[i])
        {
            core::holder child_holder(
                    m_reflective->get_child_value(holder, i));
            m_widgets[i]->fromHolder(child_holder);
        }
    }
}

SequenceWidget::SequenceWidget(core::reflective_base const * reflective,
        QWidget * parent) :
    QWidget(parent), ReflectiveWidgetBase(reflective), m_old_idx(-1),
    m_sbLength(NULL), m_sbCurrentIndex(NULL)
{
    QVBoxLayout * layout = new QVBoxLayout;
 
    QHBoxLayout * headerLayout = new QHBoxLayout;

    if (reflective->is_variable_length())
    {
        m_sbLength = new QSpinBox();
        headerLayout->addWidget(new QLabel("Length"));
        headerLayout->addWidget(m_sbLength);
        m_sbLength->setObjectName("length");
    }

    m_sbCurrentIndex = new QSpinBox();
    headerLayout->addWidget(new QLabel("Index"));
    headerLayout->addWidget(m_sbCurrentIndex);
    m_sbCurrentIndex->setObjectName("index");

    layout->addLayout(headerLayout);

    m_holder = reflective->create_holder();

    m_slice_widget = createWidget(reflective->get_slice(), this);
    
    layout->addWidget(m_slice_widget);

    m_slice = dynamic_cast< ReflectiveWidgetBase * >(m_slice_widget);

    // Spacer
    QSpacerItem * spacer = new QSpacerItem(40, 20, 
            QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addItem(spacer);

    setLayout(layout);

    if (reflective->is_variable_length())
    {
        m_slice_widget->hide();

        QObject::connect(m_sbLength, SIGNAL(valueChanged(int)),
                this, SLOT(lengthChanged(int)));

        // TODO maximo razonable
        m_sbLength->setRange(0, 9999999);
        m_sbLength->setValue(0);
    }
    else
    {
        m_sbCurrentIndex->setRange(0, m_reflective->get_length(m_holder) - 1);
        indexChanged(0);
    }

    QObject::connect(m_sbCurrentIndex, SIGNAL(valueChanged(int)),
            this, SLOT(indexChanged(int)));
}

SequenceWidget::~SequenceWidget()
{
}

void SequenceWidget::toHolder(core::holder& holder)
{
    // store current value
    if (m_reflective->get_length(m_holder) > 0)
    {
        core::holder child_value = m_reflective->get_child_value(
                m_holder, m_sbCurrentIndex->value());
        m_slice->toHolder(child_value);
    }

    m_reflective->copy(m_holder, holder);
}

void SequenceWidget::fromHolder(core::holder& holder)
{
    m_reflective->copy(holder, m_holder);

    if (m_reflective->is_variable_length())
    {
        // Invalidates current value
        m_old_idx = -1;

        // show current value
        m_sbLength->setValue(m_reflective->get_length(m_holder));
    }
    else if (m_old_idx > -1)
    {
        core::holder child_value = 
            m_reflective->get_child_value(m_holder, m_old_idx);

        m_slice->fromHolder(child_value);
    }
}

void SequenceWidget::lengthChanged(int len)
{
    if (!m_reflective->is_variable_length())
        return;

    if (len == 0)
    {
        m_slice_widget->hide();
    }
    else
    {
        m_slice_widget->show();
    }

    m_reflective->set_length(m_holder, len);

    m_sbCurrentIndex->setRange(0, len-1);
}

void SequenceWidget::indexChanged(int idx)
{
    unsigned int length = m_reflective->get_length(m_holder);

    // store current value
    if (m_old_idx > -1 && m_old_idx < (int) length)
    {
        core::holder child_value = m_reflective->get_child_value(
                m_holder, m_old_idx);
        m_slice->toHolder(child_value);
    }

    m_old_idx = idx;

    core::holder child_value = m_reflective->get_child_value(m_holder, idx);
    m_slice->fromHolder(child_value);
}

// Files
#if 0
FilesWidget::FilesWidget(core::reflective_base const * reflective,
        QWidget * parent) :
    qt::MultiFileSelectionWidget(parent), 
    ReflectiveWidgetBase(reflective)
{
}

FilesWidget::~FilesWidget()
{
}

void FilesWidget::toHolder(core::holder& holder) 
{
}

void FilesWidget::fromHolder(core::holder& holder)
{
}
#endif

