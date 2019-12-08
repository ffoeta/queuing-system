#ifndef MANUAL_HPP
#define MANUAL_HPP

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QDebug>
#include <QString>
#include <QVBoxLayout>

#include "Interface.hpp"
#include "Draw.hpp"

class Manual : public QWidget
{
public:
    Manual(Interface * parent);
private:
    void step();
    void reboot();
    void goBack();

    Draw * draw_;
    
    Interface * parent_;
    QPushButton *step_;
    QPushButton *back_;
    QPushButton *reboot_;
    QLabel      *label_;

};

#endif