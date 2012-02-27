// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * reflective.ipp
 * Copyright (C) Andrés Senac 2012 <andres@senac.es>
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

#include "reflective.hpp"

// Boolean
namespace metasim 
{
namespace core 
{
namespace detail 
{

template< typename T >
bool_reflective< T >::bool_reflective(reflective_base const * parent, 
        unsigned int idx) :
    reflective_base(parent, idx)
{
}

template< typename T >
bool bool_reflective< T >::is_primitive() const { return true; }

template< typename T >
reflective_type bool_reflective< T >::get_type() const
{
    return TYPE_BOOL;
}

template< typename T >
holder bool_reflective< T >::create_holder() const
{
    return new holder_ref_impl< T >();
}

template< typename T >
void bool_reflective< T >::copy(holder const& src, holder& dst) const
{
    dst.to_value< T >() = const_cast< holder& >(src).to_value< T >();
}

// Primitive

template< typename T >
holder primitive_reflective< T >::create_holder() const
{
    return new holder_ref_impl< T >();
}

template< typename T >
primitive_reflective< T >::primitive_reflective(
        reflective_base const * parent, 
        unsigned int idx) :
    reflective_base(parent, idx)
{
}

template< typename T >
bool primitive_reflective< T >::is_primitive() const 
{ 
    return true; 
}

template< >
METASIM_CORE_DECLSPEC reflective_type primitive_reflective< double >::get_type() const
{
    return TYPE_DOUBLE;
}

template< >
METASIM_CORE_DECLSPEC reflective_type primitive_reflective< float >::get_type() const
{
    return TYPE_FLOAT;
}

template< >
METASIM_CORE_DECLSPEC reflective_type primitive_reflective< char >::get_type() const
{
    return TYPE_CHAR;
}

template< >
METASIM_CORE_DECLSPEC reflective_type primitive_reflective< unsigned char >::get_type() const
{
    return TYPE_INT8;
}

template< >
METASIM_CORE_DECLSPEC reflective_type primitive_reflective< short >::get_type() const
{
    return TYPE_INT16;
}

template< >
METASIM_CORE_DECLSPEC reflective_type primitive_reflective< unsigned short >::get_type() const
{
    return TYPE_UINT16;
}

template< >
METASIM_CORE_DECLSPEC reflective_type primitive_reflective< uint32_t >::get_type() const
{
    return TYPE_UINT32;
}

template< >
METASIM_CORE_DECLSPEC reflective_type primitive_reflective< int32_t >::get_type() const
{
    return TYPE_INT32;
}

template< >
METASIM_CORE_DECLSPEC reflective_type primitive_reflective< uint64_t >::get_type() const
{
    return TYPE_UINT64;
}

template< >
METASIM_CORE_DECLSPEC reflective_type primitive_reflective< int64_t >::get_type() const
{
    return TYPE_INT64;
}

template< typename T >
void primitive_reflective< T >::copy(holder const& src, holder& dst) const
{
    dst.to_value< T >() = const_cast< holder& >(src).to_value< T >();
}

} // namespace detail
} // namespace core
} // namespace metasim

