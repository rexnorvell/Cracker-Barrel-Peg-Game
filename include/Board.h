#ifndef BOARD_H
#define BOARD_H

#include "Move.h"

#include <vector>
#include <utility>

class Board {
    public:
        static constexpr int BOARD_SIZE = 15;
        static constexpr int NUM_ROWS = 5;
        static constexpr int MAX_ROW_SIZE = 5;
        static constexpr int MIN_ROW_SIZE = 1;
        static constexpr int MIN_ROW_NUMBER = 0;
        static constexpr int MAX_ROW_NUMBER = 4;
        static constexpr const char* PEG_ICON = "●";
        static constexpr const char* HOLE_ICON = "○";
    
        Board(const std::array<int, BOARD_SIZE>& state = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0});
        void execute_move(Move move);
        
        void print_state() const;
        void print_legal_moves() const;
        std::vector<Move> get_legal_moves() const;
        Board get_next_board(Move move) const;
        std::array<int, BOARD_SIZE> get_state();
        bool is_solved() const;
        bool is_stalemate() const;
        int get_remaining_peg_count() const;
    
    private:
        std::array<int, BOARD_SIZE> state;
        std::vector<Move> legal_moves;

        std::vector<Move> calculate_legal_moves();
        
        bool is_valid_move(Move move) const;
        int calculate_middle_index(Move move) const;
        int get_row_number_from_index(int index) const;
};

#endif