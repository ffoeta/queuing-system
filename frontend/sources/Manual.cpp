#include "../headers/Manual.hpp"


Manual::Manual(Interface * parent) :
    parent_(parent)
{

    this->step_ = new QPushButton(tr("PRESS ME"));
    this->reboot_ = new QPushButton(tr("REBOOT"));
    this->back_ = new QPushButton(tr("BACK"));
    this->label_ = new QLabel(tr("___"));

    this->draw_ = new Draw(
        this->parent_->getAPI()->getNSources(), 
        this->parent_->getAPI()->getNBuffers(), 
        this->parent_->getAPI()->getNDevices());

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
    // float * getDroppProbability();
    // float * getAverageWaitTime();
    // float * getAverageDeviceTime();
    // float * getAverageInSystem();

    label_->setText(QString::fromStdString(
        std::to_string(this -> parent_ -> getAPI() -> next().getDroppProbability().at(0)  )
    ));
}

void Manual::reboot()
{
    this -> parent_ -> reboot();
    label_->setText(QString::fromStdString("__"));
}   

void Manual::goBack()
{
    this -> parent_ -> goToMenu();
}   
