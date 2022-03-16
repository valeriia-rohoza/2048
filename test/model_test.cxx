#include "model.hxx"
#include <catch.hxx>

//
//
// These tests should demonstrate your functional requirements.
//

/* List of tests for my code:
 * - check that the game is over when the board is full
 * - apply next_nonzero to 2 0 0 2 (2, 2), 2 2 0 0 (2,2), 2 0 0 0 (none)
 * - update score changes the score
 * - check whether create_random_two add a tile of 2, does nothing when the board is full
 * - create a full board and apply full_board, delete one element and non full
 * - move_blocks
 * */

// the game is over when the board is full
TEST_CASE("game is over when the board is full"){
    Model m;
    // set the board to 2
    int val = 2;
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
              m.set_tile_value(i,j,val);
        }
    }
    // board is full
    CHECK(m.full_board() == true);
    m.set_game_over(true);
    // then set the game to over
    CHECK(m.game_over() == true);
}

TEST_CASE("initialize model"){
    int repeats = 10;
    int count_two = 0;
    for (int k=0; k<repeats; k++){
        Model m;
        for (int i=0; i<BOARD_SIZE; i++){
            for (int j=0; j<BOARD_SIZE; j++){
                if (m.get_tile_value(i, j) == 2){
                    count_two += 1;
                }
            }
        }
    }
    CHECK(count_two == repeats * 2);
}

TEST_CASE("next nonzero is -1,-1"){
    /* 0 0 0 0
     * 0 0 0 0
     * 0 0 0 0
     * 0 0 0 0
     * */
    // next nonzero is 0
    Model m;
    std::vector<ge211::Dims<int>> dirs;
    dirs.push_back({1,0});
    dirs.push_back({-1,0});
    dirs.push_back({0,1});
    dirs.push_back({0,-1});

    // set the board to 0
    int val = 0;
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            m.set_tile_value(i,j,val);
        }
    }
    for (int k=0; k<4; k++){
        ge211::Posn<int> result = {-1, -1};
        CHECK(m.next_nonzero({2,2},dirs[k]) == result);
    }

    for (int k=0; k<4; k++){
        ge211::Posn<int> result = {-1, -1};
        CHECK(m.next_nonzero({0,0}, dirs[k]) == result);
    }
}

TEST_CASE("check non_zero with 2"){
    /* 0 0 2 0
     * 0 0 0 0
     * 2 0 2 2
     * 0 0 2 0
     * */
    // next nonzero is 0
    Model m;
    std::vector<ge211::Dims<int>> dirs;
    dirs.push_back({1,0});
    dirs.push_back({-1,0});
    dirs.push_back({0,1});
    dirs.push_back({0,-1});

    // set the board to 0
    int val1 = 0;
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            m.set_tile_value(i,j,val1);
        }
    }
    int val2 = 2;
    std::vector<ge211::Posn<int>> results;
    results.push_back({3, 2});
    results.push_back({0, 2});
    results.push_back({2, 3});
    results.push_back({2, 0});
    results.push_back({2, 2});

    for (int l=0; l<5; l++){
        m.set_tile_value(results[l].x, results[l].y, val2);
    }

    for (int f=0; f<4; f++){
        CHECK(m.next_nonzero({2,2}, dirs[f]) == results[f]);
    }
}

TEST_CASE("check_repeating test, all true"){
    /* 0 0 2 0
     * 0 0 0 0
     * 2 0 2 2
     * 0 0 2 0
     * */
    // next nonzero is 0
    Model m;
    std::vector<ge211::Dims<int>> dirs;
    dirs.push_back({1,0});
    dirs.push_back({-1,0});
    dirs.push_back({0,1});
    dirs.push_back({0,-1});

    // set the board to 0
    int val1 = 0;
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            m.set_tile_value(i,j,val1);
        }
    }
    int val2 = 2;
    std::vector<ge211::Posn<int>> results;
    results.push_back({3, 2});
    results.push_back({0, 2});
    results.push_back({2, 3});
    results.push_back({2, 0});
    results.push_back({2, 2});

    for (int l=0; l<5; l++){
        m.set_tile_value(results[l].x, results[l].y, val2);
    }

    for (int f=0; f<4; f++){
        CHECK(m.check_repeating({2,2}, dirs[f]));
    }
}

