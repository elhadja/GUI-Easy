/**
 * @file    ei_button_radio.cpp
 *
 * @brief   contains classes definitions: \ref Button_radio, \ref RB_Groupe
 *  created by Bah elhadj amadou
 */


#include "ei_button_radio.h"
#include "ei_application.h"
#include "ei_geometrymanager.h"

#include <iostream>
#include <assert.h>

ei::Button_radio::Button_radio(ei::Widget* parent, RB_Groupe* group, bool checked) : ei::Widget("Button_radio", parent)
{
    if(ei::Application::VERBOSE)
        std::cout<<"=====> making a Button_radio "<<std::endl;
    requested_size = ei::Size(20, 20);
    bckground_color.red = bckground_color.green = bckground_color.blue = 0;
    bckground_color.alpha = 255;
    border_color_top.red = border_color_top.blue = border_color_top.green = 0;
    border_color_top.alpha = 255;
    if(group != nullptr){
        this->group = group;
        group->add(this);
    }
    this->checked = checked;
    tag_id.push_back("ei_button_radio");
    if(parent != nullptr){
        parent->set_children(this);
        tooltip = new Tooltip(this);
    }
}


void ei::Button_radio::configure(ei::Size *requested_size, color_t *border_color, color_t *bckground_color){
    ei::Rect screen_location_copy(get_top_left(), screen_location.size);
    if(border_color != nullptr)
        this->border_color_top = *border_color;
    if(bckground_color != nullptr)
        this->bckground_color = *bckground_color;
    if(requested_size != nullptr){
        this->requested_size = *requested_size;
        set_screen_abs_location(nullptr, nullptr, &requested_size->width(), & requested_size->height());
    }

    if(geom_manager != nullptr){
        geom_manager->run(this);
        ei::Application::getInstance()->invalidate_rect(ei::Application::getInstance()->fusion(ei::Rect(get_top_left(), screen_location.size), screen_location_copy));
    }
}

ei::Button_radio::~Button_radio(){

}

void ei::Button_radio::draw (surface_t surface, surface_t pick_surface, Rect* clipper){
    assert(surface != nullptr && pick_surface != nullptr);
    if(ei::Application::VERBOSE)
        std::cout<<"=====> drawing a Button_radio "<<std::endl;
    if(ei::Application::DEBUG && clipper != nullptr){
        bckground_color = ei::Application::DEBUG_COLOR_CHECK;
    }
    // check if the widget exceeds his parent
    ei::Rect *new_clipper = clipper;
    bool exceeds = overflow(&new_clipper);
    if(out)
        return;
    if(clipper != nullptr && ei::Application::DEBUG){
        bckground_color = ei::Application::DEBUG_COLOR_BUTTON;
    }
    /* get size and top left */
    Size size = screen_location.size;
    Point top_left = get_top_left();
    radius = screen_location.size.width()/2;
    top_left.x() += radius;
    top_left.y() += radius;
    // drawing the button
    al_set_target_bitmap(static_cast<ALLEGRO_BITMAP *>(surface));
    if(new_clipper != nullptr){
        al_set_clipping_rectangle(new_clipper->top_left.x(), new_clipper->top_left.y(), static_cast<int>(new_clipper->size.width()), static_cast<int>(new_clipper->size.height()));
    }
    al_draw_circle(top_left.x(), top_left.y(), radius, al_map_rgba(border_color_top.red, border_color_top.green, border_color_top.blue, border_color_top.alpha), 0);
    // if the button is checked, draw a rounded circle in the button
    if(checked){
        al_draw_filled_circle(top_left.x(), top_left.y(), radius-4, al_map_rgba(bckground_color.red, bckground_color.green, bckground_color.blue, 0xff));
    }
    // actualize the clipping in all the root widget
    al_set_clipping_rectangle(0, 0, static_cast<int>(ei::Application::getInstance()->root_widget()->get_screen_location().size.width()),
                              static_cast<int>(ei::Application::getInstance()->root_widget()->get_screen_location().size.height()));

    Widget::draw(surface, pick_surface, new_clipper);

    if(exceeds){
        delete new_clipper;
    }
}

void ei::Button_radio::set_content_rec(int *x, int *y, float* width, float* height){}

bool ei::Button_radio::is_checked() const{
    return checked;
}

void ei::Button_radio::set_checked(bool val){
    checked = val;
}

ei::RB_Groupe &ei::Button_radio::getGroup(){
    return *group;
}

ei::RB_Groupe::RB_Groupe(){}

ei::RB_Groupe::~RB_Groupe(){}

void ei::RB_Groupe::add(Button_radio* button){
    group_button.push_back(button);
}

std::list<ei::Button_radio*>& ei::RB_Groupe::get_list() {
    return group_button;
}

std::string ei::Button_radio::get_type() const{
    return "Button_radio";
}
