// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * reflective.cpp
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
#include "reflective.ipp"
#include "reflective_primitive.ipp"

namespace metasim 
{
namespace core 
{

template METASIM_CORE_DECLSPEC bool& holder::to_value< bool >();
template METASIM_CORE_DECLSPEC short& holder::to_value< short >();
template METASIM_CORE_DECLSPEC unsigned short& holder::to_value< unsigned short >();
template METASIM_CORE_DECLSPEC char& holder::to_value< char >();
template METASIM_CORE_DECLSPEC unsigned char& holder::to_value< unsigned char >();
template METASIM_CORE_DECLSPEC int32_t& holder::to_value< int32_t >();
template METASIM_CORE_DECLSPEC uint32_t& holder::to_value< uint32_t >();
template METASIM_CORE_DECLSPEC uint64_t& holder::to_value< uint64_t >();
template METASIM_CORE_DECLSPEC int64_t& holder::to_value< int64_t >();
template METASIM_CORE_DECLSPEC float& holder::to_value< float >();
template METASIM_CORE_DECLSPEC double& holder::to_value< double >();
template METASIM_CORE_DECLSPEC std::string& holder::to_value< std::string >();

namespace detail 
{

template class METASIM_CORE_DECLSPEC bool_reflective< bool >;
template class METASIM_CORE_DECLSPEC primitive_reflective< short >;
template class METASIM_CORE_DECLSPEC primitive_reflective< unsigned short >;
template class METASIM_CORE_DECLSPEC primitive_reflective< char >;
template class METASIM_CORE_DECLSPEC primitive_reflective< unsigned char >;
template class METASIM_CORE_DECLSPEC primitive_reflective< int32_t >;
template class METASIM_CORE_DECLSPEC primitive_reflective< uint32_t >;
template class METASIM_CORE_DECLSPEC primitive_reflective< uint64_t >;
template class METASIM_CORE_DECLSPEC primitive_reflective< int64_t >;
template class METASIM_CORE_DECLSPEC primitive_reflective< float >;
template class METASIM_CORE_DECLSPEC primitive_reflective< double >;
template class METASIM_CORE_DECLSPEC std_string_reflective< std::string >;

accessor_base::~accessor_base()
{
}

} // namespace detail
} // namespace core
} // namespace metasim

using namespace metasim::core;

holder_impl_base::~holder_impl_base()
{
}

// Holder
holder::holder()
{
}

holder::holder(holder_impl_base * impl) :
    m_impl(holder_impl_ptr(impl))
{
}

holder::holder(const holder& o) :
    m_impl(o.m_impl)
{
}

holder& holder::operator=(const holder& o)
{
    m_impl = o.m_impl;

    return *this;
}

tag_t holder::get_tag() const
{
    if (m_impl) return m_impl->get_tag();

    return (tag_t) 0;
}

// Reflective base

reflective_base::reflective_base(reflective_base const * parent,
        unsigned int child_index) : 
    m_parent(parent), m_child_index(child_index)
{
}

reflective_base::~reflective_base()
{
}

const char * reflective_base::get_type_name() const
{
    return "undefined";
}

reflective_base const * reflective_base::get_parent() const 
{ 
    return m_parent; 
}

unsigned int reflective_base::get_child_index() const 
{ 
    return m_child_index; 
}

unsigned int reflective_base::get_children_count() const 
{ 
    return 0; 
}

const char * reflective_base::get_child_name(unsigned int idx) const 
{ 
    return 0;
}

reflective_base const * reflective_base::get_child(unsigned int idx) const
{
    return 0;
}

bool reflective_base::is_repeated() const        { return false; }
bool reflective_base::is_variable_length() const { return false; }
bool reflective_base::is_primitive() const       { return false; }
bool reflective_base::is_enum() const            { return false; }

reflective_type reflective_base::get_type() const
{
    return TYPE_INVALID;
}

reflective_base const * reflective_base::get_slice() const
{
    return 0;
}

// Dynamic information

holder reflective_base::create_holder() const
{
    return holder();
}

unsigned int reflective_base::get_length(holder const& value) const
{
    return 0;
}

void reflective_base::set_length(holder& value, unsigned int length) const
{
}

holder reflective_base::get_child_value(holder& value, 
    unsigned int idx) const
{
    return holder();
}

std::string reflective_base::to_string(holder const& value) const
{
    return std::string();
}

void reflective_base::from_string(holder& value, 
        const std::string& str) const
{
}

void reflective_base::copy(holder const & src, holder& dst) const
{
}

// Reflective Group Base

void reflective_group_base::insert_reflective(
        const std::string& name,
        tag_t tag, reflective_base const * reflective)
{
    m_reflectives.push_back(reflective);

    // Maps
    m_reflectives_by_name.insert(std::make_pair(name, reflective));
    m_reflectives_by_tag.insert(std::make_pair(tag, reflective));
}

reflective_group_base::reflective_group_base()
{
}

reflective_group_base::~reflective_group_base()
{
}

unsigned int reflective_group_base::get_reflective_count() const
{
    return m_reflectives.size();
}

reflective_base const * 
reflective_group_base::get_reflective_by_index(
        unsigned int idx) const
{
    return m_reflectives[idx];
}

reflective_base const * 
reflective_group_base::get_reflective_by_name(
        const std::string& name) const
{
    reflectives_by_name_t::const_iterator it;
    it = m_reflectives_by_name.find(name);

    if (it != m_reflectives_by_name.end())
        return it->second;

    return NULL;
}

reflective_base const * 
reflective_group_base::get_reflective_by_tag(
        tag_t tag) const
{
    reflectives_by_tag_t::const_iterator it;
    it = m_reflectives_by_tag.find(tag);

    if (it != m_reflectives_by_tag.end())
        return it->second;

    return NULL;
}
instance_base::instance_base(const std::string& name,
        reflective_group_base const * reflective) :
    m_name(name), m_reflective(reflective)
{
}

instance_base::~instance_base()
{
}

const std::string& instance_base::get_name() const
{
    return m_name;
}

reflective_group_base const * instance_base::get_reflective() const
{
    return m_reflective;
}

