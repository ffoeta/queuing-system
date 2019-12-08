#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "Interface.hpp"

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


class Settings : public QWidget
{
public:
    Settings(Interface * parent);
private:

    void goBack();
    void set();

    void save();

    void initializeButtons();
    void initializeFormLines();
    
    Interface * parent_;
    QWidget *buttonsHolder;

    QPushButton * set_;
    QPushButton * back_;

    QGroupBox *formGroupBox;
    QLineEdit *lineEdits[7];
};

#endif
