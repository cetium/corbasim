#include <iostream>
#include <protosim/qt/ProtoMessageWidget.hpp>
#include "Foo.pb.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Foo foo;
    protosim::qt::ProtoMessageWidget widget(foo.GetDescriptor());
    
    widget.show();

    return app.exec();
}
