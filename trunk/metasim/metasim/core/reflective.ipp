// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * reflective_primitive.ipp
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
#ifndef METASIM_CORE_REFLECTIVE_IPP
#define METASIM_CORE_REFLECTIVE_IPP

namespace metasim 
{
namespace core 
{

template< typename Value >
Value& holder::to_value()
{
    typedef holder_ref_impl< Value > value_impl;

    value_impl * p = reinterpret_cast< value_impl * >(
            m_impl.get());

    return p->t_;
}

template< typename T >
struct holder_ref_impl : public holder_impl_base
{
    typedef T value_type;

    T aux;
    T& t_;

    holder_ref_impl() : 
        t_(aux)
    {
    }

    holder_ref_impl(T& t) : 
        t_(t)
    {
    }

    // String sequence case
    holder_ref_impl(const T& t) : 
        aux(t), t_(aux)
    {
    }

    ~holder_ref_impl()
    {
    }

    tag_t get_tag() const
    {
        return tag< T >::value();
    }
};

template < typename T >
holder_impl_base * create_holder(T& t)
{
    return new holder_ref_impl< T >(t);
}

template < typename T >
holder_impl_base * create_holder(const T& t)
{
    return new holder_ref_impl< T >(t);
}

namespace detail 
{

// Array reflective

template< typename T >
array_reflective< T >::array_reflective(reflective_base const * parent, 
        unsigned int idx) :
    reflective_base(parent, idx), m_slice(this, 0)
{
}

template< typename T >
bool array_reflective< T >::is_repeated() const { return true; }

template< typename T >
reflective_base const * array_reflective< T >::get_slice() const
{
    return &m_slice;
}

template< typename T >
reflective_type array_reflective< T >::get_type() const
{
    return TYPE_ARRAY;
}

// Dynamic information

template< typename T >
holder array_reflective< T >::create_holder() const
{
    return new holder_ref_impl< T >();
}

template< typename T >
unsigned int array_reflective< T >::get_length(holder const& value) const
{
    return size;
}

template< typename T >
holder array_reflective< T >::get_child_value(holder& value, 
    unsigned int idx) const
{
    return holder( ::metasim::core::create_holder(value.to_value< T >()[idx]));
}

template< typename T >
void array_reflective< T >::copy(holder const& src, holder& dst) const
{
    for (unsigned i = 0; i < size; i++) 
    {
        holder child_src = get_child_value(const_cast< holder& >(src), i);
        holder child_dst = get_child_value(dst, i);
        m_slice.copy(child_src, child_dst);
    }
}

// String reflective
template< typename T >
std_string_reflective< T >::std_string_reflective(reflective_base const * parent,
        unsigned int idx) :
    reflective_base(parent, idx)
{
}

template< typename T >
bool std_string_reflective< T >::is_variable_length() const { return true; }

template< typename T >
bool std_string_reflective< T >::is_primitive() const       { return true; }

template< typename T >
reflective_type std_string_reflective< T >::get_type() const
{
    return TYPE_STRING;
}

template< typename T >
holder std_string_reflective< T >::create_holder() const
{
    return new holder_ref_impl< T >();
}

template< typename T >
std::string std_string_reflective< T >::to_string(holder const& value) const
{
    return std::string(const_cast< holder& >(value).to_value< T >());
}

template< typename T >
void std_string_reflective< T >::from_string(holder& value, const std::string& str) const
{
    value.to_value< T >() = str.c_str();
}

template< typename T >
void std_string_reflective< T >::copy(holder const& src, holder& dst) const
{
    dst.to_value< T >() = const_cast< holder& >(src).to_value< T >();
}

// Sequence reflective
template< typename T >
std_vector_reflective< T >::std_vector_reflective(reflective_base const * parent,
        unsigned int idx) :
    reflective_base(parent, idx), m_slice(this, 0)
{
}

template< typename T >
std_vector_reflective< T >::~std_vector_reflective()
{
}

template< typename T >
bool std_vector_reflective< T >::is_repeated() const        { return true; }

template< typename T >
bool std_vector_reflective< T >::is_variable_length() const { return true; }

template< typename T >
reflective_type std_vector_reflective< T >::get_type() const
{
    return TYPE_VECTOR;
}

template< typename T >
reflective_base const * std_vector_reflective< T >::get_slice() const
{
    return &m_slice;
}

// Dynamic information
template< typename T >
holder std_vector_reflective< T >::create_holder() const
{
    return new holder_ref_impl< T >();
}

template< typename T >
unsigned int std_vector_reflective< T >::get_length(holder const& value) const
{
    return const_cast< holder& >(value).to_value< T >().size();
}

template< typename T >
void std_vector_reflective< T >::set_length(holder& value, 
        unsigned int length) const
{
    return value.to_value< T >().resize(length);
}

template< typename T >
holder std_vector_reflective< T >::get_child_value(holder& value, 
    unsigned int idx) const
{
    return holder( ::metasim::core::create_holder(value.to_value< T >()[idx]));
}

template< typename T >
void std_vector_reflective< T >::copy(holder const& src, holder& dst) const
{
    unsigned int length = get_length(src);
    set_length(dst, length);

    for (unsigned i = 0; i < length; i++) 
    {
        holder child_src = get_child_value(const_cast< holder& >(src), i);
        holder child_dst = get_child_value(dst, i);
        m_slice.copy(child_src, child_dst);
    }
}

// Struct reflective
template< typename S, typename N >
struct accessor : public accessor_base
{
    holder get(holder& parent) const
    {
        return holder( ::metasim::core::create_holder(
                    boost::fusion::at < N >(parent.to_value< S >())));
    }
};

template < typename S, typename Reflective >
struct create_iterator
{
    Reflective * m_this;

