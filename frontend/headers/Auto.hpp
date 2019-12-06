#ifndef AUTO_HPP
#define AUTO_HPP

#include <QWidget>
#include <QTableWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include "../../backend/headers/InnerAPI.hpp"
#include "Interface.hpp"

#include <iostream>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>

class Auto : public QWidget
{
public:
    Auto(Interface * parent);
private:
    
    void init();

    void initializeForm();
    void initializeButtons();

    void start();
    void goBack();
    void reboot();

    QWidget *buttonsHolder;
    QWidget *formGroupBox;
    
    QLabel  *    prob_;
    QLabel  *   wait_;
    QLabel  *   device_;
    QLabel  *   system_;

    QPushButton *start_;
    QPushButton *back_;
    QPushButton *reboot_;

    Interface * parent_;
};

#endif
