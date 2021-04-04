//
// Created by Carla on 15/03/2021.
//

#include "application.h"

template <typename E>
auto application::decorate(E&& e)
{
    return hsize(90, align_center(margin({ 20, 5, 20, 5 },
                                         std::forward<E>(e)
    )));
}

template <bool is_vertical>
auto application::make_markers()
{
    auto track = cycfi::elements::basic_track<5, is_vertical>();
    return cycfi::elements::slider_labels<10>(
        cycfi::elements::slider_marks<40>(track),         // Track with marks
        0.8,                             // Label font size (relative size)
        "-5", "-4", "-3", "-2", "-1",    // Labels
        "0", "1", "2", "3", "4", "5"
    );
}

auto application::make_label(std::string const &label_name){
    return vmargin({20.,20.},cycfi::elements::label(label_name));
}

auto application::make_text(std::string const &default_value){

    labels.emplace_back(cycfi::elements::share(cycfi::elements::label(default_value)));

    return layer(
        hold(labels.back()),
        cycfi::elements::frame{}
    );
}

auto application::make_dial()
{
    dials.emplace_back(share(
        dial(
            radial_marks<20>(cycfi::elements::basic_knob<50>()),
            0.5
        ))
    );

    auto markers = radial_labels<15>(
        hold(dials.back()),
        0.7,                                   // Label font size (relative size)
        "0", "1", "2", "3", "4",               // Labels
        "5", "6", "7", "8", "9", "10"
    );

    return align_center_middle(hmargin({20.,20.},markers));
}

auto application::make_toggle_button(std::string const &label_name, auto color) {

    toggle_buttons.emplace_back(cycfi::elements::share(toggle_button(label_name, 1.0, color)));
    
    return margin({10.,10.,10.,0.},hold(toggle_buttons.back()));
}

auto application::make_toggle_buttons() {


    return
        vmargin(
            {60.,20.},
            vtile(
                 make_toggle_button("Alert", bgreen),
                 make_toggle_button("Excited", bgreen),
                 make_toggle_button("Enthusiastic", bgreen),
                 make_toggle_button("Elated", bgreen),
                 make_toggle_button("Happy", bgreen),
                 make_toggle_button("Contented", bgreen),
                 make_toggle_button("Serene", bgreen),
                 make_toggle_button("Relaxed", bgreen),
                 make_toggle_button("Calm", bgreen),
                 make_toggle_button("Bored", bred),
                 make_toggle_button("Sluggish", bred),
                 make_toggle_button("Depressed", bred),
                 make_toggle_button("Sad", bred),
                 make_toggle_button("Upset", bred),
                 make_toggle_button("Stressed", bred),
                 make_toggle_button("Nervous", bred),
                 make_toggle_button("Tense", bred)
            )
        );
}

auto application::make_vertical_slider() {
    vertical_sliders.emplace_back(cycfi::elements::share(slider(
        cycfi::elements::basic_thumb<25>(),
        make_markers<true>(),
        0.5
    )));

    return align_center(hold(vertical_sliders.back()));
}

auto application::make_control(const std::string &label_name) {
    return
        vtile(
            make_label(label_name),
            make_vertical_slider(),
            cycfi::elements::margin({20.,20.,20.,0.}, make_text("-5.0"))
        );
}

auto application::make_player() {
    auto mbutton = cycfi::elements::button("Compose", 1.2);

    return
        vtile(
            margin({20., 0., 20., 20.},
                   htile(
                       cycfi::elements::icon_button(cycfi::elements::icons::pause, 1.2),
                       cycfi::elements::icon_button(cycfi::elements::icons::play, 1.2),
                       right_margin(20.0, cycfi::elements::icon_button(cycfi::elements::icons::stop, 1.2)),
                       fixed_size(
                           {140.0,20.0},
                           mbutton
                       )
                   )
            )
        );
}

auto application::make_features() {
    return margin({20.,0.,20.,20.},
                  htile(
                      vtile(
                          make_label("Tempo"),
                          make_dial(),
                          cycfi::elements::margin({20.,20.,20.,0.}, make_text("0")),
                          make_label("Dynamics"),
                          make_dial(),
                          cycfi::elements::margin({20.,20.,20.,0.}, make_text("0")),
                          make_label("Pitch"),
                          make_dial(),
                          cycfi::elements::margin({20.,20.,20.,0.}, make_text("0"))
                      ),
                      vtile(
                          make_label("Timbre"),
                          make_dial(),
                          cycfi::elements::margin({20.,20.,20.,0.}, make_text("0")),
                          make_label("Rhythm"),
                          make_dial(),
                          cycfi::elements::margin({20.,20.,20.,0.}, make_text("0")),
                          make_label("Label"),
                          make_dial(),
                          cycfi::elements::margin({20.,20.,20.,0.}, make_text("0"))
                      )
                  )
    );
}

auto application::make_controllers() {

    return margin({20.,0.,20.,20.},
                  cycfi::elements::htile(
                      make_control("Valence"),
                      make_control("Arousal"),
                      make_control("Originality")
                  )
    );
}

