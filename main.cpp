#include "frontend/headers/Interface.hpp"

#include <QApplication>

int main( int argc, char **argv )
{
    std::srand(std::time(nullptr));

    QApplication app(argc, argv);

    

    Interface vv;
    vv.show();
    return app.exec();
}
