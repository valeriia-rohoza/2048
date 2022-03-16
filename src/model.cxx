#include "model.hxx"

Model::Model()
        :   score_(0),
            random_source_(BOARD_SIZE),
            game_over_(false),
            player_won_(false),
            timer_()
{
    int tile1_x = random_source_.next();
    int tile1_y = random_source_.next();

    // loop over all blocks and set them to 0
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            blocks_[i][j] = 0;
        }
    }
    blocks_[tile1_x][tile1_y] = 2;

//    for (int i=0; i<BOARD_SIZE; i++) {
//        for (int j = 0; j < BOARD_SIZE; j++) {
//            std::cout << blocks_[i][j] << " ";
//        }
//        std::cout << "\n";
//    }
    int tile2_x = tile1_x;
    int tile2_y = tile1_y;
    while (tile1_x == tile2_x && tile1_y == tile2_y){
        tile2_x = random_source_.next();
        tile2_y = random_source_.next();
    }
    blocks_[tile2_x][tile2_y] = 2;
}

// returns true if the position is within the board
// i and j are greater or equal 0
// AND i,j less than BOARD_SIZE
bool Model::on_board(ge211::Posn<int> posn){
    return (posn.x < BOARD_SIZE && posn.x >= 0 && posn.y < BOARD_SIZE && posn.y >= 0);
}

bool Model::on_board_single(int coord){
    return (coord < BOARD_SIZE && coord >= 0);
}

// return position of the next nonzero block
// return {-1,-1} if there is no next nonzero block
ge211::Posn<int> Model::next_nonzero(ge211::Posn<int> curr, ge211::Dims<int> direction){
    // move by one in the corresponding direction
    ge211::Posn<int> adjacent = curr + direction;
    // check whether still on the board
    // return {-1, -1} if not
    if (!on_board(adjacent)) {
        return {-1, -1};
    }
    // keep moving until you reach a nonzero
    while (blocks_[adjacent.x][adjacent.y] == 0){
        adjacent += direction;
        // return {-1, -1} if not
        if (!on_board(adjacent)) {
            return {-1, -1};
        }
    }
    return adjacent;
}

// compare the current block with the next nonzero block
bool Model::check_repeating(ge211::Posn<int> curr, ge211::Dims<int> direction) {
    ge211::Posn<int> adjacent = next_nonzero(curr, direction);

    // if there is no next nonzero block, then it returns -1,-1
    // so if the output is not on the board, it means there's none
    // in this case, return false
    if (!on_board(adjacent)){
        return false;
    }

    // compare the values of the current and the closest nonzero
    return blocks_[adjacent.x][adjacent.y] == blocks_[curr.x][curr.y];
}

void Model::update_score(int value) {
    score_ += value;
}

// while random tile is nonzero, keep choosing a random tile
// check that the board is not full, otherwise, do nothing
void Model::create_random_two() {
    if (!full_board()){
        int i = random_source_.next();
        int j = random_source_.next();

        while (blocks_[i][j] != 0) {
            i = random_source_.next();
            j = random_source_.next();
        }

        blocks_[i][j] = 2;
    }
}

// loop over all tiles and if there's a zero tile, return false
bool Model::full_board() {
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            if (blocks_[i][j] == 0){
                return false;
            }
        }
    }
    return true;
}

bool Model::is_2048_reached() {
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            if (blocks_[i][j] >= 2048){
                return true;
            }
        }
    }
    return false;
}

void Model::move_blocks(ge211::geometry::Dims<int> direction, int side, int incrementer) {
    // loop over all blocks
    // TODO: fix the iteration so that we start from the corresponding side and move one by one in the different dir
    for (int i=side; on_board_single(i); i += incrementer){
        for (int j=side; on_board_single(j); j += incrementer){
            // if it doesn't have a repeating pair
            // and the next position is on the board
            // and the next position is nonzero
            // set the next position to the current value
            // and set the current position to 0
            ge211::Posn<int> current = {i,j};
            ge211::Posn<int> next = current + direction;

            if (!check_repeating(current, direction) && on_board(next)){
                if (blocks_[next.x][next.y] == 0){
                    blocks_[next.x][next.y] = blocks_[current.x][current.y];
                    blocks_[current.x][current.y] = 0;
                }
            }

            // if it has a repeating pair
            if (check_repeating(current, direction)){
                ge211::Posn<int> adjacent = next_nonzero(current, direction);
                // set current to 0
                // adjacent doubles its value
                // update the score
                blocks_[current.x][current.y] = 0;
                blocks_[adjacent.x][adjacent.y] *= 2;

                // update the score
                update_score(blocks_[adjacent.x][adjacent.y]);
            }
        }
    }

    // check whether 2048 is reached
    player_won_ = is_2048_reached();

    // check whether the board is full
    // if it's full, the game is over
    if (full_board()){
        game_over_ = true;
    } else {
        // if the game is not over, create a random 2 tile
        create_random_two();
    }
}

// why do I need to put const here, not to change the variable
bool Model::game_over() const {
    return game_over_;
}

bool Model::player_won() const {
    return player_won_;
}

double Model::game_duration() const {
    return timer_.elapsed_time().seconds();
}

// get_tile_value
// get the value at two indices
int Model::get_tile_value(int i, int j) const {
    return blocks_[i][j];
}

// TODO: use the setter to set values of tiles, all fields
// set the value at two indices
void Model::set_tile_value(int i, int j, int value) {
    blocks_[i][j] = value;
}

void Model::set_game_over(bool status) {
    game_over_ = status;
}

void Model::set_player_won(bool status) {
    player_won_ = status;
}

//TODO: cleaner way to reset it
void Model::reset() {
    score_ = 0;
    game_over_ = false;
    player_won_ = false;
    timer_.reset();

    int tile1_x = random_source_.next();
    int tile1_y = random_source_.next();

    // loop over all blocks and set them to 0
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            blocks_[i][j] = 0;
        }
    }
    blocks_[tile1_x][tile1_y] = 2;

    int tile2_x = tile1_x;
    int tile2_y = tile1_y;
    while (tile1_x == tile2_x && tile1_y == tile2_y){
        tile2_x = random_source_.next();
        tile2_y = random_source_.next();
    }
    blocks_[tile2_x][tile2_y] = 2;
}

std::ostream&
operator<<(std::ostream& o, Model const& model)
{
    o << "Board {";
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            o << model.get_tile_value(i,j) << " ";
        }
    }
    return o << "}\n";
}