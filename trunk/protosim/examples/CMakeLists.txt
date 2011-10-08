
find_package(Qt4)

if(DEFINED QT_FOUND AND ${QT_FOUND} STREQUAL "YES")
    include(${QT_USE_FILE})

    # Examples that require QT
    add_subdirectory(widget)
endif()

