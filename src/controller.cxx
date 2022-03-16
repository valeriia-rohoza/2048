#include "controller.hxx"

Controller::Controller()
        : view_(model_)
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

void Controller::on_key(ge211::Key key) {

    if (key == ge211::Key::code('q'))
        quit();
    else if (key == ge211::Key::up()){
        // if up is pressed
        model_.move_blocks({-1, 0}, 0, 1);

    } else if (key == ge211::Key::down()){
        // if down is pressed
        model_.move_blocks({1,0}, 3, -1);
    } else if (key == ge211::Key::left()){
        // if left is pressed
        model_.move_blocks({0,-1}, 0, 1);
    } else if (key == ge211::Key::right()) {
        // if right is pressed
        model_.move_blocks({0,1}, 3, -1);
    }
}
