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

    void new_bool(bool b)
    {
        m_msg.GetReflection()->SetBool(&m_msg, m_descriptor, b);
    }

    void new_double(double d)
    {
        namespace pb = google::protobuf;

        switch(m_descriptor->cpp_type())
        {
            case pb::FieldDescriptor::CPPTYPE_DOUBLE:
                m_msg.GetReflection()->SetDouble(&m_msg, m_descriptor, d);
                break;
            case pb::FieldDescriptor::CPPTYPE_FLOAT:
                m_msg.GetReflection()->SetFloat(&m_msg, m_descriptor, d);
                break;
            // TODO integer types...
            default:
                throw "Error!";
        }
    }

    void new_string(const std::string& d)
    {
        namespace pb = google::protobuf;

        // TODO check desc type
        // enums here too, as strings
        if (m_descriptor->type() == pb::FieldDescriptor::TYPE_ENUM)
        {
            const pb::EnumDescriptor * desc = m_descriptor->enum_type();
            if (!desc)
                throw "Error!";

            const pb::EnumValueDescriptor * value = desc->FindValueByName(d);
            if (!value)
                throw "Error!";

            m_msg.GetReflection()->SetEnum(&m_msg, m_descriptor, value);
        }
        else
            m_msg.GetReflection()->SetString(&m_msg, m_descriptor, d);
    }
};

struct repeated_helper : public helper_base
{
    google::protobuf::Message& m_msg;
    const google::protobuf::FieldDescriptor * m_descriptor;


    repeated_helper(google::protobuf::Message& msg,
            const google::protobuf::FieldDescriptor * desc) :
        m_msg(msg), m_descriptor(desc)
    {
    }

    void new_bool(bool b)
    {
        m_msg.GetReflection()->AddBool(&m_msg, m_descriptor, b);
    }

    void new_double(double d)
    {
        namespace pb = google::protobuf;

        switch(m_descriptor->cpp_type())
        {
            case pb::FieldDescriptor::CPPTYPE_DOUBLE:
                m_msg.GetReflection()->AddDouble(&m_msg, m_descriptor, d);
                break;
            case pb::FieldDescriptor::CPPTYPE_FLOAT:
                m_msg.GetReflection()->AddFloat(&m_msg, m_descriptor, d);
                break;
            // TODO integer types...
            default:
                throw "Error!";
        }
    }

    void new_string(const std::string& d)
    {
        namespace pb = google::protobuf;
        
        // TODO check desc type
        // enums here too, as strings
        if (m_descriptor->type() == pb::FieldDescriptor::TYPE_ENUM)
        {
            const pb::EnumDescriptor * desc = m_descriptor->enum_type();
            if (!desc)
                throw "Error!";

            const pb::EnumValueDescriptor * value = desc->FindValueByName(d);
            if (!value)
                throw "Error!";

            m_msg.GetReflection()->AddEnum(&m_msg, m_descriptor, value);
        }
        else
            m_msg.GetReflection()->AddString(&m_msg, m_descriptor, d);
    }

    helper_base* new_child();
};

struct message_helper : public helper_base
{
    google::protobuf::Message* m_msg;

    message_helper(google::protobuf::Message* msg) :
        m_msg(msg)
    {
    }

    helper_base* new_child(const std::string& name)
    {
        namespace pb = google::protobuf;

        const pb::FieldDescriptor * child_desc = 
            m_msg->GetDescriptor()->FindFieldByName(name);

        if (!child_desc)
            throw "Error!";

        if (child_desc->is_repeated())
            return new repeated_helper(*m_msg, child_desc);

        if (child_desc->type() == pb::FieldDescriptor::TYPE_MESSAGE)
            return new message_helper(
                m_msg->GetReflection()->MutableMessage(m_msg, child_desc));

        return new field_helper(*m_msg, child_desc);
    }

    template< typename Writer >
    static inline void write(Writer& w, 
            const google::protobuf::Message * msg)
    {
        namespace pb = google::protobuf;
        double d = 0.0;
        std::string str;

        w.object_start();

        const pb::Descriptor * desc = msg->GetDescriptor();
        const pb::Reflection * reflection = msg->GetReflection();
        int count = desc->field_count();

        for (int i = 0; i < count; i++) 
        {
            const pb::FieldDescriptor * field = desc->field(i);

            w.new_string(field->name().c_str());

            if (field->is_repeated())
            {
                w.array_start();
                int times = reflection->FieldSize(*msg, field);

                for (int j = 0; j < times; j++) 
                {
                    switch(field->cpp_type())
                    {
                        case pb::FieldDescriptor::CPPTYPE_MESSAGE:
                            {
                                const pb::Message& child_msg = 
                                    reflection->GetRepeatedMessage(*msg, field, j);
                                write(w, &child_msg);
                            }
                            break;
                        case pb::FieldDescriptor::CPPTYPE_DOUBLE:
                            d = reflection->GetRepeatedDouble(*msg, field, j);
                            w.new_double(d);
                            break;
                        case pb::FieldDescriptor::CPPTYPE_STRING:
                            str = reflection->GetRepeatedString(*msg, field, j);
                            w.new_string(str.c_str());
                            break;
                        default:
                            w.new_string("TODO");
                            break;
                    }
                }

                w.array_end();
            }
            else if (!(field->is_optional() && !reflection->HasField(*msg, field)))
            {
                switch(field->cpp_type())
                {
                    case pb::FieldDescriptor::CPPTYPE_MESSAGE:
                        {
                            const pb::Message& child_msg = 
                                reflection->GetMessage(*msg, field);
                            write(w, &child_msg);
                        }
                        break;
                    case pb::FieldDescriptor::CPPTYPE_DOUBLE:
                        d = reflection->GetDouble(*msg, field);
                        w.new_double(d);
                        break;
                    case pb::FieldDescriptor::CPPTYPE_STRING:
                        str = reflection->GetString(*msg, field);
                        w.new_string(str.c_str());
                        break;
                    default:
                        w.new_string("TODO");
                        break;
                }
            }
        }

        w.object_end();
    }
};

helper_base * repeated_helper::new_child()
{
    namespace pb = google::protobuf;

    if (m_descriptor->type() == pb::FieldDescriptor::TYPE_MESSAGE)
        return new message_helper(
            m_msg.GetReflection()->AddMessage(&m_msg, m_descriptor));

    return new repeated_helper(m_msg, m_descriptor);
}

template < typename Message >
helper_base * create_helper(Message& m)
{
    return new message_helper(&m);
}

} // namespace helper
} // namespace json
} // namespace protobuf2json

#endif /* CORBASIM_JSON_HELPER_HPP */

