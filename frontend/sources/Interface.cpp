#include "../headers/Interface.hpp"

#include "../headers/Auto.hpp"
#include "../headers/Manual.hpp"
#include "../headers/MainMenu.hpp"
#include "../headers/Settings.hpp"


Interface::Interface()
{
    //Апи
    api_ = new InnerAPI();

    // окна
    autoWidget = new Auto(this);
    mainMenuWidget = new MainMenu(this);
    manualWidget = new Manual(this);
    settingsWidget = new Settings(this);

    //управление
    stackedWidget = new QStackedWidget(this);

    //добавляем виджеты 
    stackedWidget->addWidget(autoWidget);
    stackedWidget->addWidget(mainMenuWidget);
    stackedWidget->addWidget(manualWidget);
    stackedWidget->addWidget(settingsWidget);

    //выбираем текущий
    this -> stackedWidget ->setCurrentWidget(mainMenuWidget);

    this -> setAPI(3,3,3,10000,0,1,3);

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

void Interface::setAPI( int n_soruces, 
                        int n_buffers, 
                        int n_devices, 
                        int n_requests, 
                        float a, 
                        float b, 
                        float l)
{
    this -> api_ -> set(n_soruces, n_buffers, n_devices, n_requests, a, b, l);
}

void Interface::selectMode(Run_Type run_type) {
    this -> api_ ->setRunType(run_type);
}

void Interface::goToManual()
{
    this -> selectMode(MANUAL);
    this -> stackedWidget -> setCurrentWidget(manualWidget);
}

void Interface::goToAuto() 
{
    this -> selectMode(AUTO);
    this -> stackedWidget -> setCurrentWidget(autoWidget);
}

void Interface::goToMenu()
{
    this -> stackedWidget -> setCurrentWidget(mainMenuWidget);
}

void Interface::goToSettings() 
{
    this -> stackedWidget -> setCurrentWidget(settingsWidget);
}
