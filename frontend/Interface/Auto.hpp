#ifndef AUTO_HPP
#define AUTO_HPP

#include <QWidget>
#include <QTableWidget>
#include <QGridLayout>
#include "../../backend/Interface/InnerAPI.hpp"
#include "Interface.hpp"

class Auto : public QWidget
{
public:
    Auto(InnerAPI * api_);

private:
    InnerAPI * api_;
};

#endif
