#include "frontend/Interface/Interface.hpp"

#include <QApplication>

int main( int argc, char **argv )
{
    QApplication app(argc, argv);

    Interface vv;

    vv.show();
    return app.exec();
}
