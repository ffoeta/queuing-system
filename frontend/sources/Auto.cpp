#include "../headers/Auto.hpp"

Auto::Auto(Interface * parent) :
    parent_(parent)
{
    this->back_ = new QPushButton(tr("BACK"));

    QGridLayout * layout = new QGridLayout();

    connect(this->back_,
        &QPushButton::clicked, this, &Auto::goBack);

    layout->addWidget(this->back_);

    this->setLayout(layout);
}

void Auto::goBack() {
    this -> parent_ -> goToMenu();
}
