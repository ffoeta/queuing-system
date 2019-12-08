#include "../headers/Interface.hpp"

#include "../headers/Auto.hpp"
#include "../headers/Manual.hpp"
#include "../headers/MainMenu.hpp"
#include "../headers/Settings.hpp"


Interface::Interface()
{
    //Апи
    engine = new Engine();

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

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(stackedWidget);
    this -> setLayout (layout);
}

Engine * Interface::getEngine() 
{
    return this -> engine;
};

void Interface::rebootEngine()
{
    this -> engine -> _reboot();
}

void Interface::goToManual()
{
    this -> stackedWidget -> setCurrentWidget(manualWidget);
}

void Interface::goToAuto() 
{
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
