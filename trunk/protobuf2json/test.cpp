#include <iostream>
#include <string>
#include "Foo.pb.h"
#include <protobuf2json/json/parser.hpp>
#include <protobuf2json/json/writer.hpp>

int main(int argc, const char *argv[])
{
    Foo foo;

    const std::string json_foo = 
        "{"
            "\"text\": \"Hello world\","
            "\"text_repeated\":[\"one\", \"two\"],"
            "\"bars\":[{\"dou\": 100}, {\"dou\": 200}]"
        "}";

    protobuf2json::json::parse(foo, json_foo);

    std::cout << "foo.text() == \"" << foo.text() << "\"" << std::endl;
    std::cout << "foo.text_repeated_size() == \"" << 
        foo.text_repeated_size() << "\"" << std::endl;
    std::cout << "foo.bars_size() == \"" << 
        foo.bars_size() << "\"" << std::endl;
    
    
    protobuf2json::json::write(std::cout, foo);
    std::cout << std::endl;
    return 0;
}
