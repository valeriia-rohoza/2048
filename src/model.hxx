#pragma once

#include <ge211.hxx>
// size of the board BOARD_SIZE by BOARD_SIZE
#define BOARD_SIZE (4)

// The model tracks the logical state of the game, independent of the
// presentation and control. In particular, it keeps track of:
//
//  - the game configuration (the sizes of things such as blocks, the screen)
//  - a 2D array of int (int board[4][4];) to store the values of the blocks
//  - current score
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

    // HERE ARE ALL FUNCTIONS; TODO: decide later which one should be private or public
    // Given a 2D array of blocks (which we access through the model)
    // and passing Posn<int> coordinates, and Posn<int> for the direction
    // check whether two adjacent nonzero blocks form a repeating pair
    // special case:
    // check whether the next nonzero block is still within the board before adding direction
    // TODO: return block_value_1 == block_value_2
    bool check_repeating();

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
     * Loop over all blocks (two for loops for rows/columns)
     * check while it's within a board
     * For each block, call check_repeating
     * if false, if at Posn_curr + Posn_disp is within board and is zero, then replace the current cell by 0 and
     * Posn_curr + Posn_disp by current value
     * if true, curr = 0 and the next nonzero one doubles its value; update score by the value of a new tile
     * otherwise, do nothing
     * */
    void move_blocks(ge211::geometry::Posn<int> displacement);

    // update the score
    // the score starts at zero and is increased whenever two tiles combine by the value of the new tile
    // pass score by reference and the value of a new block
    void update_score();

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
};
