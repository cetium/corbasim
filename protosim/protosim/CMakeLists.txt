#
# CORBASIM BASE
#

# Fichero version.hpp
# configure_file("${CMAKE_CURRENT_SOURCE_DIR}/version.hpp.in" 
#     "${CMAKE_CURRENT_SOURCE_DIR}/version.hpp" IMMEDIATE @ONLY)

# Fichero config.hpp
# configure_file("${CMAKE_CURRENT_SOURCE_DIR}/core/config.hpp.in" 
#     "${CMAKE_CURRENT_SOURCE_DIR}/core/config.hpp" IMMEDIATE @ONLY)

set(protosim_EXPORTED_HEADERS
    protobuf_fwd.hpp
    )

foreach(_header ${protosim_EXPORTED_HEADERS})
    get_filename_component(_header_path ${_header} PATH)
    install(FILES ${_header} 
        DESTINATION include/protosim/${_header_path}) 
endforeach(_header ${protosim_EXPORTED_HEADERS})

set(protosim_LIBS
    boost_serialization
    boost_thread
    boost_system
    boost_regex)

set(protosim_SRCS
    # JSON
    json/detail/modp_b64.c
    )
add_library(protosim SHARED ${protosim_SRCS})
target_link_libraries(protosim
    ${protosim_LIBS})

set_target_properties(protosim PROPERTIES 
    VERSION ${${PROJECT_NAME}_VERSION} 
    SOVERSION ${${PROJECT_NAME}_MAJOR_VERSION})

install(TARGETS protosim DESTINATION lib)

#
# CORBASIM QT
#
if(NOT DEFINED CORBASIM_DISABLE_UI)

    find_package(Qt4 REQUIRED)

    include(${QT_USE_FILE})

    set(protosim_qt_EXPORTED_HEADERS
        qt/FieldWidget.hpp
        qt/ProtoMessageWidget.hpp
        qt/widgets.hpp
    )

    foreach(_header ${protosim_qt_EXPORTED_HEADERS})
        get_filename_component(_header_path ${_header} PATH)
        install(FILES ${_header} 
            DESTINATION include/protosim/${_header_path}) 
    endforeach(_header ${protosim_qt_EXPORTED_HEADERS})

    set(protosim_qt_MOC_HDRS
        qt/FieldWidget.hpp
        qt/ProtoMessageWidget.hpp)

    set(protosim_qt_SRCS
        qt/FieldWidget.cpp
        qt/ProtoMessageWidget.cpp
        qt/widgets.cpp)

    set(protosim_qt_LIBS
        ${QT_LIBRARIES}
        protosim
#         boost_serialization
#         boost_thread
#         boost_system
#         boost_regex
    )

    qt4_wrap_cpp(protosim_qt_MOC_SRCS ${protosim_qt_MOC_HDRS})
    add_library(protosim_qt SHARED ${protosim_qt_SRCS} 
        ${protosim_qt_MOC_SRCS})
    target_link_libraries(protosim_qt
        ${protosim_qt_LIB})

    set_target_properties(protosim_qt PROPERTIES 
        VERSION ${${PROJECT_NAME}_VERSION} 
        SOVERSION ${${PROJECT_NAME}_MAJOR_VERSION})

    install(TARGETS protosim_qt DESTINATION lib)
endif()

