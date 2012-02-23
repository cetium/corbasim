// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * adapted.hpp
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

#ifndef METASIM_CORE_ADAPTED_HPP
#define METASIM_CORE_ADAPTED_HPP

#include <metasim/core/reflective_fwd.hpp>

#include <string>
#include <vector>
#include <list>
#include <map>

#include <boost/cstdint.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/for_each.hpp> // run-time foreach
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/range_c.hpp>

#include <boost/fusion/sequence/intrinsic.hpp>

#include <boost/fusion/mpl.hpp>
#include <boost/fusion/adapted.hpp> // BOOST_FUSION_ADAPT_STRUCT

#include <metasim/core/adapted.hpp>

namespace metasim 
{
namespace adapted 
{

template< typename T >
struct enumeration;

} // namespace adapte
} // namespace metasim

#endif /* METASIM_CORE_ADAPTED_HPP */

