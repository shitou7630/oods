#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::init(int nRows, int nCols, int button_size) {
    this->nRows = nRows;
    this->nCols = nCols;
    this->button_size = button_size;
    this->setStyleSheet(COLOR_BACKGROUND);

    this->setGeometry(QRect(QPoint(0, 0), QSize(nCols * button_size, (nRows + 3) * button_size)));

    bool **matrix = new bool*[nRows];
    for (int i = 0; i < nRows; i++) {
        matrix[i] = new bool[nCols];
        fill(matrix[i], matrix[i] + nCols, true);
    }
    pGraph = new Graph(matrix, nRows, nCols);
    src.row = nRows - 1;
    src.col = 0;
    des.row = 0;
    des.col = nRows - 1;

    buttons = new PButton*[nRows];
    for (int i = 0; i < nRows; i++) {
        buttons[i] = new PButton[nCols];
        for (int j = 0; j < nCols; j++) {
            buttons[i][j] = new Button(this, matrix[i] + j);
            buttons[i][j]->setGeometry(QRect(QPoint(button_size * j, button_size * i), QSize(button_size, button_size)));
            buttons[i][j]->setColor(COLOR_ORIGINAL);
            connect(buttons[i][j], SIGNAL(blockChange()), this, SLOT(slotDijkstra()));
        }
    }
    p_slider = new QSlider(this);
    p_slider->setGeometry(QRect(QPoint(0, button_size * (nRows + 1)), QSize(button_size * nCols, button_size)));
    p_slider->setOrientation(Qt::Horizontal);
    connect(p_slider, SIGNAL(valueChanged(int)), this, SLOT(slotSlider(int)));
    callDijkstra();
}

void Widget::slotDijkstra() {
    callDijkstra();
}

void Widget::callDijkstra() {
    dijkstra.dijkstra(pGraph, src, des, actions, path);
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            if (pGraph->matrix[i][j])
                buttons[i][j]->setColor(COLOR_ORIGINAL);
    p_slider->setMinimum(0);
    p_slider->setMaximum((int)actions.size());
    p_slider->setValue(0);
    slider_last_value = 0;
    p_slider->setSingleStep(1);    
}

void Widget::slotSlider(int value) {
    int row, col;
    if (slider_last_value < value) {
        paint(slider_last_value, value);
    }
    else {
        for (int i = 0; i < nRows; i++)
            for (int j = 0; j < nCols; j++)
                if (pGraph->matrix[i][j])
                    buttons[i][j]->setColor(COLOR_ORIGINAL);
        paint(0, value);
    }
    slider_last_value = value;
}

void Widget::paint(int start_step, int last_step) {
    int row, col;
    for (int i = start_step; i < last_step; i++) {
        Action action = actions[i];
        row = action.v.row;
        col = action.v.col;
        switch(action.action_type) {
        case COLLECT:{
            buttons[row][col]->setColor(COLOR_COLLECT);
            break;
        }
        case UPDATE:{
            buttons[row][col]->setColor(COLOR_UPDATE);
            break;
        }
        default: break;
        }
        if (row == des.row && col == des.col) {
            for (Vertex v : path) {
                buttons[v.row][v.col]->setColor(COLOR_PATH);
            }
            break;
        }
    }
}