TEST_CASE("check_repeating test, all false"){
    /* 0 0 4 0
     * 0 0 0 0
     * 4 0 2 4
     * 0 0 4 0
     * */
    Model m;
    std::vector<ge211::Dims<int>> dirs;
    dirs.push_back({1,0});
    dirs.push_back({-1,0});
    dirs.push_back({0,1});
    dirs.push_back({0,-1});

    // set the board to 0
    int val1 = 0;
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            m.set_tile_value(i,j,val1);
        }
    }
    int val2 = 2;
    std::vector<ge211::Posn<int>> results;
    results.push_back({3, 2});
    results.push_back({0, 2});
    results.push_back({2, 3});
    results.push_back({2, 0});
    results.push_back({2, 2});

    for (int l=0; l<4; l++){
        m.set_tile_value(results[l].x, results[l].y, val2);
    }
    int val3 = 4;
    m.set_tile_value(results[4].x, results[4].y, val3);

    for (int f=0; f<4; f++){
        CHECK(!m.check_repeating({2,2}, dirs[f]));
    }
}

TEST_CASE("check_repeating test, all zeros and false"){
    /* 0 0 0 0
     * 0 0 0 0
     * 0 0 0 0
     * 0 0 0 0
     * */
    Model m;
    std::vector<ge211::Dims<int>> dirs;
    dirs.push_back({1,0});
    dirs.push_back({-1,0});
    dirs.push_back({0,1});
    dirs.push_back({0,-1});

    // set the board to 0
    int val1 = 0;
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            m.set_tile_value(i,j,val1);
        }
    }
    for (int f=0; f<4; f++){
        CHECK(!m.check_repeating({2,2}, dirs[f]));
    }
}

// - check whether create_random_two add a tile of 2, does nothing when the board is full
TEST_CASE("create_random_two does nothing when the board is full"){
    Model m;
    // set the board to 4
    int val = 4;
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            m.set_tile_value(i,j,val);
        }
    }
    // board is full

    m.create_random_two();
    int count_two=0;
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            if (m.get_tile_value(i,j) == 2){
                count_two += 1;
            }
        }
    }
    CHECK(count_two == 0);
}

// create a random two
TEST_CASE("creates random two on an empty board"){
    Model m;
    // set the board to 0
    int val = 0;
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            m.set_tile_value(i,j,val);
        }
    }
    m.create_random_two();
    int count_two=0;
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            if (m.get_tile_value(i,j) == 2){
                count_two += 1;
            }
        }
    }
    CHECK(count_two == 1);
}

TEST_CASE("check move_blocks up"){
    Model m;
    // set the board to 0
    int val1 = 0;
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            m.set_tile_value(i,j,val1);
        }
    }
    int val2 = 2;
    std::vector<ge211::Posn<int>> results;
    results.push_back({3, 2});
    results.push_back({0, 2});
    results.push_back({2, 3});
    results.push_back({2, 0});
    results.push_back({2, 2});

    for (int l=0; l<5; l++){
        m.set_tile_value(results[l].x, results[l].y, val2);
    }

    // the board is set as following
    /* 0 0 2 0
     * 0 0 0 0
     * 2 0 2 2
     * 0 0 2 0
     * */

    // as if we pressed up
    m.move_blocks({-1, 0}, 0, 1);
    // the board should be as following and extra 2 at the random place
    /* 0 0 4 0
     * 2 0 0 2
     * 0 0 2 0
     * 0 0 0 0
     * */

    CHECK(m.get_tile_value(0, 2) == 4);
    CHECK(m.get_tile_value(1, 0) == 2);
    CHECK(m.get_tile_value(1, 3) == 2);
    CHECK(m.get_tile_value(2, 2) == 2);

    int count_two=0;
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            if (m.get_tile_value(i,j) == 2){
                count_two += 1;
            }
        }
    }
    // three plus one random
    CHECK(count_two == 4);
}

TEST_CASE("check move_blocks down"){
    Model m;
    // set the board to 0
    int val1 = 0;
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            m.set_tile_value(i,j,val1);
        }
    }
    int val2 = 2;
    std::vector<ge211::Posn<int>> results;
    results.push_back({3, 2});
    results.push_back({0, 2});
    results.push_back({2, 3});
    results.push_back({2, 0});
    results.push_back({2, 2});

    for (int l=0; l<5; l++){
        m.set_tile_value(results[l].x, results[l].y, val2);
    }

    // the board is set as following
    /* 0 0 2 0
     * 0 0 0 0
     * 2 0 2 2
     * 0 0 2 0
     * */

    // as if we pressed down
    m.move_blocks({1,0}, 3, -1);
    // the board should be as following and extra 2 at the random place
    /* 0 0 0 0
     * 0 0 2 0
     * 0 0 0 0
     * 2 0 4 2
     * */

    CHECK(m.get_tile_value(1, 2) == 2);
    CHECK(m.get_tile_value(3, 0) == 2);
    CHECK(m.get_tile_value(3, 2) == 4);
    CHECK(m.get_tile_value(3, 3) == 2);

    int count_two=0;
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            if (m.get_tile_value(i,j) == 2){
                count_two += 1;
            }
        }
    }
    // three plus one random
    CHECK(count_two == 4);
}

