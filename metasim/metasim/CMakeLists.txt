#
# CORE LIBRARY
#
set(metasim_core_SRCS 
    core/reflective.cpp)

add_library(metasim_core SHARED ${metasim_core_SRCS})

#
# GUI LIBRARY
#

set(metasim_gui_EXPORTED_HEADERS
    gui/ModelNode.hpp
    gui/qvariant.hpp
    gui/DataModel.hpp
    gui/ReflectiveGUI.hpp)

foreach(_header ${metasim_gui_EXPORTED_HEADERS})
    get_filename_component(_header_path ${_header} PATH)
    install(FILES ${_header}
        DESTINATION include/metasim/${_header_path})
endforeach(_header ${metasim_gui_EXPORTED_HEADERS})

set(metasim_gui_MOC_HDRS
    gui/DataModel.hpp
    gui/ReflectiveGUI.hpp)

set(metasim_gui_SRCS
    gui/ModelNode.cpp
    gui/qvariant.cpp
    gui/DataModel.hpp
    gui/ReflectiveGUI.cpp)

set(metasim_gui_LIBS
    ${QT_LIBRARIES}
    metasim_core)

# NOTE: QT bug: https://bugreports.qt.nokia.com/browse/QTBUG-22829
qt4_wrap_cpp(metasim_gui_MOC_SRCS ${metasim_gui_MOC_HDRS} 
    OPTIONS -DBOOST_TT_HAS_OPERATOR_HPP_INCLUDED)

add_library(metasim_gui SHARED 
    ${metasim_gui_SRCS}
    ${metasim_gui_MOC_SRCS})
target_link_libraries(metasim_gui ${metasim_gui_LIBS})

set_target_properties(metasim_gui PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_MAJOR_VERSION})

install(TARGETS metasim_gui DESTINATION lib)

