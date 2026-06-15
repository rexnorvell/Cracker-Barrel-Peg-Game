#ifndef NODE_H
#define NODE_H

#include "Board.h"

class Node {
    public:
        Node(const Board& board, Node* parent, Move previous_move = Move{-1, -1});
        Board get_board() const;
        Node* get_parent() const;
        Move get_previous_move() const;
    private:
        Board board;
        Node* parent;
        Move previous_move;
};

#endif