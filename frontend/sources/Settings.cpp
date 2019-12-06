#include "../headers/Settings.hpp"

Settings::Settings(Interface * parent) :
    parent_(parent)
{
    initializeFormLines();
    initializeButtons();

    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(this->buttonsHolder);
    layout->addWidget(this->formGroupBox);

    this->setLayout(layout);
}

void Settings::initializeFormLines()
{
    this->formGroupBox = new QGroupBox(tr("setup"));
    QFormLayout *layout = new QFormLayout;

    this->lineEdits[0] = new QLineEdit(tr("3"));
    this->lineEdits[1] = new QLineEdit(tr("3"));
    this->lineEdits[2] = new QLineEdit(tr("3"));
    this->lineEdits[3] = new QLineEdit(tr("10000"));
    this->lineEdits[5] = new QLineEdit(tr("0"));
    this->lineEdits[6] = new QLineEdit(tr("1"));
    this->lineEdits[4] = new QLineEdit(tr("3"));

    layout->addRow(new QLabel(tr("Sources:")), this->lineEdits[0]);
    layout->addRow(new QLabel(tr("Buffers:")), this->lineEdits[1]);
    layout->addRow(new QLabel(tr("Devices:")), this->lineEdits[2]);
    layout->addRow(new QLabel(tr("N packages:")), this->lineEdits[3]);
    layout->addRow(new QLabel(tr("Source A:")), this->lineEdits[5]);
    layout->addRow(new QLabel(tr("Source B:")), this->lineEdits[6]);
    layout->addRow(new QLabel(tr("Device const:")), this->lineEdits[4]);

    this->formGroupBox->setLayout(layout);
}

void Settings::initializeButtons()
{
    this->buttonsHolder = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    set_ = new QPushButton(tr("set"));
    layout->addWidget(set_);
    connect(set_, &QPushButton::clicked, this, [this]() { this->set();});

    back_ = new QPushButton(tr("go back"));
    layout->addWidget(back_);
    connect(back_, &QPushButton::clicked, this, [this]() { this->goBack();});

    buttonsHolder->setLayout(layout);
}

void Settings::save() {
    int n_soruces = this->lineEdits[0]->text().toInt();
    int n_buffers = this->lineEdits[1]->text().toInt();
    int n_devices = this->lineEdits[2]->text().toInt();
    int n_requests = this->lineEdits[3]->text().toInt();
    double a = this->lineEdits[4]->text().toDouble();
    double b = this->lineEdits[5]->text().toDouble();
    double l = this->lineEdits[6]->text().toDouble();

    this -> parent_ -> setAPI(n_soruces, n_buffers, n_devices, n_requests, a, b, l);
}

void Settings::set() {
    this -> save();
    this -> parent_ -> goToMenu();
}

void Settings::goBack() {
    this -> parent_ -> goToMenu();
}