// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * json_writer.hpp
 * Copyright (C) Cátedra SAES-UMU 2010 <catedra-saes-umu@listas.um.es>
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

#ifndef CORBASIM_JSON_IMPL_JSON_WRITER_HPP
#define CORBASIM_JSON_IMPL_JSON_WRITER_HPP

#include <string>
#include <deque>
#include <exception> // Exceptions
#include <stdexcept>
#include <protosim/json/detail/json.hpp>

namespace csu
{
namespace protosim
{
namespace json
{
namespace writer
{

struct binary_blob_emitter
{
    template<typename Ostream>
    static void new_blob_to_ostream (Ostream& os, match_pair const& p)
    {
        os.write((const char*)&(p.second),sizeof(size_t));
        os.write(p.first, p.second);
    }
};


// States
enum State
{
    BEGIN,
    END,

    IN_OBJECT_AWAIT_ID,
    IN_OBJECT_AWAIT_VALUE,

    IN_ARRAY_AWAIT_VALUE
};


// JSON semantic state
template <typename Ostream, typename BlobEmitter = binary_blob_emitter >
class json_writer
{
    struct state_struct
    {
        State s;
        bool first_in_object_or_array;
    };
    std::deque<state_struct> state_stack;

public:
    json_writer (Ostream& o) : o_ (o), level(0)
    {
        state_struct ss = { BEGIN, false };
        state_stack.push_back (ss);
    }

    inline void new_null()
    {
        _check_pre();

        o_ << "null";

        _check_post();
    }

    inline void new_double(double d)
    {
        _check_pre();

        // TODO: optimize
        o_ << d;

        _check_post();
    }

    // TODO: escape chars
    inline void new_string(match_pair  const& p)
    {
        _check_pre();

        o_ << '"';
        o_.write(p.first, p.second);
        o_ << '"';

        _check_post();
    }

    // Overload for ASCIIZ. This allows not having to pre-calculate
    // the string size for C strings.
    // TODO: escape chars
    inline void new_string (const char* s)
    {
        _check_pre();

        o_ << '"' << s << '"';

        _check_post();
    }

    inline void new_bool(bool b)
    {
        _check_pre();

        o_ << (b ? "true" : "false");

        _check_post();
    }

    inline void new_blob(match_pair const& p)
    {
        _check_pre();

        o_ << '@';
        BlobEmitter::template new_blob_to_ostream<Ostream>(o_, p);
        o_ << '@';

        _check_post();
    }

    inline void object_start()
    {
        _check_pre();

        state_struct ss = { IN_OBJECT_AWAIT_ID, true };
        state_stack.push_back (ss);

        o_ << "{";
        ++level;
        _indent();
    }

    inline void object_end()
    {
        state_stack.pop_back();

        --level;

        _indent();
        o_ << "}";

        _check_post();
    }

    inline void array_start()
    {
        _check_pre();

        state_struct ss  = { IN_ARRAY_AWAIT_VALUE, true};
        state_stack.push_back (ss);

        o_ << "[";
        ++level;
        _indent();
    }

    inline void array_end()
    {
        state_stack.pop_back();

        --level;

        _indent();
        o_ << "]";

        _check_post();
    }

    inline Ostream& ostream()
    {
        _check_pre();
        _check_post();
        return o_;
    }

private:

    inline void _indent()
    {
#if 0
        o_ << '\n';
        for (int i = 0; i < level; i++) 
            o_<< "    ";
#endif
    }

    inline void _check_pre()
    {
        state_struct& ss = state_stack.back();
        if (ss.s == IN_OBJECT_AWAIT_ID ||
            ss.s == IN_ARRAY_AWAIT_VALUE)
        {
            if (!ss.first_in_object_or_array)
            {
                o_ << ",";

                _indent();
            }
            else
                ss.first_in_object_or_array = false;
        }
        else if (ss.s == IN_OBJECT_AWAIT_VALUE)
        {
            // Output the ":"
            o_ << ":";
#if 0
            o_ << ' ';
#endif
        }
    }

    inline void _check_post()
    {
        state_struct& ss = state_stack.back();
        if (ss.s == IN_OBJECT_AWAIT_VALUE)
            ss.s = IN_OBJECT_AWAIT_ID;
        else if (ss.s == IN_OBJECT_AWAIT_ID)
            ss.s = IN_OBJECT_AWAIT_VALUE;
    }

    Ostream& o_;
    int level;
};


} // writer
} // json
} // mycorba
} // csu


#endif
