#include "../Interface/Manual.hpp"


Manual::Manual(InnerAPI * api)
{
    this->api_ = api;

    this->button = new QPushButton(tr("PRESS ME"));
    this->button2 = new QPushButton(tr("BACK"));
    this->label = new QLabel(tr("___"));

    QGridLayout *layout = new QGridLayout();

    layout->addWidget(this->label);
    layout->addWidget(this->button);
    layout->addWidget(this->button2);

    connect(this->button,
            &QPushButton::clicked, this, &Manual::check);

    connect(this->button2,
            &QPushButton::clicked, this, &Manual::check2);

    this->setLayout(layout);
}

void Manual::check()
{
    auto time = this->api_ -> next();
    label->setText(QString::fromStdString(std::to_string(time.getCurrent())));
}

void Manual::check2()
{
    auto  goTo = new Interface();

    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(goTo);

    qDeleteAll(this->children());
    delete this->layout();

    this->setLayout(layout);
    
}