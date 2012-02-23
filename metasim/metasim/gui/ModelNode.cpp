// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ModelNode.cpp
 * Copyright (C) Cátedra SAES-UMU 2011 <catedra-saes-umu@listas.um.es>
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

#include "ModelNode.hpp"

using namespace metasim::gui;

Node::Node(core::reflective_base const * r,
        core::holder h, Node const * p, unsigned int idx) :
    reflective(r), holder(h), parent(p), index(idx), initialized(false)
{
}

void Node::initialize()
{
    if (reflective->is_repeated())
    {
        const unsigned int count = reflective->get_length(holder);
        children.reserve(count);

        core::reflective_base const * slice =
            reflective->get_slice();

        for (unsigned int i = 0; i < count; i++) 
        {
            Node_ptr child(new Node(slice, 
                    reflective->get_child_value(holder, i), this, i));

            children.push_back(child);
        }
    }
    else if(reflective->get_type() == core::TYPE_STRUCT)
    {
        const unsigned int count = reflective->get_children_count();
        children.reserve(count);

        for (unsigned int i = 0; i < count; i++) 
        {
            Node_ptr child(new Node(reflective->get_child(i), 
                    reflective->get_child_value(holder, i), this, i));

            children.push_back(child);
        }
    }

    initialized = true;
}

void Node::check_for_initialized()
{
    if (!initialized)
        initialize();
}

