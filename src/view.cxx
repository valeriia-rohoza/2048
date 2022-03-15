#include "view.hxx"

static ge211::Color const color_tiles {0, 255, 255};

View::View(Model const& model)
        : model_(model)
{
    for (int i=0; i<BOARD_SIZE; i++){
        std::vector<ge211::Rectangle_sprite> temp_row;
        for (int j=0; j<BOARD_SIZE; j++){
            temp_row.push_back(ge211::Rectangle_sprite(tile_dimensions_(), color_tiles));
        }
        tiles_sprite_.push_back(temp_row);
    }

    for (int i=0; i<BOARD_SIZE; i++){
        std::vector<ge211::Text_sprite> temp_row;
        for (int j=0; j<BOARD_SIZE; j++){
            temp_row.push_back(ge211::Text_sprite(std::to_string(model_.tile_value(i,j)), {"sans.ttf", 30}));
        }
        values_sprite_.push_back(temp_row);
    }
}

/* What do I need to draw:
        * - tiles with numbers
        * - button restart - if it's clicked, then we just call constructor again
        * - score number
        * - time of the game
        *
        *
*/


void
View::draw(ge211::Sprite_set& set)
{
    // if the game is over, then show (You won!) or (Big oops!) depending on the winner
    if (model_.game_over() && model_.player_won()){
        // show yaay!
        true;
    } else if (model_.game_over() && !model_.player_won()){
        // show big oops!
        true;
    } else {
        // add 16 white tiles
        for (int i=0; i<BOARD_SIZE; i++){
            for (int j=0; j<BOARD_SIZE; j++){
                set.add_sprite(tiles_sprite_[i][j], tile_position_(i, j));
                set.add_sprite(values_sprite_[i][j], tile_position_(i, j));
                // add numbers

            }
        }
    }
}

ge211::Dims<int> View::tile_dimensions_() const {
    // use the preset dimensions
    // 80% out of the height
    ge211::Dims<int> screen_size = {SCREEN_WIDTH, SCREEN_HEIGHT*SCALE/100};
    ge211::Dims<int> margin_size = {SIDE_MARGIN, TOP_MARGIN};

    int board_size = BOARD_SIZE;

    return (screen_size-2*margin_size)/board_size;
}

// position of the tile in pixels for a given position in i,j
const ge211::Posn<int> View::tile_position_(int i, int j) {
    ge211::Dims<int> tile = tile_dimensions_();
    return {SIDE_MARGIN + tile.width * j, TOP_MARGIN + tile.height * i};
}
