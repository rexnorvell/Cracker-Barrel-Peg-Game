#ifndef SOLVER_H
#define SOLVER_H

#include "Node.h"

class Solver {
    public:
        Solver(const Node& root);
        std::vector<Node*> get_solutions() const;
        void print_solutions() const;
    private:
        Node root;
        std::vector<Node*> solutions;

        void calculate_solutions();
};

#endif