    create_iterator(Reflective * _this) : 
        m_this(_this)
    {}

    template < typename N >
    void operator()(N const& nn)
    {
        // Tipo del campo actual
        typedef typename boost::fusion::result_of::value_at< S, N >::type 
			current_t;

        // Tipo que contiene el nombre del campo actual
        typedef boost::fusion::extension::struct_member_name< S, N::value > 
			name_t;

        typedef reflective< current_t > reflective_t;

        reflective_ptr ptr_(new reflective_t(m_this, N::value));
        accessor_ptr ac_(new accessor< S, N >());

        m_this->m_children.push_back(ptr_);
        m_this->m_child_names.push_back(name_t::call());
        m_this->m_accessors.push_back(ac_);
    }
};

template< typename T >
struct_reflective< T >::struct_reflective(reflective_base const * parent, 
        unsigned int idx) :
    reflective_base(parent, idx)
{
    // Reserve
    m_children.reserve(members_count);
    m_child_names.reserve(members_count);
    m_accessors.reserve(members_count);

    // Iterate
    create_iterator< T, struct_reflective > it(this);
    boost::mpl::for_each< members_range_t >(it);
}

template< typename T >
unsigned int struct_reflective< T >::get_children_count() const 
{ 
    return members_count;
}

template< typename T >
const char * struct_reflective< T >::get_child_name(unsigned int idx) const 
{
    return m_child_names[idx];
}

template< typename T >
reflective_base const * struct_reflective< T >::get_child(
        unsigned int idx) const
{
    return m_children[idx].get();
}

template< typename T >
reflective_type struct_reflective< T >::get_type() const
{
    return TYPE_STRUCT;
}

template< typename T >
void struct_reflective< T >::copy(holder const& src, holder& dst) const
{
    for (unsigned i = 0; i < members_count; i++) 
    {
        holder child_src = get_child_value(const_cast< holder& >(src), i);
        holder child_dst = get_child_value(dst, i);
        get_child(i)->copy(child_src, child_dst);
    }
}

// Dynamic information
template< typename T >
holder struct_reflective< T >::create_holder() const
{
    return new holder_ref_impl< T >();
}

template< typename T >
holder struct_reflective< T >::get_child_value(holder& value, 
    unsigned int idx) const
{
    return m_accessors[idx]->get(value);
}

template< typename T >
struct_reflective< T > const * struct_reflective< T >::get_instance()
{
    static boost::shared_ptr< struct_reflective > _instance(
            new struct_reflective);

    return _instance.get();
}

// Enum reflective
template< typename T >
enum_reflective< T >::enum_reflective(reflective_base const * parent,
        unsigned int idx) :
    reflective_base(parent, idx)
{
}

template< typename T >
bool enum_reflective< T >::is_enum() const
{
    return true;
}

template< typename T >
reflective_type enum_reflective< T >::get_type() const
{
    return TYPE_ENUM;
}

template< typename T >
unsigned int enum_reflective< T >::get_children_count() const
{
    return adapted_t::size;
}

template< typename T >
const char * enum_reflective< T >::get_child_name(unsigned int idx) const
{
    return adapted_t::values()[idx];
}

template< typename T >
holder enum_reflective< T >::create_holder() const
{
    return new holder_ref_impl< T >();
}

template< typename T >
void enum_reflective< T >::copy(holder const& src, holder& dst) const
{
    dst.to_value< T >() = const_cast< holder& >(src).to_value< T >();
}

// Unsupported type
template< typename T >
unsupported_type< T >::unsupported_type(reflective_base const * parent, 
        unsigned int idx) :
    reflective_base(parent, idx)
{
}

} // namespace detail
} // namespace core
} // namespace metasim

#endif /* METASIM_CORE_REFLECTIVE_IPP */