auto application::make_application() {

    return
        margin({ 20., 10., 20., 10. },
               vmin_size(400.,
                         htile(
                             valign(0.5, margin({ 10., 10., 10., 10. }, pane("Emotions",
                                                make_toggle_buttons(), 1.0F))),
                             vstretch(0.5, margin({ 10., 10., 10., 10. }, pane("Controllers", make_controllers(), 1.0F))),
                             vtile(
                                 hstretch(0.5, margin({ 10., 10., 10., 10. }, cycfi::elements::pane("Features", make_features(), 1.0F))),
                                 margin({ 10., 10., 10., 10. }, cycfi::elements::pane("Player", make_player()))
                             )
                         )
               )
        );
}

void application::dial_value(int dial_index, double value, cycfi::elements::view &view_) {

    dials[dial_index]->dial_base::value(value);
    view_.refresh(*dials[dial_index]);

    labels[(dial_index+3)]->set_text(std::to_string(value));
    view_.refresh(*labels[(dial_index+3)]);
}

void application::slider_value(int slider_index, double value, cycfi::elements::view &view_) {

    vertical_sliders[slider_index]->slider_base::value(value);
    view_.refresh(*vertical_sliders[slider_index]);

    labels[slider_index]->set_text(std::to_string(value));
    view_.refresh(*labels[slider_index]);
}

void application::toggle_button_value(size_t index, bool status, cycfi::elements::view &view_) {
        toggle_buttons[index]->value(status);
        view_.refresh(*toggle_buttons[index]);
}

void application::toggle_button_values(size_t index, double value, cycfi::elements::view &view_) {

    if(index == 0){
        if(value > 0.5){

            toggle_button_value(0, true, view_);
            toggle_button_value(2, true, view_);
            toggle_button_value(9, false, view_);
            toggle_button_value(11, false, view_);
        }
        else{
            toggle_button_value(0, false, view_);
            toggle_button_value(2, false, view_);
            toggle_button_value(9, true, view_);
            toggle_button_value(11,true, view_);
        }
    }

    if(index == 1){
        if(value > 0.5){

            toggle_button_value(1, true, view_);
            toggle_button_value(3, true, view_);
            toggle_button_value(10, false, view_);
            toggle_button_value(12, false, view_);
        }
        else{
            toggle_button_value(1, false, view_);
            toggle_button_value(3, false, view_);
            toggle_button_value(10, true, view_);
            toggle_button_value(12, true, view_);
        }
    }
}

void application::link_sliders(int index, cycfi::elements::view &view_) {

    vertical_sliders[index]->on_change =
        [index, &view_, this](double val){

          labels[index]->set_text(std::to_string(val));
          view_.refresh(*labels[index]);

          if(index == 0){
              dial_value(1, val, view_);
              dial_value(3, val, view_);
              dial_value(4, val, view_);
              toggle_button_values(index, val, view_);
          }

          if(index == 1){
              dial_value(0, val, view_);
              dial_value(2, val, view_);
              dial_value(3, val, view_);
              dial_value(4, val, view_);
              dial_value(5, val, view_);
              toggle_button_values(index, val, view_);
          }
        };
}

void application::link_dials(int index, cycfi::elements::view &view_) {
    int dials_index = index + 3;

    dials[index]->on_change =
        [index, dials_index, &view_, this](double val){

          labels[dials_index]->set_text(std::to_string(val));
          view_.refresh(*labels[dials_index]);

          if(index == 0 || index == 2 || index == 3 || index == 4 || index == 5){
              slider_value(1, val,view_);
              dial_value(2, val, view_);
              dial_value(3, val, view_);
              dial_value(4, val, view_);
              dial_value(5, val, view_);
              toggle_button_values(1, val, view_);
          }

          if(index == 1 || index == 3 || index == 4){
              slider_value(0, val,view_);
              dial_value(3, val, view_);
              dial_value(4, val, view_);
              toggle_button_values(0, val, view_);
          }
        };
}

void application::link_buttons(int index, cycfi::elements::view &view_) {

    double size          = toggle_buttons.size();
    double value         = (size - index)*(1.0/size);
    double value_arousal = index*(1.0/size);

    toggle_buttons[index]->on_click =
        [index, value, value_arousal, &view_, this](double status) {

              slider_value(0, value, view_);
              dial_value(0,value,view_);
              dial_value(1,value,view_);
              dial_value(2,value,view_);
              dial_value(3,value_arousal,view_);
              dial_value(4,value_arousal,view_);
              dial_value(5,value_arousal,view_);

              if(index <= toggle_buttons.size()/2){
                  slider_value(1, value, view_);
              }
              else{
                  slider_value(1, value_arousal, view_);
              }
        };
}

void application::link_controls(cycfi::elements::view &view_) {

    link_sliders(0, view_);
    link_sliders(1, view_);
    link_sliders(2, view_);
    link_dials(0, view_);
    link_dials(1, view_);
    link_dials(2, view_);
    link_dials(3, view_);
    link_dials(4, view_);
    link_dials(5, view_);

    for(size_t i = 0; i < toggle_buttons.size(); ++i){
        link_buttons(i,view_);
    }
}

// Initialize the application
// The application will stop when the window is closed
void application::initialize_application() {

    _window.on_close = [this]() { _app.stop(); };

    _view.content(
        make_application(),
        _background
    );

    link_controls(_view);
}

void application::run() {

    _app.run();
}