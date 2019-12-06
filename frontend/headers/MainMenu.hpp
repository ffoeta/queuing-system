#ifndef MAINMENU_HPP
#define MAINMENU_HPP

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
#include "Interface.hpp"

class MainMenu : public QWidget
{
public:
    MainMenu(Interface * parent);
private:
    void init();

    Interface * parent_;

    QWidget *buttonsHolder;

    QPushButton * start_auto_;
    QPushButton * start_manual_;
    QPushButton * settings_;
    QPushButton * quit_;

    void start();
    void manual();
    void settings();
    void quit();

    // Настройка с двумя кнопками -> они переходят в автоматический режим или в ручной
};

#endif