// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * reflective.hpp
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

#ifndef METASIM_JSON_REFLECTIVE_HPP
#define METASIM_JSON_REFLECTIVE_HPP

#include <ostream>
#include <metasim/core/reflective_fwd.hpp>
#include <metasim/json/helper.hpp>
#include <metasim/json/writer.hpp>

namespace metasim 
{
namespace json 
{

struct reflective_helper : public helper::helper_base
{
    reflective_helper(core::reflective_base const * reflective,
            core::holder holder);

    virtual ~reflective_helper();

    void new_double(double d);

    void new_string(const std::string& d);

    void new_bool(bool d);

    void new_null();

    // For structs
    helper::helper_base* new_child(const std::string& name);

    // For arrays
    helper::helper_base* new_child();

    core::reflective_base const * m_reflective;
    core::holder m_holder;
    unsigned int m_currentIndex;
};

typedef csu::metasim::json::writer::json_writer< std::ostream > 
    std_writer_t;

void write(std_writer_t& w, 
        metasim::core::reflective_base const * reflective, 
        metasim::core::holder holder);

bool parse(core::reflective_base const * reflective, 
        core::holder& holder, const char * str, size_t size);

void write(std::ostream& os, core::reflective_base const * reflective, 
        const core::holder& holder, bool indent = false);

} // namespace json
} // namespace metasim

#endif /* METASIM_JSON_REFLECTIVE_HPP */

