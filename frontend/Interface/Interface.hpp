#ifndef INTERFACE_1_HPP
#define INTERFACE_1_HPP

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>

#include "../../backend/Interface/InnerAPI.hpp"

class Interface : public QWidget
{
public:
    Interface();
    void initializeButtons();
    void initializeFormLines();
private:
    InnerAPI api_;

    QWidget *buttonsHolder;
    QPushButton *buttons[2];

    QGroupBox *formGroupBox;
    QLineEdit *lineEdits[7];

    void startModuling(Run_Type run_type);
    // Настройка с двумя кнопками -> они переходят в автоматический режим или в ручной
};

#endif