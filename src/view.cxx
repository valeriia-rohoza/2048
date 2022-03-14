#include "view.hxx"

View::View(Model const& model)
        : model_(model)
{ }

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
        // the game continues
        true;
    }
}

//ge211::Posn<int> View::screen_to_board(ge211::Posn<int>) const {
//    return ge211::Posn<int>(0, 0);
//}
//
//ge211::Posn<int> View::board_to_screen(ge211::Posn<int>) const {
//    return ge211::Posn<int>(0, 0);
//}
