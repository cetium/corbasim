// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * initialize.cpp
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

#include "initialize.hpp"

#include <QMetaType>
#include <boost/shared_ptr.hpp>
#include <corbasim/impl.hpp>
#include <corbasim/qt/ReferenceModel.hpp>
#include <corbasim/core/reflective_fwd.hpp>
#include <corbasim/core/file_format_helper.hpp>

namespace  
{

class Initializer
{
public:
    Initializer()
    {
        // Q_INIT_RESOURCE(corbasim_qt);

        qRegisterMetaType< CORBA::Object_var >
            ("CORBA::Object_var");

        // Singleton instances
        corbasim::qt::ReferenceModel::getDefaultModel();

        // Ensure created all file format helpers
        {
            using namespace ::corbasim::core;

            file_format_factory const * fff = 
                file_format_factory::get_instance();

            for (int i = 0; i < FILE_FORMAT_MAX; ++i) 
            {
                fff->get_helper(static_cast< file_format >(i));
            }
        }
    }
};

} // namespace

CORBASIM_QT_DECLSPEC void corbasim::qt::initialize()
{
    static boost::shared_ptr< Initializer > instance(new Initializer);
}


