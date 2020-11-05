/**
  
  *\file ei_frame.cpp
  *\brief contains definitions of class Frame \ref ei_widget.h
  * \author Bah elhad amadou and Remi
  */

#include "ei_widget.h"
#include "ei_geometrymanager.h"
#include "ei_application.h"

#include <assert.h>
#include <iostream>

#define DEFAULT_SIZE_WIDTH 100
#define DEFAULT_SIZE_HEIGHT 100

ei::Frame::Frame(Widget* parent) : Widget("Frame", parent){
    this->border_width = default_frame_border_width;
    this->relief = ei_relief_none;
    this->text_color = default_text_color;
    this->text_anchor = ei_anc_center;
    this->img_anchor = ei_anc_center;
    this->img = nullptr;
    this->text = nullptr;
    this->text_font = ei::Application::get_default_font();
    tag_id.push_back("ei_frame");
    if(parent != nullptr)
        parent->set_children(this);
}

ei::Frame::~Frame(){}

void ei::Frame::configure (Size* requested_size, const color_t*  color, int* border_width, relief_t* relief,const char **text, font_t* text_font,                                                     color_t* text_color, anchor_t* text_anchor, surface_t* img, Rect** img_rect, anchor_t* img_anchor)
{
    ei::Rect screen_location_copy(get_top_left(), screen_location.size);
    if(requested_size != nullptr){
        this->requested_size = *requested_size;
        if(get_screen_location().size.width() == 0.f && get_screen_location().size.height() == 0.f) // if it's the first size configuration
            set_screen_location(nullptr, nullptr, &requested_size->width(), &requested_size->height());
        set_screen_abs_location(nullptr, nullptr, &requested_size->width(), &requested_size->height());
        set_content_rec(nullptr, nullptr, &requested_size->width(), &requested_size->height());
    }else{
        if(this->requested_size.width() == 0.f && this->requested_size.height() == 0.f){   // if the requested size wasn't configured
            if(text != nullptr){    // put a size that is big enought to display the text
                Size size;
                if(text_font != nullptr)
                    hw_text_compute_size(*text, *text_font, size);
                else
                    hw_text_compute_size(*text, this->text_font, size);
                this->requested_size = Size(size.width(), size.height());
                set_screen_location(nullptr, nullptr, &this->requested_size.width(), &this->requested_size.height());
                set_screen_abs_location(nullptr, nullptr, &this->requested_size.width(), &this->requested_size.height());
            }else if(img != nullptr){   // put a size that is big enought to display the image
                Size size = hw_surface_get_size(*img);
                this->requested_size = Size(size.width(), size.height());
                set_screen_location(nullptr, nullptr, &this->requested_size.width(), &this->requested_size.height());
                set_screen_abs_location(nullptr, nullptr, &this->requested_size.width(), &this->requested_size.height());
            }
        }
    }

    if(color != nullptr){
        this->bckground_color = *color;
    }

    if(border_width != nullptr){
        this->border_width = (*border_width);
    }

    if(relief != nullptr){
        this->relief = (*relief);
    }

    if(text != nullptr && img != nullptr){
        std::cerr<<"error: you must use only text or image"<<std::endl;
        return;
    }

    if(text != nullptr){
        this->text = *text;
    }

    if(text_font != nullptr){
        this->text_font = *text_font;
    }

    if(text_color != nullptr){
        this->text_color = *text_color;
    }

    if(text_anchor != nullptr){
        this->text_anchor = *text_anchor;
    }

    if(img != nullptr){
        this->img = *img;
    }

    if(img_rect != nullptr){
        this->img_rect = *img_rect;
    }

    if(img_anchor != nullptr){
        this->img_anchor = *img_anchor;
    }

    if(geom_manager != nullptr){
        geom_manager->run(this);
        ei::Application::getInstance()->invalidate_rect(ei::Application::getInstance()->fusion(ei::Rect(get_top_left(), screen_location.size), screen_location_copy));
    }
}

