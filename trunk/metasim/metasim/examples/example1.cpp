#include <iostream>
#include <metasim/core/adapted.hpp>
#include <metasim/core/reflective.hpp>
#include <metasim/gui/ReflectiveGUI.hpp>
#include <metasim/core/reflective.ipp>

struct ChildStruct
{
    int32_t a;
    std::string str;
    std::vector< std::string > vec;
};

typedef ChildStruct ArrayChildStruct[10];

struct MyStruct
{
    int32_t a;
    std::string str;
    ChildStruct ch;
    ArrayChildStruct ach;
};

BOOST_FUSION_ADAPT_STRUCT(ChildStruct, (int32_t, a) (std::string, str) (std::vector< std::string >, vec))
BOOST_FUSION_ADAPT_STRUCT(MyStruct, (int32_t, a) (std::string, str) (ChildStruct, ch) (ArrayChildStruct, ach))

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QWidget * w = metasim::gui::createWidget(metasim::core::reflective< MyStruct >::get_instance(), NULL);
    w->show();
    
    return app.exec();
} 
