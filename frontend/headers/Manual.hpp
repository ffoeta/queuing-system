#ifndef MANUAL_HPP
#define MANUAL_HPP

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QDebug>
#include <QString>
#include <QVBoxLayout>

#include "../../backend/headers/InnerAPI.hpp"
#include "Interface.hpp"

class Manual : public QWidget
{
public:
    Manual(Interface * parent);
private:
    void step();
    void reboot();
    void goBack();
    
    Interface * parent_;
    QPushButton *step_;
    QPushButton *back_;
    QPushButton *reboot_;
    QLabel      *label_;

};

#endif