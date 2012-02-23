// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * qvariant.hpp
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

#ifndef METASIM_GUI_QVARIANT_HPP
#define METASIM_GUI_QVARIANT_HPP

#include <metasim/core/reflective_fwd.hpp>
#include <QVariant>
#include <QScriptValue>
#include <QScriptEngine>

namespace metasim 
{
namespace gui 
{

    QVariant toQVariant(
            metasim::core::reflective_base const * reflective,
            metasim::core::holder& holder);

    bool fromQVariant(
            metasim::core::reflective_base const * reflective,
            metasim::core::holder& holder,
            const QVariant& var);

    QScriptValue toQScriptValue(
            QScriptEngine * engine,
            metasim::core::reflective_base const * reflective,
            metasim::core::holder& holder);

    bool fromQScriptValue(
            QScriptEngine * engine,
            metasim::core::reflective_base const * reflective,
            metasim::core::holder& holder,
            const QScriptValue& var);

} // namespace gui
} // namespace metasim

#endif /* METASIM_GUI_QVARIANT_HPP */

