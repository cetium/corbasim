// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * reflective_fwd.hpp
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

#ifndef METASIM_CORE_REFLECTIVE_FWD_HPP
#define METASIM_CORE_REFLECTIVE_FWD_HPP

#include <metasim/core/export.hpp>

#include <string>
#include <vector>
#include <map>
#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>
#include <metasim/core/holder.hpp>

namespace metasim 
{
namespace core 
{

enum reflective_type
{
    TYPE_INVALID,

    TYPE_BOOL,
    TYPE_ENUM,
    TYPE_CHAR,
    TYPE_INT8 = TYPE_CHAR,
    TYPE_UINT8,
    TYPE_INT16,
    TYPE_UINT16,
    TYPE_INT32,
    TYPE_UINT32,
    TYPE_INT64,
    TYPE_UINT64,
    TYPE_FLOAT,
    TYPE_DOUBLE,

    TYPE_STRING,
    TYPE_WCHAR,
    TYPE_WSTRING,
    TYPE_STRUCT,
    TYPE_ARRAY,
    TYPE_UNION,
    TYPE_MAP,
    TYPE_VECTOR,
    TYPE_LIST
};

struct METASIM_CORE_DECLSPEC reflective_base
{
    virtual ~reflective_base();

    virtual const char * get_type_name() const;

    // Relative to its parent
    reflective_base const * get_parent() const;
    unsigned int get_child_index() const;

    virtual unsigned int get_children_count() const;
    virtual const char * get_child_name(unsigned int idx) const;
    virtual reflective_base const * get_child(unsigned int idx) const;

    virtual bool is_repeated() const;
    virtual bool is_variable_length() const;
    virtual bool is_primitive() const;
    virtual bool is_enum() const;

    virtual reflective_type get_type() const;

    // Requires is_repeated or is_enum
    virtual reflective_base const * get_slice() const;

    virtual holder create_holder() const;

    // dynamic information
    virtual unsigned int get_length(holder const& value) const;
    virtual void set_length(holder& value, unsigned int length) const;

    virtual holder get_child_value(holder& value, 
        unsigned int idx) const;
    
    // String types
    virtual std::string to_string(holder const& h) const;
    virtual void from_string(holder& h, const std::string& str) const;

    // All types
    virtual void copy(holder const& src, holder& dst) const;

protected:

    reflective_base(reflective_base const * parent = NULL, 
            unsigned int child_index = 0);

    reflective_base const * m_parent;
    unsigned int m_child_index;
};

typedef boost::shared_ptr< reflective_base > reflective_ptr;

template< typename T >
struct reflective;

struct METASIM_CORE_DECLSPEC reflective_group_base
{
    reflective_group_base();
    virtual ~reflective_group_base();

    unsigned int get_reflective_count() const;
    reflective_base const * get_reflective_by_name(
            const std::string& name) const;
    reflective_base const * get_reflective_by_index(unsigned int idx) const;
    reflective_base const * get_reflective_by_tag(tag_t tag) const;

    void insert_reflective(const std::string& name,
        tag_t tag, reflective_base const * reflective);

    template< typename T >
    void insert_type(const std::string& name)
    {
        insert_reflective(name, tag< T >::value(), 
                reflective< T >::get_instance());
    }

protected:

    // Data
    typedef std::vector< reflective_base const * > 
        reflectives_t;
    reflectives_t m_reflectives;

    typedef std::map< std::string, reflective_base const * > 
        reflectives_by_name_t;
    reflectives_by_name_t m_reflectives_by_name;

    typedef std::map< tag_t, reflective_base const * > 
        reflectives_by_tag_t;
    reflectives_by_tag_t m_reflectives_by_tag;
};

struct METASIM_CORE_DECLSPEC instance_base
{
    instance_base(const std::string& name,
            reflective_group_base const * reflective);
    virtual ~instance_base();

    const std::string& get_name() const;
    reflective_group_base const * get_reflective() const;

protected:

    const std::string m_name;
    reflective_group_base const * m_reflective;
};

typedef boost::shared_ptr< instance_base * > instance_ptr;

} // namespace core
} // namespace metasim

#endif /* METASIM_CORE_REFLECTIVE_FWD_HPP */

