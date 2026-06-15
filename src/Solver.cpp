#include "Solver.h"

#include <iostream>
#include <set>

Solver::Solver(const Node& root): root(root) {
    calculate_solutions();
}

std::vector<Node*> Solver::get_solutions() const {
    return this->solutions;
}

void Solver::calculate_solutions() {
    std::stack<Node*> frontier;
    frontier.push(new Node(this->root));
    Node* current_node;

    while (!frontier.empty()) {
        current_node = frontier.top();
        frontier.pop();

        if (current_node->get_board().is_solved()) {
            this->solutions.push_back(current_node);
        }

        for (Move move : current_node->get_board().get_legal_moves()) {
            Board next_board = current_node->get_board().get_next_board(move);
            frontier.push(new Node(next_board, current_node, move));
        }
    }
}

void Solver::print_solutions() const {
    std::cout << this->solutions.size() << " solutions found." << std::endl;
    int solution_counter = 0;

    for (Node* solution : this->solutions) {
        std::cout << "Solution #" << ++solution_counter << ": " << std::endl;
        std::vector<Move> moves;
        Node* current_node = solution;

        while (current_node->get_parent() != nullptr) {
            moves.push_back(current_node->get_previous_move());
            current_node = current_node->get_parent();
        }

        for (int i = moves.size() - 1; i >= 0; i--) {
            if (i == 0) {
                std::cout << "(" << moves[i].start << ", " << moves[i].end << ")";
            }
            else {
                std::cout << "(" << moves[i].start << ", " << moves[i].end << "), ";
            }
        }
        
        std::cout << std::endl;
    }
}