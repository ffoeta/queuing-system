#ifndef MANUAL_HPP
#define MANUAL_HPP

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QDebug>
#include <QString>
#include <QVBoxLayout>

#include "../../backend/Interface/InnerAPI.hpp"
#include "Interface.hpp"

class Manual : public QWidget
{
public:
    Manual(InnerAPI * api);
private:
    InnerAPI * api_;
    void check();
    void check2();
    QPushButton *button;
    QPushButton *button2;
    QLabel      *label;

};

#endif