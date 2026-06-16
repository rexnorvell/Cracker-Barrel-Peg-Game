#include <iostream>
#include <iomanip>

#include "Board.h"

Board::Board(const std::array<int, BOARD_SIZE>& state): state(state), legal_moves(calculate_legal_moves()) {}

void Board::print_state() const {
    int i, j, index = 0;
    std::cout << "-------------" << std::endl;
    
    for (i = 0; i < NUM_ROWS; i++) {
        std::string spaces(i, ' ');
        std::cout << spaces;
        std::cout << "\\ ";

        for (j = 0; j < NUM_ROWS - i; j++) {
            std::string icon = (this->state[index] == 1) ? (PEG_ICON) : (HOLE_ICON);
            std::cout << std::left << std::setw(icon.length() + 1) << icon;
            index++;
        }
        
        std::cout << "/" << std::endl;
    }

    std::string spaces(NUM_ROWS, ' ');
    std::cout << spaces << "\\ /" << std::endl;
}

std::vector<Move> Board::calculate_legal_moves() {
    std::vector<Move> legal_moves;
    int i, current_row_number, next_row_number, next_index, middle_index;
    for (i = 0; i < BOARD_SIZE; i++) {
        // If there's no peg here, move to the next index
        if (this->state[i] == 0) {
            continue;
        }

        // Try the six possible moves for this peg
        current_row_number = get_row_number_from_index(i);

        // Try the two moves going up
        next_row_number = current_row_number - 2;
        if (next_row_number >= MIN_ROW_NUMBER) {
            // Up and to the left
            middle_index = i - (5 - next_row_number - 1);
            next_index = middle_index - (5 - next_row_number);
            if (this->state[next_index] == 0 && this->state[middle_index] == 1 && get_row_number_from_index(next_index) == next_row_number) {
                legal_moves.push_back(Move{i, next_index});
            }
        
            // Up and to the right
            middle_index = i - (5 - next_row_number - 2);
            next_index = middle_index - (5 - next_row_number - 1);
            if (this->state[next_index] == 0 && this->state[middle_index] == 1 && get_row_number_from_index(next_index) == next_row_number) {
                legal_moves.push_back(Move{i, next_index});
            }
        }

        // Try the two moves going down
        next_row_number = current_row_number + 2;
        if (next_row_number <= MAX_ROW_NUMBER) {
            // Down and to the left
            middle_index = i + 5 - current_row_number - 1;
            next_index = middle_index + 5 - current_row_number - 2;
            if (this->state[next_index] == 0 && this->state[middle_index] == 1 && get_row_number_from_index(next_index) == next_row_number) {
                legal_moves.push_back(Move{i, next_index});
            }

            // Down and to the right
            middle_index = i + 5 - current_row_number;
            next_index = middle_index + 5 - current_row_number - 1;
            if (this->state[next_index] == 0 && this->state[middle_index] == 1 && get_row_number_from_index(next_index) == next_row_number) {
                legal_moves.push_back(Move{i, next_index});
            }
        }

        // Left
        middle_index = i - 1;
        next_index = middle_index - 1;
        next_row_number = get_row_number_from_index(next_index);
        if (this->state[next_index] == 0 && this->state[middle_index] == 1 && current_row_number == next_row_number) {
            legal_moves.push_back(Move{i, next_index});
        }

        // Right
        middle_index = i + 1;
        next_index = middle_index + 1;
        next_row_number = get_row_number_from_index(next_index);
        if (this->state[next_index] == 0 && this->state[middle_index] == 1 && current_row_number == next_row_number) {
            legal_moves.push_back(Move{i, next_index});
        }
    }

    return legal_moves;
}

std::vector<Move> Board::get_legal_moves() const {
    return this->legal_moves;
}

int Board::get_row_number_from_index(int index) const {
    if (index < 0 || index >= BOARD_SIZE) {
        return -1;
    }

    int current_value = index;
    
    for (int i = 0; i < NUM_ROWS; i++) {
        current_value -= (NUM_ROWS - i);

        if (current_value < 0) {
            return i;
        }
    }

    std::cout << "Error: An unexpected error occurred with index " << index << "." << std::endl;
    return -1;
}

void Board::print_legal_moves() const {
    std::cout << "Legal Moves:" << std::endl;
    int counter = 0;

    for (const Move& move: legal_moves) {
        std::cout << ++counter << ": (" << move.start << ", " << move.end << ")" << std::endl;
    }
}

void Board::execute_move(Move move) {
    int first_index = move.start;
    int second_index = move.end;
    int middle_index = calculate_middle_index(Move{first_index, second_index});

    // Move the peg
    this->state[first_index] = 0;
    this->state[middle_index] = 0;
    this->state[second_index] = 1;

    // Update the legal moves
    this->legal_moves = calculate_legal_moves();
}

Board Board::get_next_board(const Move move) const {
    Board board = Board(this->state);
    board.execute_move(move);
    return board;
}

std::array<int, Board::BOARD_SIZE> Board::get_state() {
    return this->state;
}

int Board::calculate_middle_index(Move move) const {
    int starting_row_number = get_row_number_from_index(move.start);
    int ending_row_number = get_row_number_from_index(move.end);
    int middle_index;

    if (starting_row_number == ending_row_number) { // If the move was in the same row
        middle_index = (move.start + move.end) / 2;
    }
    else if (starting_row_number < ending_row_number) { // If the move was down
        middle_index = (move.end - move.start) / 2 + move.start + 1;
    }
    else { // If the move was up
        middle_index = (move.start - move.end) / 2 + move.end + 1;
    }

    return middle_index;
}

bool Board::is_valid_move(Move move) const {
    bool is_valid = false;

    if (this->state[move.start] == 0) { // If the start index has no peg, the move is invalid
        is_valid = false;
    }
    else if (this->state[move.end] == 1) { // If the end index has a peg, the move is invalid
        is_valid = false;
    }
    else if (this->state[calculate_middle_index(move)] == 0) { // If the middle index has no peg, the move is invalid
        is_valid = false;
    }
    else if (abs(move.start - move.end) != 2 && abs(get_row_number_from_index(move.start) - get_row_number_from_index(move.end)) != 2) { // If the peg doesn't move two places, the move is invalid
        is_valid = false;
    }
    else { // Otherwise, the move is valid
        is_valid = true;
    }

    return is_valid;
}

bool Board::is_solved() const {
    return get_remaining_peg_count() == 1;
}

int Board::get_remaining_peg_count() const {
    int peg_count = 0;

    for (int peg_value : this->state) {
        if (peg_value == 1) {
            peg_count++;
        }
    }

    return peg_count;
}

bool Board::is_stalemate() const {
    return this->legal_moves.size() == 0;
}