TEST_CASE("check move_blocks right"){
    Model m;
    // set the board to 0
    int val1 = 0;
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            m.set_tile_value(i,j,val1);
        }
    }
    int val2 = 2;
    std::vector<ge211::Posn<int>> results;
    results.push_back({3, 2});
    results.push_back({0, 2});
    results.push_back({2, 3});
    results.push_back({2, 0});
    results.push_back({2, 2});

    for (int l=0; l<5; l++){
        m.set_tile_value(results[l].x, results[l].y, val2);
    }

    // the board is set as following
    /* 0 0 2 0
     * 0 0 0 0
     * 2 0 2 2
     * 0 0 2 0
     * */

    // as if we pressed right
    m.move_blocks({0,1}, 3, -1);
    // the board should be as following and extra 2 at the random place
    /* 0 0 0 2
     * 0 0 0 0
     * 0 2 0 4
     * 0 0 0 2
     * */

    CHECK(m.get_tile_value(0, 3) == 2);
    CHECK(m.get_tile_value(2, 1) == 2);
    CHECK(m.get_tile_value(2, 3) == 4);
    CHECK(m.get_tile_value(3, 3) == 2);

    int count_two=0;
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            if (m.get_tile_value(i,j) == 2){
                count_two += 1;
            }
        }
    }
    // three plus one random
    CHECK(count_two == 4);
}

TEST_CASE("check move_blocks left"){
    Model m;
    // set the board to 0
    int val1 = 0;
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            m.set_tile_value(i,j,val1);
        }
    }
    int val2 = 2;
    std::vector<ge211::Posn<int>> results;
    results.push_back({3, 2});
    results.push_back({0, 2});
    results.push_back({2, 3});
    results.push_back({2, 0});
    results.push_back({2, 2});

    for (int l=0; l<5; l++){
        m.set_tile_value(results[l].x, results[l].y, val2);
    }

    // the board is set as following
    /* 0 0 2 0
     * 0 0 0 0
     * 2 0 2 2
     * 0 0 2 0
     * */

    // as if we pressed left
    m.move_blocks({0,-1}, 0, 1);
    // the board should be as following and extra 2 at the random place
    /* 0 2 0 0
     * 0 0 0 0
     * 4 0 2 0
     * 0 2 0 0
     * */

    CHECK(m.get_tile_value(0, 1) == 2);
    CHECK(m.get_tile_value(2, 0) == 4);
    CHECK(m.get_tile_value(2, 2) == 2);
    CHECK(m.get_tile_value(3, 1) == 2);

    int count_two=0;
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            if (m.get_tile_value(i,j) == 2){
                count_two += 1;
            }
        }
    }
    // three plus one random
    CHECK(count_two == 4);
}

TEST_CASE("check move_blocks for the full board of different values"){
    Model m;
    // set the board to different values
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            m.set_tile_value(i,j,(i+1)*(j+1));
        }
    }

    // the board is set as following
    /* 1 2 3 4
     * 2 4 . .
     * 3 . . .
     * 4 . . 16
     * */

    std::vector<ge211::Dims<int>> dirs;
    dirs.push_back({1,0});
    dirs.push_back({-1,0});
    dirs.push_back({0,1});
    dirs.push_back({0,-1});

    std::vector<ge211::Dims<int>> side_incr;
    side_incr.push_back({3,-1});
    side_incr.push_back({0,1});
    side_incr.push_back({3,-1});
    side_incr.push_back({0,1});

    // as if we pressed any
    for (int f=0; f<4; f++){
        m.move_blocks(dirs[f], side_incr[f].width, side_incr[f].height);
        for (int i=0; i<BOARD_SIZE; i++){
            for (int j=0; j<BOARD_SIZE; j++){
                CHECK(m.get_tile_value(i,j) == (i+1)*(j+1));
            }
        }

        CHECK(m.full_board() == true);
        CHECK(m.game_over() == true);
        m.set_game_over(false);
    }
}

