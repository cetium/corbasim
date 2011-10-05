cmake_minimum_required(VERSION 2.6)
project(protobuf2json CXX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(protobuf2json_test test.cpp Foo.pb.cc)

target_link_libraries(protobuf2json_test
    pthread protobuf
)

