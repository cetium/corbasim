#include <iostream>
#include <metasim/core/adapted.hpp>
#include <metasim/core/reflective.hpp>
#include <metasim/gui/ReflectiveGUI.hpp>
#include <metasim/core/reflective.ipp>

struct MyStruct
{
    int32_t a;
    std::string str;
};

BOOST_FUSION_ADAPT_STRUCT(MyStruct, (int32_t, a) (std::string, str))

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QWidget * w = metasim::gui::createWidget(metasim::core::reflective< MyStruct >::get_instance(), NULL);
    w->show();
    
    return app.exec();
} 
