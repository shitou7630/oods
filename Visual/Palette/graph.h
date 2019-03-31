#ifndef GRAPH_H
#define GRAPH_H

#endif // GRAPH_H
#define NO_VALUE -1

struct Vertex {
    int row, col;
    Vertex() {}
    Vertex(int row, int col) : row(row), col(col) {}
};

struct Graph {
    bool **matrix;
    int nRows, nCols;
    Graph(bool **matrix, int nRows, int nCols) : matrix(matrix), nRows(nRows), nCols(nCols) {}
};

struct AdjIter {
public:
    AdjIter(Graph *pGraph, Vertex v) : pGraph(pGraph), v_row(v.row), v_col(v.col), direction(UP) {}

    Vertex getNext() {
        switch(direction) {
        case UP: {
            if (v_row - 1 >= 0 && pGraph->matrix[v_row - 1][v_col])
                return Vertex(v_row - 1, v_col);
            break;
        }
        case DOWN: {
            if (v_row + 1 < pGraph->nRows && pGraph->matrix[v_row + 1][v_col])
                return Vertex(v_row + 1, v_col);
            break;
        }
        case LEFT: {
            if (v_col - 1 >= 0 && pGraph->matrix[v_row][v_col - 1])
                return Vertex(v_row, v_col - 1);
            break;
        }
        case RIGHT: {
            if (v_col + 1 < pGraph->nCols && pGraph->matrix[v_row][v_col + 1])
                return Vertex(v_row, v_col + 1);
            break;
        }
        default:{
            break;
        }
        }
        return Vertex(NO_VALUE, NO_VALUE);
    }

    bool hasNext() {
        return direction != NO_DIRECTION;
    }

    void update() {
        switch(direction){
        case UP: direction = DOWN; break;
        case DOWN: direction = LEFT; break;
        case LEFT: direction = RIGHT; break;
        case RIGHT: direction = NO_DIRECTION; break;
        default: break;
        }
    }
private:
    Graph *pGraph;
    int v_row, v_col;

    typedef enum {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        NO_DIRECTION,
    }Direction;

    Direction direction;
};
