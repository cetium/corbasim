// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * writer.hpp
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

#ifndef CORBASIM_JSON_WRITER_HPP
#define CORBASIM_JSON_WRITER_HPP

#include <protobuf2json/json/helper.hpp>
#include <protobuf2json/json/detail/json_writer.hpp>

namespace protobuf2json 
{
namespace json 
{

template< typename Ostream, typename T >
inline void write(Ostream& os, const T& t);

template< typename Ostream, typename T >
inline void write(Ostream& os, const T& t)
{
    typedef csu::protobuf2json::json::writer::json_writer< Ostream > writer_t;
    writer_t w(os);
    helper::message_helper::write(w, &t);
}

} // namespace json
} // namespace protobuf2json

#endif /* CORBASIM_JSON_WRITER_HPP */

