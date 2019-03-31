#ifndef ACTION_H
#define ACTION_H

#endif // ACTION_H

#include "graph.h"

typedef enum{
    COLLECT,
    UPDATE,
} ActionType;

struct Action {
    Vertex v;
    ActionType action_type;
    Action(Vertex v, ActionType action_type) : v(v), action_type(action_type) {}
};
