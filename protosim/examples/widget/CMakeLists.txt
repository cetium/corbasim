
include_directories(${CMAKE_CURRENT_BINARY_DIR})
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS Foo.proto)

add_executable(widget_example widget.cpp ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(widget_example
    ${QT_LIBRARIES} ${PROTOBUF_LIBRARY}
    protosim protosim_qt
)


