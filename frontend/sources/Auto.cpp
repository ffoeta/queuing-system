#include "../headers/Auto.hpp"

Auto::Auto(Interface * parent) :
    parent_(parent)
{   
    QVBoxLayout *layout = new QVBoxLayout;

    init();

    layout->addWidget(this->formGroupBox);
    layout->addWidget(this->buttonsHolder);

    this->setLayout(layout);

}

void Auto::init() {
    this->initializeButtons();
    this->initializeForm();
}

void Auto::reboot() {
    this -> parent_ -> getEngine() -> _reboot();
    prob_       -> setText(QString::fromStdString("drop prob: _"));
    wait_       -> setText(QString::fromStdString("average wait: _"));
    device_     -> setText(QString::fromStdString("average device: _"));
    system_     -> setText(QString::fromStdString("average system: _"));
}

void Auto::initializeButtons() {
    this->buttonsHolder = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;

    back_ = new QPushButton(tr("back"));
    layout->addWidget(back_);

    reboot_ = new QPushButton(tr("reboot"));
    layout->addWidget(reboot_);

    start_ = new QPushButton(tr("start"));
    layout->addWidget(start_);


    connect(this->back_,
        &QPushButton::clicked, this, &Auto::goBack);

    connect(this->reboot_,
        &QPushButton::clicked, this, &Auto::reboot);

    connect(this->start_,
        &QPushButton::clicked, this, &Auto::start);

    buttonsHolder->setLayout(layout);
}


void Auto::initializeForm() {
    this->formGroupBox= new QWidget;
    QFormLayout *layout = new QFormLayout;

    prob_ = new QLabel(tr("drop prob: _"));
    wait_ = new QLabel(tr("average wait: _"));
    device_ = new QLabel(tr("average device: _"));
    system_ = new QLabel(tr("average system: _"));

    layout->addRow(prob_);
    layout->addRow(wait_);
    layout->addRow(device_);
    layout->addRow(system_);

    formGroupBox->setLayout(layout);
}

void Auto::start() {
    auto run = this -> parent_ -> getEngine() -> _auto();

    // prob_ -> setText(QString::fromStdString("drop prob: " +
    //     std::to_string(run.getDroppProbability().at(0))
    // ));

    // wait_ -> setText(QString::fromStdString("average wait: " +
    //     std::to_string(run.getAverageWaitTime().at(0))
    // ));

    // device_ -> setText(QString::fromStdString("average device: " +
    //     std::to_string(run.getAverageDeviceTime().at(0))
    // ));

    // system_ -> setText(QString::fromStdString("average system: " +
    //     std::to_string(run.getAverageInSystem().at(0))
    // ));
}

void Auto::goBack() {
    this -> parent_ -> goToMenu();
}
