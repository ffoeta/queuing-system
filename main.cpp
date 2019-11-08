#include "frontend/Interface.hpp"
#include "backend/BLogic.hpp"

#include <QApplication>

int main( int argc, char **argv )
{
    QApplication app(argc, argv);

    Interface vv;

    vv.show();
    return app.exec();
}
