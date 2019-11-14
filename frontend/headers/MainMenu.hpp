#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>
#include <QStackedWidget>

#include "../../backend/headers/InnerAPI.hpp"
#include "Interface.hpp"

class MainMenu : public QWidget
{
public:
    MainMenu(Interface * parent);
    void initializeButtons();
    void initializeFormLines();
private:
    
    Interface * parent_;

    QWidget *buttonsHolder;
    QPushButton *buttons[2];

    QGroupBox *formGroupBox;
    QLineEdit *lineEdits[7];

    void iterate(Run_Type run_type);
    // Настройка с двумя кнопками -> они переходят в автоматический режим или в ручной
};

#endif