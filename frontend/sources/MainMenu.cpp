#include "../headers/MainMenu.hpp"

MainMenu::MainMenu(Interface * parent) : 
    parent_(parent)
{
    init();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(this->buttonsHolder);

    this->setLayout(layout);
}

void MainMenu::init()
{
    this->buttonsHolder = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    quit_ = new QPushButton(tr("quit"));    
    connect(quit_, &QPushButton::clicked, this, [this]() { this->quit();});

    settings_ = new QPushButton(tr("settings"));
    connect(settings_, &QPushButton::clicked, this, [this]() { this->settings();});

    start_manual_ = new QPushButton(tr("manual"));
    connect(start_manual_, &QPushButton::clicked, this, [this]() { this->manual();});

    start_auto_ = new QPushButton(tr("start"));
    connect(start_auto_, &QPushButton::clicked, this, [this]() { this->start();});

    layout->addWidget(start_auto_);
    layout->addWidget(start_manual_);
    layout->addWidget(settings_);
    layout->addWidget(quit_);

    buttonsHolder->setLayout(layout);
}

void MainMenu::start() {
    this -> parent_ -> goToAuto();
}

void MainMenu::manual() {
    this -> parent_ -> goToManual();
}

void MainMenu::settings() {
    this -> parent_ -> goToSettings();
}

void MainMenu::quit() {
    exit(0);
}
