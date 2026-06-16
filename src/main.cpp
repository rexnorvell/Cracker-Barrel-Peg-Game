#include "Board.h"
#include "Node.h"
#include "Solver.h"

#include <iostream>
#include <limits>

void welcome_user();
void print_control_panel();
void find_all_solutions();
void determine_hardest_starting_configuration();
void play_game();

int main() {
    welcome_user();
    std::string user_input;

    while (true) {
        print_control_panel();
        
        std::getline(std::cin, user_input);
        std::cout << std::endl;

        if (user_input.empty()) {
            std::cout << "Error: Input error." << std::endl;
            std::cin.clear();
        }
        else if (user_input == "q") {
            break;
        }
        else if (user_input == "a") {
            find_all_solutions();
        }
        else if (user_input == "h") {
            determine_hardest_starting_configuration();
        }
        else if (user_input == "p") {
            play_game();
        }
        else {
            std::cout << "Error: Invalid option." << std::endl;
        }
    }

    return 0;
}

void welcome_user() {
    std::string welcome_message = "| Welcome to the Cracker Barrel Peg Game Solver! |";
    std::string dash_border(welcome_message.length(), '-');
    std::cout << dash_border << std::endl;
    std::cout << welcome_message << std::endl;
    std::cout << dash_border << std::endl;
}

void print_control_panel() {
    std::cout << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
    std::cout << "| Control Panel:                                    |" << std::endl;
    std::cout << "| a - prints all solutions for the default game     |" << std::endl;
    std::cout << "| h - determines the hardest starting configuration |" << std::endl;
    std::cout << "| p - play the Cracker Barrel peg game              |" << std::endl;
    std::cout << "| q - quits the program                             |" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
    std::cout << std::endl;
}

void find_all_solutions() {
    std::cout << "Calculating solutions..." << std::endl;
    Node root = Node(Board(), nullptr);
    Solver solver = Solver(root);
    solver.print_solutions();
}

void determine_hardest_starting_configuration() {
    for (int i = 0; i < Board::BOARD_SIZE; i++) {
        std::cout << "Calculating for Board #" << i + 1 << "..." << std::endl;
        std::array<int, Board::BOARD_SIZE> starting_state;

        for (int j = 0; j < Board::BOARD_SIZE; j++) {
            starting_state[j] = (j == i) ? (0) : (1);
        }
        
        Board board = Board(starting_state);
        board.print_state();
        Node root = Node(board, nullptr);
        Solver solver = Solver(root);
        std::vector<Node*> solutions = solver.get_solutions();
        std::cout << solutions.size() << " solutions for Board #" << i + 1 << "." << std::endl;
    }
}

void play_game() {
    Board board = Board();
    board.print_state();
    while (board.get_legal_moves().size() > 0) {
        board.print_legal_moves();
        int number_of_moves = board.get_legal_moves().size();
        std::string error_string = "Error: Input an integer between 1 and " + std::to_string(number_of_moves) + ".";
        std::string move_string;
        std::getline(std::cin, move_string);
        if (move_string.empty()) {
            std::cout << error_string << std::endl;
            std::cin.clear();
        }
        else {
            try {
                size_t pos;
                int move = std::stoi(move_string, &pos);
                if (pos != move_string.size()) {
                    std::cout << error_string << std::endl;
                }
                else if (move < 1 || move > number_of_moves) {
                    std::cout << error_string << std::endl;
                }
                else {
                    board.execute_move(board.get_legal_moves()[move - 1]);
                }
            }
            catch (...) {
                std::cout << error_string << std::endl;
            }
        }
        board.print_state();
    }
    if (board.is_solved()) {
        std::cout << "Congratulations! You won!" << std::endl;
    }
    else {
        std::cout << "Game over! " << board.get_remaining_peg_count() << " pegs remaining." << std::endl;
    }
}