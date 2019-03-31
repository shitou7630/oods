#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include "button.h"
#include "dijkstra.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    void init(int nRows, int nCols, int button_size);

signals:

private slots:
    void slotDijkstra();
    void slotSlider(int value);
    void paint(int start_step, int last_step);

private:

    void callDijkstra();

    Ui::Widget *ui;

    int nRows;
    int nCols;
    int button_size;

    Graph *pGraph;
    Vertex src, des;
    Dijkstra dijkstra;
    vector<Action> actions;
    vector<Vertex> path;

    PButton **buttons;

    QSlider *p_slider;
    int slider_last_value;
};

#endif // WIDGET_H
