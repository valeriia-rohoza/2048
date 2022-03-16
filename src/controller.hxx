#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    Controller();
    ge211::Dims<int> initial_window_dimensions() const override;
    bool on_restart(ge211::Posn<int> posn);

protected:
    void draw(ge211::Sprite_set& set) override;
    void on_key(ge211::Key key) override;
    void on_mouse_up(ge211::Mouse_button, ge211::Posn<int>) override;

private:
    Model model_;
    View view_;
};
