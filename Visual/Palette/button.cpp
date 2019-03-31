#include "button.h"

Button::Button(QWidget *parent, bool *p_bool) : QWidget(parent), p_bool(p_bool)
{
    p_button = new QPushButton(this);
    p_button->setWindowOpacity(1);
    connect(p_button, SIGNAL(clicked()), this, SLOT(block()));
}

void Button::setColor(QString qstr) {
    p_button->setStyleSheet(qstr);
}

void Button::block() {
    if (*p_bool) {
        //block this button
        *p_bool = false;
        setColor(COLOR_BLOCKED);
    }
    else {
        //unblock
        *p_bool = true;
        setColor(COLOR_ORIGINAL);
    }
    emit blockChange();
}
