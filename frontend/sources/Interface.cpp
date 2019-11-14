#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <iostream>

#include "../headers/Interface.hpp"
#include "../headers/Auto.hpp"
#include "../headers/Manual.hpp"
#include "../headers/MainMenu.hpp"

Interface::Interface()
{
    api_ = new InnerAPI();
    autoWidget = new Auto(this);
    mainMenuWidget = new MainMenu(this);
    manualWidget = new Manual(this);

    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(autoWidget);
    stackedWidget->addWidget(mainMenuWidget);
    stackedWidget->addWidget(manualWidget);

    this-> stackedWidget ->setCurrentIndex(1);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(stackedWidget);
    this -> setLayout (layout);
}

InnerAPI * Interface::getAPI() 
{
    return this -> api_;
};

void Interface::reboot() 
{
    this -> api_ -> reboot();
};

void Interface::setAPI(Run_Type run_Type, 
                        int n_soruces, 
                        int n_buffers, 
                        int n_devices, 
                        int n_requests, 
                        float a, 
                        float b, 
                        float l)
{
    this -> api_ -> set(run_Type, n_soruces, n_buffers, n_devices, n_requests, a, b, l);
}

void Interface::goToManual()
{
    this -> stackedWidget -> setCurrentIndex(2);

}

void Interface::goToMenu()
{
    this -> stackedWidget -> setCurrentIndex(1);
}

void Interface::goToAuto() 
{
    this -> stackedWidget -> setCurrentIndex(0);
}
