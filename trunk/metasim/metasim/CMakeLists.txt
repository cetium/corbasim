#
# CORE LIBRARY
#

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/core/version.hpp.in" 
    "${CMAKE_CURRENT_SOURCE_DIR}/core/version.hpp" IMMEDIATE @ONLY)

set(metasim_core_EXPORTED_HEADERS
    core/adapted.hpp
    core/holder.hpp
    core/export.hpp
    core/reflective_fwd.hpp
    core/reflective.hpp
    core/reflective.ipp
    core/reflective_primitive.ipp

    core/version.hpp

    json/converter.hpp
    json/helper.hpp
    json/parser.hpp
    json/reflective.cpp
    json/reflective.hpp
    json/writer.hpp
    json/detail/base64_blob.hpp
    json/detail/json.hpp
    json/detail/json_parse.hpp
    json/detail/json_writer.hpp
)

foreach(_header ${metasim_core_EXPORTED_HEADERS})
    get_filename_component(_header_path ${_header} PATH)
    install(FILES ${_header}
        DESTINATION include/metasim/${_header_path})
endforeach(_header ${metasim_core_EXPORTED_HEADERS})

set(metasim_core_SRCS 
    json/reflective.cpp
    json/detail/modp_b64.c
    core/reflective.cpp)

add_library(metasim_core SHARED ${metasim_core_SRCS})

set_target_properties(metasim_core PROPERTIES 
    VERSION ${${PROJECT_NAME}_VERSION} 
    SOVERSION ${${PROJECT_NAME}_MAJOR_VERSION})

install(TARGETS metasim_core DESTINATION lib)

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
    gui/DataModel.cpp
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

#
# EXAMPLES AND TESTS
#
add_subdirectory(examples EXCLUDE_FROM_ALL)

