// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * reflective.hpp
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

#ifndef METASIM_CORE_REFLECTIVE_HPP
#define METASIM_CORE_REFLECTIVE_HPP

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
namespace core 
{
namespace detail
{

template< typename T >
struct bool_reflective : public reflective_base
{
    bool_reflective(reflective_base const * parent = NULL, 
            unsigned int idx = 0);
    
    bool is_primitive() const;
    
    holder create_holder() const;

    reflective_type get_type() const;
    
    void copy(holder const& src, holder& dst) const;
};

template< typename T >
struct primitive_reflective : public reflective_base
{
    primitive_reflective(reflective_base const * parent = NULL, 
            unsigned int idx = 0);

    bool is_primitive() const;

    reflective_type get_type() const;
    
    holder create_holder() const;
    
    void copy(holder const& src, holder& dst) const;
};

template< typename T >
struct array_reflective : public reflective_base
{
    typedef typename boost::remove_bounds < T >::type slice_t;
    typedef reflective < slice_t > slice_reflective_t;

    static const size_t size = sizeof(T) / sizeof(slice_t);

    array_reflective(reflective_base const * parent = NULL, 
            unsigned int idx = 0);

    bool is_repeated() const;

    reflective_base const * get_slice() const;

    reflective_type get_type() const;

    // Dynamic information

    holder create_holder() const;

    unsigned int get_length(holder const& value) const;

    holder get_child_value(holder& value, unsigned int idx) const;

    void copy(holder const& src, holder& dst) const;

    slice_reflective_t m_slice;
};

template< typename T >
struct std_string_reflective : public reflective_base
{
    std_string_reflective(reflective_base const * parent = NULL,
            unsigned int idx = 0);

    bool is_variable_length() const;

    bool is_primitive() const;

    reflective_type get_type() const;

    holder create_holder() const;

    std::string to_string(holder const& h) const;

    void from_string(holder& h, const std::string& str) const;
    
    void copy(holder const& src, holder& dst) const;
};

template< typename T >
struct std_vector_reflective : public reflective_base
{
    typedef typename T::value_type slice_t;
    // typedef reflective < slice_t > slice_reflective_t;

    std_vector_reflective(reflective_base const * parent = NULL,
            unsigned int idx = 0);
    
    ~std_vector_reflective();

    bool is_repeated() const;
    bool is_variable_length() const;
    
    reflective_type get_type() const;

    reflective_base const * get_slice() const;

    // Dynamic information
    holder create_holder() const;

    unsigned int get_length(holder const& value) const;

    void set_length(holder& value, unsigned int length) const;

    holder get_child_value(holder& value, 
        unsigned int idx) const;

    void copy(holder const& src, holder& dst) const;

    reflective_base const * m_slice;
};

typedef std::vector< reflective_ptr > reflective_children;

struct METASIM_CORE_DECLSPEC accessor_base
{
    virtual holder get(holder& parent) const = 0;
    virtual ~accessor_base();
};

typedef boost::shared_ptr< accessor_base > accessor_ptr;

template< typename T >
struct struct_reflective : public reflective_base
{
    static const std::size_t members_count = 
        boost::fusion::result_of::size< T >::value;
    typedef boost::mpl::range_c< size_t, 0, members_count > 
        members_range_t;

    struct_reflective(reflective_base const * parent = NULL, 
            unsigned int idx = 0);

    unsigned int get_children_count() const;

    const char * get_child_name(unsigned int idx) const;
    
    reflective_base const * get_child(unsigned int idx) const;

    reflective_type get_type() const;

    // Dynamic information
    holder create_holder() const;

    holder get_child_value(holder& value, 
        unsigned int idx) const;

    void copy(holder const& src, holder& dst) const;

    static struct_reflective const * get_instance();

    // Data
    reflective_children m_children;
    std::vector< const char * > m_child_names;
    std::vector< accessor_ptr > m_accessors;
};

template< typename T >
struct enum_reflective : public reflective_base
{
    typedef adapted::enumeration< T > adapted_t;

    enum_reflective(reflective_base const * parent = NULL, 
            unsigned int idx = 0);

    bool is_enum() const;

    reflective_type get_type() const;

    unsigned int get_children_count() const;

    const char * get_child_name(unsigned int idx) const;

    holder create_holder() const;

    void copy(holder const& src, holder& dst) const;
};

template< typename T >
struct unsupported_type : public reflective_base
{
    unsupported_type(reflective_base const * parent = NULL, 
            unsigned int idx = 0);
};

/**
 * @brief Calculates the reflective type for a type Y based on a type T.
 *
 * @tparam T A basic C++ type.
 * @tparam Y Must have the same basic usage than T.
 */
template< typename T, typename Y = T>
struct calculate_reflective
{
    typedef typename 
        // if
        boost::mpl::eval_if< boost::is_arithmetic< T >, 
            boost::mpl::identity< primitive_reflective< Y > >,
        // else if
        boost::mpl::eval_if< boost::is_enum< T >, 
            boost::mpl::identity< enum_reflective< Y > >,
        // else if
        boost::mpl::eval_if< boost::is_class< T >, 
            boost::mpl::identity< struct_reflective< Y > >,
        // else
            boost::mpl::identity< unsupported_type< Y > >
        > > >::type type;
};

template< typename Y >
struct calculate_reflective< bool, Y >
{
    typedef bool_reflective< Y > type;
};

template< typename T, typename Y, unsigned int N >
struct calculate_reflective< T[N], Y >
{
    typedef array_reflective< Y > type;
};

template< typename Y >
struct calculate_reflective< std::string, Y >
{
    typedef std_string_reflective< Y > type;
};

template< typename T, typename Y >
struct calculate_reflective< std::vector< T >, Y >
{
    typedef std_vector_reflective< Y > type;
};

} // namespace detail

template < typename T >
struct reflective : public detail::calculate_reflective< T >::type
{
    typedef typename detail::calculate_reflective< T >::type base_t;

    reflective(reflective_base const * parent = NULL,
            unsigned int idx = 0) : base_t(parent, idx) 
    {}
};

} // namespace core
} // namespace metasim

#endif /* METASIM_CORE_REFLECTIVE_HPP */

