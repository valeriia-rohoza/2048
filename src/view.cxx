#include "view.hxx"

static ge211::Color const color_tiles {49,76,182};
static ge211::Color const color_inner_tiles {100,97,160};
static ge211::Color const color_restart {182,140,184};
static ge211::Color const color_background{239,189,235};

View::View(Model const& model)
        : model_(model),
        winner_message_("Yay!", {"sans.ttf", 30}),
        loser_message_("Big oops", {"sans.ttf", 30}),
        time_message_("0", {"sans.ttf", 20}),
        restart_button_({RESTART_SIDE, RESTART_SIDE}, color_restart),
        restart_message_("Restart", {"sans.ttf", 15}),
        score_message_("0", {"sans.ttf", 20})
{
    reset_tiles_();
}

/* What do I need to draw:
        * - tiles with numbers
        * - button restart - if it's clicked, then we just call constructor again
        * - score number
        * - time of the game
*/

void
View::draw(ge211::Sprite_set& set)
{
    // clear sprites
    clear_sprites_();
    reset_tiles_();

    ge211::Posn<int> message_posn = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
    // if the game is over, then show (You won!) or (Big oops!) depending on the winner
    if (model_.game_over() && model_.player_won()){
        // show yay!
        set.add_sprite(winner_message_, {message_posn.x - winner_message_.dimensions().width/2, message_posn.y - winner_message_.dimensions().height/2}, 10);
    } else if (model_.game_over() && !model_.player_won()){
        // show big oops!
        set.add_sprite(loser_message_, {message_posn.x - loser_message_.dimensions().width/2, message_posn.y - loser_message_.dimensions().height/2}, 10);
    } else {
        // add 16 white tiles
        for (int i=0; i<BOARD_SIZE; i++){
            for (int j=0; j<BOARD_SIZE; j++){
                set.add_sprite(tiles_sprite_[i][j], tile_position_(i, j), 1);
                set.add_sprite(inner_tiles_sprite_[i][j], inner_tile_position_(i, j), 5);
                set.add_sprite(values_sprite_[i][j], inner_tile_position_(i,j), 10);
                // add numbers
            }
        }

        time_message_ = ge211::Text_sprite(std::to_string(model_.game_duration()), {"sans.ttf", 20});
        ge211::Posn<int> time_posn = {TIMER_MARGIN, TIMER_MARGIN};
        set.add_sprite(time_message_, time_posn, 20);

        ge211::Posn<int> restart_posn = {SCREEN_WIDTH-RESTART_MARGIN-RESTART_SIDE, RESTART_MARGIN_SIDE};
        set.add_sprite(restart_button_, restart_posn, 1);
        set.add_sprite(restart_message_, {restart_posn.x + (RESTART_SIDE - restart_message_.dimensions().width)/2, restart_posn.y + RESTART_SIDE/2 - restart_message_.dimensions().height/2}, 10);

        score_message_ = ge211::Text_sprite(std::to_string(model_.get_score()), {"sans.ttf", 20});
        ge211::Posn<int> score_posn = {SCREEN_WIDTH/3, TIMER_MARGIN};
        set.add_sprite(score_message_, score_posn, 30);
    }
}

ge211::Dims<int> View::tile_dimensions_() const {
    // use the preset dimensions
    // 80% out of the height
    ge211::Dims<int> screen_size = {SCREEN_WIDTH, SCREEN_HEIGHT*SCALE/100};
    int margin_size = SIDE_MARGIN;

    int board_size = BOARD_SIZE;

    // (screen_size-2*margin_size)/board_size
    return {(screen_size.width - 2*margin_size)/board_size,(screen_size.height - 2*margin_size)/board_size};
}

ge211::Dims<int> View::inner_tile_dimensions_() const {
    return {tile_dimensions_().width * (100 - 2*TILE_SCALE)/100, tile_dimensions_().height * (100 - 2*TILE_SCALE)/100};
}


// position of the tile in pixels for a given position in i,j
const ge211::Posn<int> View::tile_position_(int i, int j) {
    ge211::Dims<int> tile = tile_dimensions_();
    return {SIDE_MARGIN + tile.width * j, TOP_MARGIN + tile.height * i};
}

const ge211::Posn<int> View::inner_tile_position_(int i, int j) {
    ge211::Dims<int> tile = tile_dimensions_();
    return {SIDE_MARGIN + tile.width * j + TILE_SCALE*tile.width/100, TOP_MARGIN + tile.height * i + TILE_SCALE*tile.height/100};
}

void View::clear_sprites_() {
    for (int i=0; i<BOARD_SIZE; i++){
        tiles_sprite_[i].clear();
        inner_tiles_sprite_[i].clear();
        values_sprite_[i].clear();
    }
    tiles_sprite_.clear();
    inner_tiles_sprite_.clear();
    values_sprite_.clear();
}

void View::reset_tiles_() {
    for (int i=0; i<BOARD_SIZE; i++){
        std::vector<ge211::Rectangle_sprite> temp_row;
        for (int j=0; j<BOARD_SIZE; j++){
            temp_row.push_back(ge211::Rectangle_sprite(tile_dimensions_(), color_tiles));
        }
        tiles_sprite_.push_back(temp_row);
    }

    for (int i=0; i<BOARD_SIZE; i++){
        std::vector<ge211::Rectangle_sprite> inner_temp_row;
        for (int j=0; j<BOARD_SIZE; j++){
            inner_temp_row.push_back(ge211::Rectangle_sprite(inner_tile_dimensions_(), color_inner_tiles));
        }
        inner_tiles_sprite_.push_back(inner_temp_row);
    }

    for (int i=0; i<BOARD_SIZE; i++){
        std::vector<ge211::Text_sprite> temp_row_text;
        for (int j=0; j<BOARD_SIZE; j++){
            int temp_tile_value = model_.get_tile_value(i,j);
            if (temp_tile_value == 0){
                temp_row_text.push_back(ge211::Text_sprite(" ", {"sans.ttf", 64}));
            } else {
                temp_row_text.push_back(ge211::Text_sprite(std::to_string(temp_tile_value), {"sans.ttf", 30}));
            }
        }
        values_sprite_.push_back(temp_row_text);
    }

}