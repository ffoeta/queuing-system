#include "../Interface/Auto.hpp"


Auto::Auto(InnerAPI * api)
{
    this->api_ = api;
    
    QGridLayout *mainLayout = new QGridLayout();

    this->setLayout(mainLayout);
}