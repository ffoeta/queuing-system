#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <iostream>
#include "../Interface/Interface.hpp"
#include "../Interface/Auto.hpp"
#include "../Interface/Manual.hpp"

Interface::Interface()
{
    this->initializeButtons();
    this->initializeFormLines();

    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(this->formGroupBox);
    layout->addWidget(this->buttonsHolder);

    this->setLayout(layout);
}

void Interface::initializeButtons()
{
    this->buttonsHolder = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;

    buttons[0] = new QPushButton(tr("Ручной"));
    layout->addWidget(buttons[0]);
    connect(buttons[0], &QPushButton::clicked, this, [this]() { this->startModuling(MANUAL); });

    buttons[1] = new QPushButton(tr("Автоматический"));
    layout->addWidget(buttons[1]);
    connect(buttons[1], &QPushButton::clicked, this, [this]() { this->startModuling(AUTO); });

    buttonsHolder->setLayout(layout);
}

void Interface::initializeFormLines()
{
    this->formGroupBox = new QGroupBox(tr("Настройки"));
    QFormLayout *layout = new QFormLayout;

    this->lineEdits[0] = new QLineEdit(tr("3"));
    this->lineEdits[1] = new QLineEdit(tr("3"));
    this->lineEdits[2] = new QLineEdit(tr("3"));
    this->lineEdits[3] = new QLineEdit(tr("10000"));
    this->lineEdits[4] = new QLineEdit(tr("3"));
    this->lineEdits[5] = new QLineEdit(tr("0"));
    this->lineEdits[6] = new QLineEdit(tr("1"));

    layout->addRow(new QLabel(tr("Sources:")), this->lineEdits[0]);
    layout->addRow(new QLabel(tr("Buffers:")), this->lineEdits[1]);
    layout->addRow(new QLabel(tr("Devices:")), this->lineEdits[2]);
    layout->addRow(new QLabel(tr("N packages:")), this->lineEdits[3]);
    layout->addRow(new QLabel(tr("Sources const:")), this->lineEdits[4]);
    layout->addRow(new QLabel(tr("Devices A:")), this->lineEdits[5]);
    layout->addRow(new QLabel(tr("Devices B:")), this->lineEdits[6]);

    this->formGroupBox->setLayout(layout);
}

void Interface::startModuling(Run_Type run_type)
{
    

    int n_soruces = this->lineEdits[0]->text().toInt();
    int n_buffers = this->lineEdits[1]->text().toInt();
    int n_devices = this->lineEdits[2]->text().toInt();
    int n_requests = this->lineEdits[3]->text().toInt();
    double l = this->lineEdits[4]->text().toDouble();
    double a = this->lineEdits[5]->text().toDouble();
    double b = this->lineEdits[6]->text().toDouble();

    api_.set(run_type, n_soruces, n_buffers, n_devices, n_requests, a, b, l);
 
    QWidget *goTo;
    if (run_type == AUTO)
    {
        goTo = new Auto(&api_);
    }
    else
    {
        goTo = new Manual(&api_);
    }

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(goTo);

    qDeleteAll(this->children());
    delete this->layout();

    this->setLayout(layout);
}