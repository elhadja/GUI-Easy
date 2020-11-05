/**
  *\file ei_geometry_manager.cpp
  * \brief contains definitions of GeometryManager and Placer \ref ei_geometrymanager.h
  *\author Bah elhadj amadou and Remi
  */

#include <cassert>
#include <iostream>

#include "ei_geometrymanager.h"
#include "ei_application.h"

ei::GeometryManager::GeometryManager(){}

ei::GeometryManager::~GeometryManager(){}

void ei::Placer::configure (ei::Widget*    widget,
                            ei::anchor_t*  anchor,
                            int*       x,
                            int*       y,
                            float*     width,
                            float*     height,
                            float*     rel_x,
                            float*     rel_y,
                            float*     rel_width,
                            float*     rel_height)
{
    assert(widget);

    ei::Point topleft_copy(widget->get_top_left());
    ei::Size size_copy(widget->get_screen_location().size);
    widget->set_geom_manager(this);

    if(anchor != nullptr){
        widget->set_anchor(*anchor);
    }else{
        if(widget->get_anchor() == ei_anc_none){
            widget->set_anchor(ei_anc_northwest);
        }
    }

    /* absolute x and y */
    int x_copy(widget->get_screen_abs_location().top_left.x()), y_copy(widget->get_screen_abs_location().top_left.y());
    if(x!=nullptr)
        x_copy = *x;
    if(y!=nullptr)
        y_copy = *y;
    widget->set_screen_abs_location(&x_copy, &y_copy, nullptr, nullptr);

    /* width and height */
    float width_copy(widget->get_requested_size().width());
    float height_copy(widget->get_requested_size().height());
    if(width != nullptr)
        width_copy = *width;
    if(height != nullptr)
        height_copy = *height;
    widget->set_screen_abs_location(nullptr, nullptr, &width_copy, &height_copy);

    /*relative x and y*/
    float rel_x_copy(widget->get_screen_rel_location().top_left.x());
    float rel_y_copy(widget->get_screen_rel_location().top_left.y());
    if(rel_x != nullptr)
        rel_x_copy = *rel_x;
    if(rel_y != nullptr)
        rel_y_copy = *rel_y;
    widget->set_screen_rel_location(&rel_x_copy, &rel_y_copy, nullptr, nullptr);

    /* relative width and height */
    float rel_width_copy(widget->get_screen_rel_location().size.width());
    float rel_height_copy(widget->get_screen_rel_location().size.height());
    if(rel_width != nullptr)
        rel_width_copy = * rel_width;
    if(rel_height != nullptr)
        rel_height_copy = *rel_height;
    widget->set_screen_rel_location(nullptr, nullptr, &rel_width_copy, &rel_height_copy);

    /* managing geometry for this and widget child */
    run(widget);
    ei::Rect clipper = ei::Application::getInstance()->fusion(ei::Rect(widget->get_top_left(), widget->get_screen_location().size), ei::Rect(topleft_copy, size_copy));
    clipper.top_left -= ei::Point(1, 1);
    clipper.size += ei::Point(2, 2);
    ei::Application::getInstance()->invalidate_rect(clipper);

}

void ei::Placer::actualize_pos(ei::Widget* widget){
    ei::Point pos = widget->getParent()->get_content_rect().top_left;
    ei::Point_f rel_pos=widget->get_screen_rel_location().top_left;
    int x(pos.x()), y(pos.y());
    float rel_x(rel_pos.x()), rel_y(rel_pos.y());
    x += (rel_x * widget->getParent()->get_content_rect().size.width()) + widget->get_screen_abs_location().top_left.x();
    y += (rel_y * widget->getParent()->get_content_rect().size.height()) + widget->get_screen_abs_location().top_left.y();
    widget->set_screen_location(&x, &y, nullptr, nullptr);
    ei::Point point = widget->get_top_left();
    widget->set_content_rec(&point.x(), &point.y(), nullptr, nullptr);
}


void ei::Placer::actualize_size(ei::Widget* widget){
    ei::Size size = widget->get_screen_abs_location().size, rel_size=widget->get_screen_rel_location().size;
    ei::Point pos = widget->get_screen_abs_location().top_left;
    ei::Point_f rel_pos = widget->get_screen_rel_location().top_left;
    float width(0), height(0);
    if(rel_size.width() > 0){
        width = (rel_size.width() * widget->getParent()->get_content_rect().size.width());
    }else{
        width = widget->get_screen_abs_location().size.width();
    }
    if(rel_size.height() > 0){
        height = (rel_size.height() * widget->getParent()->get_content_rect().size.height());
    }else{
        height = widget->get_screen_abs_location().size.height();
    }
    widget->set_screen_location(nullptr, nullptr, &width, &height);
    widget->set_content_rec(nullptr, nullptr, &width, &height);
}

void ei::Placer::run (ei::Widget* widget)
{
    assert(widget != nullptr);
    if(widget->getParent() == nullptr)
        return;
    actualize_size(widget);
    actualize_pos(widget);
    std::list<Widget*>::iterator it;
    for(it=widget->get_children().begin(); it!=widget->get_children().end(); it++){
        run(*it);
    }
}

void ei::Placer::release (ei::Widget* widget){
    assert(widget);
    widget->set_geom_manager(nullptr);
}
