#pragma once

#include "model.hxx"

// set the screen dimensions and margins

#define SCREEN_WIDTH (820)
#define SCREEN_HEIGHT (1024)
#define TOP_MARGIN (100)
#define SIDE_MARGIN (100)
#define SCALE (80)

class View
{
public:
    explicit View(Model const& model);

    // draw BOARD_SIZE*BOARD_SIZE rectangles
    //
    void draw(ge211::Sprite_set& set);

    // TODO: initialize a vector of 16 rectangle sprites and 16 corresponding text sprites
    // match the indices with the board
    // text sprite for the score in bejeweled
    // add some space into the score when deciding on the positions

//    /// Returns the size of the window as given by `config.scene_dims`.
//    ge211::Dims<int> initial_window_dimensions() const;

    // loop over the blocks and draw the corresponding text
    // if 0, puts an empty sprite
    //

private:
    Model const& model_;
    // 2D array of Rectangle sprites to represent tiles
    // ge211::Rectangle_sprite tile_sprite;
    std::vector<std::vector<ge211::Rectangle_sprite>> tiles_sprite_;
    std::vector<std::vector<ge211::Text_sprite>> values_sprite_;
    // dimensions of the tile in pixels
    ge211::Dims<int> tile_dimensions_() const;
    // position for a given i, j
    const ge211::Posn<int> tile_position_(int i, int j);
};
