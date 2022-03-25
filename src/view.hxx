#pragma once

#include "model.hxx"

// set the screen dimensions and margins
#define SCREEN_WIDTH (640)
#define SCREEN_HEIGHT (640)
#define TOP_MARGIN (100)
#define SIDE_MARGIN (100)
#define SCALE (100)
#define TIMER_MARGIN (10)
#define RESTART_SIDE (50)
#define RESTART_MARGIN (50)
#define TILE_SCALE (10)
#define RATIO_PT_PX (75)

class View
{
public:
    explicit View(Model const& model);

    // draw BOARD_SIZE*BOARD_SIZE rectangles
    //
    void draw(ge211::Sprite_set& set);

    // initialize a vector of 16 rectangle sprites and 16 corresponding text sprites
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
    std::vector<std::vector<ge211::Rectangle_sprite>> inner_tiles_sprite_;
    std::vector<std::vector<ge211::Text_sprite>> values_sprite_;
    ge211::Text_sprite winner_message_;
    ge211::Text_sprite loser_message_;
    ge211::Text_sprite time_message_;
    ge211::Rectangle_sprite restart_button_;
    ge211::Text_sprite restart_message_;
    ge211::Text_sprite score_message_;
    // dimensions of the tile in pixels
    ge211::Dims<int> tile_dimensions_() const;
    ge211::Dims<int> inner_tile_dimensions_() const;
    // position for a given i, j
    const ge211::Posn<int> tile_position_(int i, int j);
    const ge211::Posn<int> inner_tile_position_(int i, int j);
    // clear all sprites
    void clear_sprites_();
    void reset_tiles_();
};
