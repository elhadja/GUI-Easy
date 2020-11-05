/**
  *\file ei_topLevel.cpp
  *\brief contains definitions of TopLevel class TopLevel\ref ei_widget.h
  *\author Bah elhad amadou
  */


#include "ei_widget.h"
#include "ei_geometrymanager.h"
#include "ei_eventmanager.h"
#include "ei_application.h"

#include <iostream>

#define DEFAULT_WIDTH 320
#define DEFAULT_HEIGHT 240


const int ei::Toplevel::title_bar_height = 50;
const int ei::Toplevel::default_width = 320;
const int ei::Toplevel::default_height = 240;

ei::Toplevel::Toplevel(Widget* parent): ei::Widget ("TopLevel",parent)
{
    if(ei::Application::VERBOSE)
        std::cout<<"=====> making a TopLevel"<<std::endl;
    min_size = Size(160, 120);
    border_width = 4;
    title = "Toplevel";
    is_closable = EI_TRUE;
    resizable = ei_axis_both;
    this->title_font = ei::Application::get_default_font();
    tag_id.push_back("ei_topLevel");

    //create and configure button close
    but_close = new Button(this);
    surface_t image = hw_image_load(DATA_DIR"cross.png");
    but_close->configure (nullptr, nullptr,nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, &image, nullptr, nullptr);
    btn_close_placer = new Placer();
    float but_x_rel=1.0, but_y_rel=0.0;
    int but_x(-25), but_y(-30);
    btn_close_placer->configure(but_close, nullptr, &but_x, &but_y, nullptr, nullptr, &but_x_rel, &but_y_rel, nullptr, nullptr);
    but_close->set_name("bouton_close");

    // create and configure button resize
    but_resize = new Button(this);
    int but_resize_border(0), corner_radius(0);
    but_resize->configure (nullptr, &bckground_color,&but_resize_border, &corner_radius, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    btn_resize_placer= new Placer();
    float but_x_rel2=1.0, but_y_rel2=1.0, but_height(15), but_width(15);
    int but_x2(0), but_y2(-0);
    ei::anchor_t but_resize_anchor = ei_anc_southeast;
    btn_resize_placer->configure(but_resize, &but_resize_anchor, &but_x2, &but_y2, &but_width, &but_height, &but_x_rel2, &but_y_rel2, nullptr, nullptr);
    but_resize->set_name("button_resize");

    if(parent != nullptr)
        parent->set_children(this);
}

ei::Toplevel::~Toplevel(){
    delete btn_close_placer;
    delete btn_resize_placer;
}

void ei::Toplevel::draw (surface_t surface, surface_t pick_surface, Rect* clipper){
    color_t center_color = {255, 255, 255, 255};
    if(ei::Application::VERBOSE){
        std::cout<<"=====> drawing a Toplevel: "<<name<<", tag_id: "<<tag_id.front()<<std::endl;
    }
    if(ei::Application::DEBUG && clipper != nullptr){
        center_color = ei::Application::DEBUG_COLOR_TOPLEVEL;
    }
    // check if the widget exceeds his parent
    ei::Rect *new_clipper = clipper;
    bool exceeds = overflow(&new_clipper);
    if(out)
        return;
    Point top_left = get_top_left();
    // draw topLevel
    ei_draw_filled_rounded_rect(surface, new_clipper, ei::Rect(top_left, screen_location.size), bckground_color);
    ei_draw_filled_rounded_rect(surface, new_clipper, *content_rect, center_color);
    // title
    draw_text(surface, &top_left, title, title_font, &default_text_color);

    // drawn all children
    Widget::draw(surface, pick_surface, new_clipper);
    if(exceeds)
        delete new_clipper;
}

void ei::Toplevel::configure (Size* requested_size,
                              color_t*        color,
                              int*            border_width,
                              const char**    title,
                              bool_t*         closable,
                              axis_set_t*     resizable,
                              Size*           min_size)
{
    if(border_width != nullptr)

        this->border_width = *border_width;

    ei::Rect screen_location_copy(get_top_left(), screen_location.size);
    if(requested_size != nullptr){
        *requested_size = Size(requested_size->width() + (this->border_width*2), requested_size->height() + ei::Toplevel::title_bar_height + this->border_width);
        this->requested_size = *requested_size;
        if(get_screen_location().size.width() == 0.f && get_screen_location().size.height() == 0.f) // if it's the first size configuration
        {
            set_screen_location(nullptr, nullptr, &requested_size->width(), &requested_size->height());
        }
        set_screen_abs_location(nullptr, nullptr, &requested_size->width(), &requested_size->height());
    }else{
        if(this->requested_size.width() == 0.f && this->requested_size.height() == 0.f){   // if the requested size wasn't configured
            this->requested_size = Size(ei::Toplevel::default_width + (this->border_width*2), ei::Toplevel::default_height + ei::Toplevel::title_bar_height);
            set_screen_abs_location(nullptr, nullptr, &this->requested_size.width(), &this->requested_size.height());
        }
    }

    if(color != nullptr)
        bckground_color = *color;
    if(title != nullptr)
        this->title = *title;
    if(closable != nullptr){
        is_closable = *closable;
        if(*closable == ei::EI_FALSE)
            this->but_close->get_geom_manager()->release(this->but_close);
    }
    if(resizable != nullptr)
        this->resizable = *resizable;
    if(min_size!=nullptr)
        *min_size = *min_size;
    if(geom_manager != nullptr){
        geom_manager->run(this);
    }
    if(geom_manager != nullptr){
        geom_manager->run(this);
        ei::Application::getInstance()->invalidate_rect(ei::Application::getInstance()->fusion(ei::Rect(get_top_left(), screen_location.size), screen_location_copy));
    }

}


void ei::Toplevel::set_content_rec(int *x, int *y, float* width, float* height){
    if(x!=nullptr && y!=nullptr)
        content_rect->top_left = Point(*x + border_width, *y + ei::Toplevel::title_bar_height);
    if(width!=nullptr && height!=nullptr)
        content_rect->size = Size(*width - (2*border_width), *height - ei::Toplevel::title_bar_height - border_width);
}


ei::axis_set_t ei::Toplevel::get_resizable(){
    return resizable;
}


const ei::Size& ei::Toplevel::get_minimum_size() const{
    return min_size;
}

std::string ei::Toplevel::get_type() const{
    return "Toplevel";
}
