// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * writer.hpp
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

#ifndef METASIM_JSON_WRITER_HPP
#define METASIM_JSON_WRITER_HPP

#include <metasim/json/helper.hpp>
#include <metasim/json/detail/json_writer.hpp>
#include <ostream>

namespace metasim 
{
namespace json 
{

typedef csu::metasim::json::writer::json_writer< std::ostream > ostream_writer_t;

} // namespace json
} // namespace metasim

#endif /* METASIM_JSON_WRITER_HPP */