void ei::Frame::draw (surface_t surface, surface_t pick_surface, Rect* clipper)
{
    if(ei::Application::VERBOSE){
        std::cout<<"=====> drawing a Frame: "<<name<<", tag_id: "<<tag_id.front()<<std::endl;
    }
    if(ei::Application::DEBUG && clipper != nullptr){
        bckground_color = ei::Application::DEBUG_COLOR_FRAME;
    }
    // check if the widget exceeds his parent
    ei::Rect *new_clipper = clipper;
    bool exceeds = overflow(&new_clipper);
    // draw the frame
    ei_draw_filled_rounded_rect(surface, new_clipper, ei::Rect(get_top_left(), screen_location.size), bckground_color);
    // draw border
    Point top_left = get_top_left();
    Size size = screen_location.size;
    linked_point_t point_list;
    if(border_width > 0){
        //top
        point_list = rounded_frame(ei::Rect(top_left, ei::Size(size.width(), size.height() - (size.height() -border_width))) ,0, BT_FULL);
        draw_polygon(surface, point_list, border_color_top, new_clipper);
        point_list.clear();
        //bottom
        point_list = rounded_frame(ei::Rect(ei::Point(top_left.x(), static_cast<int>(top_left.y() + (size.height() - border_width))),
                                            ei::Size(size.width(), size.height() - (size.height() -border_width))) ,0, BT_FULL);
        draw_polygon(surface, point_list, border_color_bottom, new_clipper);
        point_list.clear();
        //left
        point_list = rounded_frame(ei::Rect(top_left, ei::Size(size.width() - (size.width() - border_width), size.height())) ,0, BT_FULL);
        draw_polygon(surface, point_list, border_color_top, new_clipper);
        point_list.clear();
        //right
        point_list = rounded_frame(ei::Rect(ei::Point(static_cast<int>(top_left.x() + (size.width() - border_width)), top_left.y()),
                                            ei::Size(size.width() - (size.width() - border_width), size.height())) ,0, BT_FULL);
        draw_polygon(surface, point_list, border_color_bottom, new_clipper);
        point_list.clear();
    }

    if(text || img){
        ei::Size correct_size;
        surface_t generic_surface = (text != nullptr) ? hw_text_create_surface(text,text_font, &text_color) : img;
        anchor_t generic_anchor = (text != nullptr) ? text_anchor : img_anchor;
        int generic_sub = (text != nullptr) ? 3 : 0;
        if((hw_surface_get_size(generic_surface).width() < screen_location.size.width() && hw_surface_get_size(generic_surface).height() < screen_location.size.height() && !exceeds)){
            Point point = use_anchor(content_rect->top_left, content_rect->size,hw_surface_get_size(generic_surface), generic_anchor);
            if(text != nullptr)
                draw_text(surface, &point, text, text_font, &text_color);
            else
                ei_copy_surface(surface, img, &point, EI_FALSE);
        }else{
            if(exceeds){
                correct_size = ei::Size(new_clipper->size.width() - (2 * border_width) - generic_sub, new_clipper->size.height() - (2 *border_width) - generic_sub);
            }else{
                correct_size = ei::Size(content_rect->size.width() - generic_sub, content_rect->size.height() - generic_sub);
            }
            if(correct_size.width() < 1 || correct_size.height() < 1){
                return;
            }
            surface_t correct_surface = hw_surface_create(surface, &correct_size);   // size est la taille du bouton et surface est la surface root.
            fill(correct_surface, &bckground_color, EI_TRUE);
            Point p(0, -3);
            ei_copy_surface(correct_surface, generic_surface, &p, EI_FALSE);
            ei_copy_surface(surface, correct_surface, &content_rect->top_left, EI_TRUE);
            hw_surface_free(correct_surface);
        }
        if(text != nullptr)
            hw_surface_free(generic_surface);

    }

    Widget::draw(surface, pick_surface, new_clipper);

    if(exceeds){
        delete new_clipper;
    }
}


void ei::Frame::set_content_rec(int *x, int *y, float* width, float* height){
    if(x!=nullptr && y!=nullptr)
        content_rect->top_left = Point(*x + border_width, *y + border_width);
    if(width!=nullptr && height!=nullptr)
        content_rect->size = Size(*width - (2*border_width), *height - (2*border_width));
}

std::string ei::Frame::get_type() const{
    return "Frame";
}
