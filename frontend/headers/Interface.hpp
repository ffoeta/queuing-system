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
#include "../../backend/headers/InnerAPI.hpp"


class Interface : public QWidget
{
private:
    QStackedWidget * stackedWidget;
    
    QWidget *autoWidget;
    QWidget *mainMenuWidget;
    QWidget *manualWidget;
    QWidget *settingsWidget;

    InnerAPI * api_;
public:
    Interface();

    void goToManual();
    void goToMenu();
    void goToAuto();
    void goToSettings();

    InnerAPI * getAPI();

    void reboot();
    void setAPI(int n_soruces, int n_buffers, int n_devices, int n_requests, float a, float b, float l);
    void selectMode(Run_Type run_type);
};

#endif