// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * parser.hpp
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

#ifndef CORBASIM_JSON_PARSER_HPP
#define CORBASIM_JSON_PARSER_HPP

#include <list>
#include <boost/shared_ptr.hpp>
#include <protobuf2json/json/helper.hpp>
#include <protobuf2json/json/detail/json.hpp>
#include <protobuf2json/json/detail/json_parse.hpp>
#include <protobuf2json/json/detail/json_writer.hpp>

#include <iostream>
#include <string>

namespace protobuf2json 
{
namespace json 
{

struct semantic_state
{
    typedef csu::protobuf2json::json::match_pair match_pair;
    typedef boost::shared_ptr< helper::helper_base > helper_ptr;
    std::list< helper_ptr > m_helpers_stack;

    struct state_struct
    {
        csu::protobuf2json::json::writer::State s;
        bool first_in_object_or_array;
    };
    std::list<state_struct> state_stack;

    semantic_state(helper::helper_base * initial_helper)
    {
        m_helpers_stack.push_back(helper_ptr(initial_helper));

        state_struct ss;
        ss.s = csu::protobuf2json::json::writer::BEGIN;
        ss.first_in_object_or_array = false;
        state_stack.push_back(ss);
    }

    inline void new_null()
    {
        _check_pre();
        //std::cout << "new null" << std::endl;
        _check_post();
    }

    inline void new_double(double d)
    {
        _check_pre();
        std::cout << "new double: " << d << std::endl;

        m_helpers_stack.back()->new_double(d);
        _consume();

        _check_post();
    }

    inline void new_string(match_pair  const& p)
    {
        namespace w = csu::protobuf2json::json::writer;

        std::string val(p.first, p.second);

        _check_pre();
        std::cout << "new string: " << val <<  std::endl;

        if (state_stack.back().s != w::IN_OBJECT_AWAIT_ID)
        {
            m_helpers_stack.back()->new_string(val);
            _consume();
        }
        else 
        {
            helper_ptr parent = m_helpers_stack.back();
            m_helpers_stack.push_back(helper_ptr(parent->new_child(val)));
        }

        _check_post();
    }

    inline void new_bool(bool b)
    {
        _check_pre();
        std::cout << "new bool: " << b << std::endl;
        
        m_helpers_stack.back()->new_bool(b);
        _consume();

        _check_post();
    }

    inline void new_blob(match_pair const& p)
    {
        _check_pre();
        //std::cout << "new blob, size: " << p.second << std::endl;
        _check_post();
    }

    inline void object_start()
    {
        namespace w = csu::protobuf2json::json::writer;

        //std::cout << "object start" << std::endl;
        
        _check_pre();

        state_struct ss;
        ss.s = w::IN_OBJECT_AWAIT_ID;
        ss.first_in_object_or_array = true;
        state_stack.push_back(ss);
    }

    inline void object_end()
    {
        //std::cout << "object end" << std::endl;
        
        state_stack.pop_back();
        _consume();
        _check_post();
    }

    inline void array_start()
    {
        namespace w = csu::protobuf2json::json::writer;

        //std::cout << "array start" << std::endl;
        
        _check_pre();

        state_struct ss;
        ss.s = w::IN_ARRAY_AWAIT_VALUE;
        ss.first_in_object_or_array = true;
        state_stack.push_back(ss);
    }

    inline void array_end()
    {
        //std::cout << "array end" << std::endl;
        
        state_stack.pop_back();
        _consume();
        _check_post();
    }

    inline void _check_pre()
    {
        namespace w = csu::protobuf2json::json::writer;

        state_struct& ss = state_stack.back();
        if (ss.s == w::IN_OBJECT_AWAIT_ID ||
                ss.s == w::IN_ARRAY_AWAIT_VALUE)
        {
            if (!ss.first_in_object_or_array)
                ;
            else
                ss.first_in_object_or_array = false;

            if (ss.s == w::IN_ARRAY_AWAIT_VALUE)
            {
                helper_ptr parent = m_helpers_stack.back();
                m_helpers_stack.push_back(helper_ptr(parent->new_child()));
            }
        }
        else if (ss.s == w::IN_OBJECT_AWAIT_VALUE)
        {
        }
    }

    inline void _check_post()
    {
        namespace w = csu::protobuf2json::json::writer;

        state_struct& ss = state_stack.back();
        if (ss.s == w::IN_OBJECT_AWAIT_VALUE)
            ss.s = w::IN_OBJECT_AWAIT_ID;
        else if (ss.s == w::IN_OBJECT_AWAIT_ID)
            ss.s = w::IN_OBJECT_AWAIT_VALUE;
    }

    inline void _consume()
    {
        m_helpers_stack.pop_back();
    }
};

typedef csu::protobuf2json::json::parser::State< semantic_state > state;

template< typename T >
inline bool parse(T& t, const char * str, size_t size)
{
    helper::helper_base * initial_helper = helper::create_helper(t);
    semantic_state _ss(initial_helper);
    state _st(_ss, str, size);

    return csu::protobuf2json::json::parser::grammar::gram::match(_st);
}

template< typename T >
inline bool parse(T& t, const std::string& str)
{
    return parse(t, str.c_str(), str.length());
}

} // namespace json
} // namespace protobuf2json

#endif /* CORBASIM_JSON_PARSER_HPP */

