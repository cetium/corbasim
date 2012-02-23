// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * holder.hpp
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

#ifndef METASIM_HOLDER_HPP
#define METASIM_HOLDER_HPP

#include <boost/shared_ptr.hpp>

namespace metasim 
{
namespace core 
{

struct holder;

struct holder_impl_base {};

typedef boost::shared_ptr< holder_impl_base > holder_impl_ptr;

template< typename T >
struct holder_ref_impl;

struct holder
{
    holder();

    /**
     * @brief Assumes its shared ownership.
     *
     * @param impl
     */
    holder(holder_impl_base * impl);

    holder(const holder& o);

    holder& operator=(const holder& o);

    template< typename Value >
    Value& to_value();
    
protected:    

    holder_impl_ptr m_impl;
};


} // namespace core
} // namespace metasim

#endif /* METASIM_HOLDER_HPP */

