/**
  * \file toplevel_test.cpp
  * \brief contains class \ref ei::Toplevel_test definition
  * \author Bah elhadj amadou
  */


#include "toplevel_test.h"

ei::Toplevel_test::Toplevel_test() : Toplevel (nullptr)
{
    app_size = Size(1000, 1000);
    app = new Application(&app_size);
}

ei::Toplevel_test::~Toplevel_test(){
    delete app;
}

bool ei::Toplevel_test::get_resizable_test(){
    resizable = ei_axis_x;
    return get_resizable() == ei_axis_x;
}

bool ei::Toplevel_test::get_minimum_size_test(){
    min_size = ei::Size(100, 100);
    return get_minimum_size() == ei::Size(100, 100);
}

bool ei::Toplevel_test::set_content_rect_test(){
    int x(10), y(10);
    float width(100), height(100);
    border_width = 5;
    set_content_rec(&x, &y, &width, &height);

    return get_content_rect().top_left == ei::Point(x + border_width, y + ei::Toplevel::title_bar_height) && get_content_rect().size == ei::Size(90, 95 - ei::Toplevel::title_bar_height);
}

bool ei::Toplevel_test::ToplevelTest(){
    bool is_correct(true);
    is_correct = is_correct && title != nullptr;
    is_correct = is_correct && but_close != nullptr;
    is_correct = is_correct && but_resize != nullptr;
    is_correct = is_correct && but_close->get_geom_manager() != nullptr;
    is_correct = is_correct && but_resize->get_geom_manager() != nullptr;
    return is_correct;
}
