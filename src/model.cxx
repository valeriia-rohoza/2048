#include "model.hxx"

// TODO: check whether I initialize the blocks correctly
Model::Model()
        : blocks_{0},
            score_(0),
            random_source_(BOARD_SIZE)
{
    int tile1_x = random_source_.next();
    int tile1_y = random_source_.next();

    blocks_[tile1_x][tile1_y] = 2;

    int tile2_x = random_source_.next();
    int tile2_y = random_source_.next();
    while (tile1_x == tile2_x && tile2_x == tile2_y){
        tile2_x = random_source_.next();
        tile2_y = random_source_.next();
    }
//    // add two tiles with 2 at random places
//    for (int k=0; k<2; k++){
//        blocks_[random_source_.next()][random_source_.next()] = 2;
//    }

    // ge211::geometry::Posn<int> first_tile = {random_source_.next(), random_source_.next()};
    // blocks_[first_tile.x][first_tile.y] = 2;
    // TODO: make sure that the second random tile does not overlap with the first one
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
            // otherwise, do nothing
        }
    }
}