#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <iostream>
#include "../../backend/headers/Engine.hpp"


class Interface : public QWidget
{
public:
    Interface();

    Engine * getEngine();

    void goToManual();
    void goToMenu();
    void goToAuto();
    void goToSettings();

    void rebootEngine();

private:
    Engine *engine;
    
    QStackedWidget * stackedWidget;
    QWidget *autoWidget;
    QWidget *mainMenuWidget;
    QWidget *manualWidget;
    QWidget *settingsWidget;

};

#endif
