#pragma once

#include <ge211.hxx>
#include <iostream>
// size of the board BOARD_SIZE by BOARD_SIZE
#define BOARD_SIZE (4)

// using namespace ge211::time;
// The model tracks the logical state of the game, independent of the
// presentation and control. In particular, it keeps track of:
//
//  - a 2D array of int (int board[4][4];) to store the values of the blocks
//  - current score
//  - game status (is it over or not)
//  - game results (whether won or not)
//
// It also provides member functions to help the UI in updating it

class Model
{
public:
    ///
    /// Associated types
    ///

    ///
    /// Constructors
    ///
    // 4 by 4 board, all tiles but two are zeros
    // and two randomly-selected tiles have values of 2
    explicit Model();

    // HERE ARE ALL FUNCTIONS;
    // Given a 2D array of blocks (which we access through the model)
    // and passing Posn<int> coordinates, and Dims<int> for the direction
    // check whether two adjacent nonzero blocks form a repeating pair
    // special case:
    // check whether the next nonzero block is still within the board before adding direction

    // update the score
    // the score starts at zero and is increased whenever two tiles combine by the value of the new tile
    // pass score by reference and the value of a new block
    void update_score(int value);

    bool check_repeating(ge211::Posn<int> coordinates, ge211::Dims<int> direction);

    // create one tile with 2 in place of the empty tile
    // it means that the board was full before the swipe, and no reduction happened
    // then the game is over
    // while random tile is nonzero, keep choosing random tiles
    // once found a zero tile, set it to 2
    void create_random_two();

    // check whether the game is over
    // loop over all tiles and if there's a zero tile, return false
    // otherwise, return true
    bool full_board();

    // check whether the largest tile has a value of 2048 (or larger because it's implied)
    // since check each time, it's ok to == 2048, but nothing bad happens if >= 2048
    bool is_2048_reached();

    /* How blocks move?
     * Pressing the right arrow button.
     * The right-most non-zero block will move by 1 if it's allowed (the block should remain on the board).
     * Then the second right-most non-zero block checked whether it and the right-most block
     * form a repeating or non-repeating pair
     * If it's a non-repeating pair, then the block moves to the right by 1 if it's allowed
     * (the block should not overlap with other blocks); then we do the same to the third right-most block.
     * If the second right-most and the right-most blocks form a repeating pair,
     * then the second right-most block disappears and the right-most block doubles its value.
     * Then we do the same for the third right-most block;
     * note that if the most recent value of the right-most block and the third right-most block form a repeating pair
     * (while the 2nd right-most block got destroyed), the reduction will happen the same way.
     *
     * Thoughts:
     * Number all blocks (0,0) in the top left corner and to the right, (0,1)...
     *                                                  down (1,0), ...
     * move_blocks takes displacement, which can be either
     * - (1,0) down
     * - (-1,0) up
     * - (0,1) right
     * - (0,-1) left
     *
     * takes side coordinate & increment, which can be either
     * - (3, -1) right
     * - (0, 1) left
     * - (0, 1) up
     * - (3, -1) down
     *
     * Loop over all blocks (two for loops for rows/columns)
     * check while it's within a board
     * For each block, call check_repeating
     * if false, if at Posn_curr + Posn_disp is within board and is zero, then replace the current cell by 0 and
     * Posn_curr + Posn_disp by current value
     * if true, curr = 0 and the next nonzero one doubles its value; update score by the value of a new tile
     * otherwise, do nothing
     * */
    void move_blocks(ge211::geometry::Dims<int> direction, int side, int incrementer);

    // check whether the current position is on the board
    // i and j are greater or equal 0
    // AND i,j less than BOARD_SIZE
    bool on_board(ge211::Posn<int> posn);
    bool on_board_single(int coord);
    ge211::Posn<int> next_nonzero(ge211::Posn<int> curr, ge211::Dims<int> direction);
    bool game_over() const;
    bool player_won() const;
    double game_duration() const;
    int get_tile_value(int i, int j) const;
    void set_tile_value(int i, int j, int value);
    void set_game_over(bool status);
    void set_player_won(bool status);
    void reset();
    int get_score() const;
    ///
    /// Public member functions
    ///

private:
    ///
    /// Private helper functions
    ///

    ///
    /// Private member variables
    ///
    // 2D array of blocks
    int blocks_[BOARD_SIZE][BOARD_SIZE];
    int score_;
    ge211::Random_source<int> random_source_;
    bool game_over_;
    bool player_won_;
    ge211::Timer timer_;
};
