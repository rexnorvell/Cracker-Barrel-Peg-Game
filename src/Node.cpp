#include "Node.h"

Node::Node(const Board& board, Node* parent, Move previous_move)
    : board(board), parent(parent), previous_move(previous_move) {
}

Board Node::get_board() const {
    return this->board;
}

Node* Node::get_parent() const {
    return this->parent;
}

Move Node::get_previous_move() const {
    return this->previous_move;
}