#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>
#include <QStackedWidget>

#include "../../backend/headers/InnerAPI.hpp"

class Interface : public QWidget
{
private:
    QStackedWidget * stackedWidget;
    QWidget *autoWidget;
    QWidget *mainMenuWidget;
    QWidget *manualWidget;

    InnerAPI * api_;
public:
    Interface();
    void goToManual();
    void goToMenu();
    void goToAuto();

    InnerAPI * getAPI();

    void reboot();

    void setAPI(Run_Type run_Type, int n_soruces, int n_buffers, int n_devices, int n_requests, float a, float b, float l);
};

#endif