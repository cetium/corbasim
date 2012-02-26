// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * export.hpp
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

#ifndef METASIM_GUI_EXPORT_HPP
#define METASIM_GUI_EXPORT_HPP

#if defined(_MSC_VER)

    #if defined(metasim_gui_EXPORTS)
        #define METASIM_GUI_DECLSPEC __declspec(dllexport)
    #else
        #define METASIM_GUI_DECLSPEC __declspec(dllimport)
    #endif

#else
    #define METASIM_GUI_DECLSPEC 
#endif

#endif /* METASIM_GUI_EXPORT_HPP */

