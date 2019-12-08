#include "../headers/Manual.hpp"
#include <iostream>

Manual::Manual(Interface * parent) :
    parent_(parent)
{

    this->step_ = new QPushButton(tr("PRESS ME"));
    this->reboot_ = new QPushButton(tr("REBOOT"));
    this->back_ = new QPushButton(tr("BACK"));
    this->label_ = new QLabel(tr("___"));

    this->draw_ = new Draw(
        this->parent_->getEngine()->_getNSources(), 
        this->parent_->getEngine()->_getNBuffers(), 
        this->parent_->getEngine()->_getNDevices());

    QGridLayout * layout = new QGridLayout();

    layout->addWidget(this->draw_);

    layout->addWidget(this->label_);
    layout->addWidget(this->step_);
    layout->addWidget(this->reboot_);
    layout->addWidget(this->back_);

    connect(this->step_,
            &QPushButton::clicked, this, &Manual::step);

    connect(this->reboot_,
            &QPushButton::clicked, this, &Manual::reboot);

    connect(this->back_,
            &QPushButton::clicked, this, &Manual::goBack);

    this->setLayout(layout);
}

void Manual::step()
{   
    this -> parent_ -> getEngine() -> _manual();

    auto source_picture = this -> parent_ -> getEngine() -> _picture().getSourcePicture();
    auto buffer_picture = this -> parent_ -> getEngine() -> _picture().getBufferPicture();
    auto device_picture = this -> parent_ -> getEngine() -> _picture().getDevicePicture();

    std::cout << "source: " << source_picture.at(0) << source_picture.at(1) << source_picture.at(2)  << std::endl;
    std::cout << "buffer: " << buffer_picture.at(0) << buffer_picture.at(1) << buffer_picture.at(2)  << std::endl;
    std::cout << "device: " << device_picture.at(0) << device_picture.at(1) << device_picture.at(2)  << std::endl;
}

void Manual::reboot()
{
    this -> parent_ -> rebootEngine();
    label_->setText(QString::fromStdString("__"));
}   

void Manual::goBack()
{
    this -> parent_ -> goToMenu();
}   
