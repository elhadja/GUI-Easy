/**
 * @file    ei_check_box.cpp
 *
 * @brief   contains classe \ref Check_box definition
 *  created by Bah elhadj amadou
 */


#include "ei_check_box.h"
#include "ei_application.h"

#include <iostream>

ei::Check_box::Check_box(Widget* parent): Widget ("Check_box", parent)
{
    if(ei::Application::VERBOSE)
        std::cout<<"=====> making a Check_box "<<std::endl;
    requested_size = ei::Size(20, 20);
    tag_id.push_back("ei_check_box");
    checked = false;
    if(parent != nullptr){
        parent->set_children(this);
        tooltip = new Tooltip(this);
    }
}

ei::Check_box::~Check_box(){}

void ei::Check_box::draw (surface_t surface,
                          surface_t pick_surface,
                          Rect*     clipper){
    assert(surface != nullptr && pick_surface != nullptr);
    if(ei::Application::VERBOSE)
        std::cout<<"=====> drawing a check_box :"<<name<<std::endl;
    // check if the widget exceeds his parent
    ei::Rect *new_clipper = clipper;
    bool exceeds = overflow(&new_clipper);
    if(out)
        return;
    /* get size and top left */
    Size size = screen_location.size;
    Point top_left = get_top_left();
    // drawing the check_box
    linked_point_t list_point = rounded_frame(ei::Rect(ei::Point(get_top_left().x(), get_top_left().y()), ei::Size(screen_location.size.width(), screen_location.size.height())), 0, BT_FULL);
    draw_polyline(surface, list_point, bckground_color, new_clipper);
    if(checked){
        draw_line(surface, get_top_left(), ei::Point(get_top_left().x() + screen_location.size.width(), get_top_left().y() + screen_location.size.height()), bckground_color, clipper);
        draw_line(surface, ei::Point(get_top_left().x() + screen_location.size.width(), get_top_left().y()), ei::Point(get_top_left().x(), get_top_left().y() + screen_location.size.height()), bckground_color, clipper);
    }

    ei::Widget::draw(surface, pick_surface, new_clipper);

    if(exceeds)
        delete new_clipper;
}

void ei::Check_box::set_content_rec(int *x, int *y, float* width, float* height){}

bool ei::Check_box::is_checked() const{
    return checked;
}

void ei::Check_box::set_checked(bool val){
    checked = val;
}

std::string ei::Check_box::get_type() const
{
    return "Check_box";
}
