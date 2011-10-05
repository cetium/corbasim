#include <iostream>
#include <string>
#include "Foo.pb.h"
#include <protobuf2json/json/parser.hpp>

int main(int argc, const char *argv[])
{
    Foo foo;

    const std::string json_foo = "{\"text\": \"Hello world\"}";

    protobuf2json::json::parse(foo, json_foo);

    std::cout << "foo.text() == \"" << foo.text() << "\"" << std::endl;
    
    return 0;
}
