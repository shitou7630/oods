#ifndef BUTTON_H
#define BUTTON_H

#include <QWidget>
#include <QPushButton>
#include "color.h"

class Button : public QWidget
{
    Q_OBJECT
public:
    explicit Button(QWidget *parent = nullptr, bool *p_bool = nullptr);
    void setColor(QString qstr);

signals:
    void blockChange();

public slots:
    void block();
private:
    QPushButton *p_button;
    int button_size;
    bool *p_bool;
};

typedef Button *PButton;
#endif // BUTTON_H
