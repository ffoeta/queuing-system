#ifndef AUTO_HPP
#define AUTO_HPP

#include <QWidget>
#include <QTableWidget>
#include <QGridLayout>
#include <QPushButton>
#include "../../backend/headers/InnerAPI.hpp"
#include "Interface.hpp"

class Auto : public QWidget
{
public:
    Auto(Interface * parent);
private:
    void goBack();
    QPushButton *back_;
    Interface * parent_;
};

#endif
