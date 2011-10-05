// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * helper.hpp
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

#ifndef CORBASIM_JSON_HELPER_HPP
#define CORBASIM_JSON_HELPER_HPP

#include <string>
#include <map>
#include <vector>
#include <deque>
#include <boost/shared_ptr.hpp>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>

namespace protobuf2json 
{
namespace json 
{
namespace helper 
{

struct helper_base
{
    virtual void new_double(double d)
    {
        throw "Error!";
    }

    virtual void new_string(const std::string& d)
    {
        throw "Error!";
    }

    virtual void new_bool(bool d)
    {
        throw "Error!";
    }

    // For structs
    virtual helper_base* new_child(const std::string& name)
    {
        throw "Error!";
    }

    // For arrays
    virtual helper_base* new_child()
    {
        throw "Error!";
    }

    virtual ~helper_base() {}

protected:
    helper_base() {}
};

struct field_helper : public helper_base
{
    google::protobuf::Message& m_msg;
    const google::protobuf::FieldDescriptor * m_descriptor;


    field_helper(google::protobuf::Message& msg,
            const google::protobuf::FieldDescriptor * desc) :
        m_msg(msg), m_descriptor(desc)
    {
    }

    void new_string(const std::string& d)
    {
        // TODO check desc type
        m_msg.GetReflection()->SetString(&m_msg, m_descriptor, d);
    }
};

/* TODO
struct repeated_helper : public helper_base
{
    ...
};
*/

struct message_helper : public helper_base
{
    google::protobuf::Message& m_msg;

    message_helper(google::protobuf::Message& msg) :
        m_msg(msg)
    {
    }

    helper_base* new_child(const std::string& name)
    {
        namespace pb = google::protobuf;

        const pb::FieldDescriptor * child_desc = 
            m_msg.GetDescriptor()->FindFieldByName(name);

        if (!child_desc)
            throw "Error!";

        if (child_desc->label() == pb::FieldDescriptor::LABEL_REPEATED)
            throw "Error!";

        return new field_helper(m_msg, child_desc);
    }
};

template < typename Message >
helper_base * create_helper(Message& m)
{
    return new message_helper(m);
}

} // namespace helper
} // namespace json
} // namespace protobuf2json

#endif /* CORBASIM_JSON_HELPER_HPP */

