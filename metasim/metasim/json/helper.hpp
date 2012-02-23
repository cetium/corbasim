// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * helper.hpp
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

#ifndef METASIM_JSON_HELPER_HPP
#define METASIM_JSON_HELPER_HPP

#include <string>
#include <boost/shared_ptr.hpp>

namespace metasim 
{
namespace json 
{
namespace helper 
{

struct helper_base;

struct helper_base
{
    virtual void new_double(double d)
    {
        throw "Error!";
    }

    virtual void new_string(const std::string& d)
    {
        throw "Error!";
    }

    virtual void new_bool(bool d)
    {
        throw "Error!";
    }

    virtual void new_null()
    {
        throw "Error!";
    }

    // For structs
    virtual helper_base* new_child(const std::string& name)
    {
        throw "Error!";
    }

    // For arrays
    virtual helper_base* new_child()
    {
        throw "Error!";
    }

    virtual ~helper_base() {}

};

} // namespace helper
} // namespace json
} // namespace metasim

#endif /* METASIM_JSON_HELPER_HPP */

