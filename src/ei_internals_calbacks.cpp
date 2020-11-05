/**
  *\file ei_internals_calbacks.cpp
  *\brief contains internals calbacks definition
  * \author Bah elhadj amadou, Remi
  */

#include <iostream>

#include "ei_internals_calbacks.h"
#include "ei_application.h"
#include "ei_button_radio.h"
#include "ei_check_box.h"
#include "ei_entry.h"
#include "hw_interface.h"
#include "ei_eventmanager.h"
#include "ei_geometrymanager.h"
#include "ei_types.h"



ei::bool_t button_pressed (ei::Widget* widget, ei::Event* event, void* user_param)
{
    if(ei::Application::VERBOSE)
        std::cout<<"=====> bouton pressed or released: "<<widget->get_name()<<std::endl;

    widget->swap_borer_color();
    ei::Rect rect;
    rect = ei::Rect(widget->get_top_left(), widget->get_screen_location().size);
    static_cast<ei::Application*>(user_param)->invalidate_rect(rect);
    return ei::EI_TRUE;
}

ei::bool_t move_mouse_resize(ei::Widget* widget, ei::Event* event, void* user_param)
{
    if(ei::Application::VERBOSE){
        std::cout<<"=====> resizing a topLevel"<<std::endl;
    }

    ei::Widget* w = static_cast<ei::Widget*>(user_param);
    float width(w->getParent()->get_screen_location().size.width()), height(w->getParent()->get_screen_location().size.height());
    ei::Point top_left = w->getParent()->get_top_left();
    ei::MouseEvent* e = static_cast<ei::MouseEvent*>(event);
    ei::Size size_clipping(width+1, height);

    // calculate the new size
    switch (static_cast<ei::Toplevel*>(w->getParent())->get_resizable()) {
    case ei::ei_axis_x:
        width = e->where.x() - w->getParent()->get_top_left().x();
        break;
    case ei::ei_axis_y:
        height = e->where.y() - w->getParent()->get_top_left().y();
        break;
    case ei::ei_axis_both:
        height = e->where.y() - w->getParent()->get_top_left().y();
        width = e->where.x() - w->getParent()->get_top_left().x();
        break;
    default:
        return ei::EI_TRUE;
    }

    // if the widget has already the minimum size, the dimension is restaured
    if(static_cast<ei::Toplevel*>(w->getParent())->get_minimum_size().width() > width)
        width = w->getParent()->get_screen_location().size.width();
    if(static_cast<ei::Toplevel*>(w->getParent())->get_minimum_size().height() > height)
        height = w->getParent()->get_screen_location().size.height();

    // actualize all children's size
    w->getParent()->set_screen_abs_location(nullptr, nullptr, &width, &height);
    w->getParent()->get_geom_manager()->run(w->getParent());

    // compute clipper
    if(width > size_clipping.width()){
        size_clipping.width() = w->getParent()->get_screen_location().size.width();
    }
    if(height > size_clipping.height()){
        size_clipping.height() = w->getParent()->get_screen_location().size.height();
    }

    ei::Application::getInstance()->invalidate_rect(ei::Rect(top_left, size_clipping));
    return ei::EI_TRUE;
}

ei::bool_t stop_resize(ei::Widget* widget, ei::Event* event, void* user_param)
{
    if(ei::Application::VERBOSE){
        std::cout<<"=====> stop resizing the topLevel"<<std::endl;
    }

    ei::EventManager::getInstance().unbind(ei::ei_ev_mouse_move, NULL, "all", move_mouse_resize, static_cast<ei::Widget*>(user_param));
    ei::EventManager::getInstance().unbind(ei::ei_ev_mouse_buttonup, NULL, "all", stop_resize, static_cast<ei::Widget*>(user_param));

    return ei::EI_FALSE;
}

ei::bool_t move_widget_bis(ei::Widget* widget, ei::Event* event, void* user_param)
{
    if(ei::Application::VERBOSE)
        std::cout<<"=====> setting window position"<<std::endl;

    infos_t* info = static_cast<infos_t*>(user_param);
    ei::MouseEvent* mouse = static_cast<ei::MouseEvent*>(event);
    ei::Point topleft_copy(info->widget->get_top_left());
    ei::Rect screen_location_copy(info->widget->get_screen_location().top_left, info->widget->get_screen_location().size);
    ei::Rect screen_abs_location_copy(info->widget->get_screen_abs_location().top_left, info->widget->get_screen_abs_location().size);
    ei::Rect clipper;

    // get the position where was the mouse at the last move
    int last_click_x = info->widget->get_screen_abs_location().top_left.x() + (mouse->where.x() - info->x);
    int last_click_y = info->widget->get_screen_abs_location().top_left.y() + (mouse->where.y() - info->y);

    info->widget->set_screen_abs_location(&last_click_x, &last_click_y, nullptr, nullptr);

    info->widget->get_geom_manager()->run(info->widget);

    // if the widget exceeds his parent, this moved is ignored
    if(info->widget->overflow(nullptr)){
        info->widget->set_screen_abs_location(&screen_abs_location_copy.top_left.x(), &screen_abs_location_copy.top_left.y(), nullptr, nullptr);
        info->widget->get_geom_manager()->run(info->widget);
        return ei::EI_FALSE;
    }
    // compute the clipper
    clipper = ei::Application::getInstance()->fusion(ei::Rect(topleft_copy, screen_location_copy.size), ei::Rect(info->widget->get_top_left(), info->widget->get_screen_location().size + ei::Size(5, 0)));

    // the size of the clipper is increased by security
    clipper.top_left = clipper.top_left - ei::Point(2, 2);
    clipper.size = clipper.size + ei::Size(4, 4);

    ei::Application::getInstance()->invalidate_rect(clipper);

    // we keep the position of the mouse witch will be used for the next move
    info->x += mouse->where.x() - info->x;
    info->y += mouse->where.y() - info->y;
    return ei::EI_TRUE;
}

ei::bool_t stop_move_widget(ei::Widget* widget, ei::Event* event, void* user_param)
{
    if(ei::Application::VERBOSE){
        std::cout<<"=====> disable move topLevel"<<std::endl;
    }

    ei::EventManager::getInstance().unbind(ei::ei_ev_mouse_move, NULL, "all", move_widget_bis, static_cast<infos_t*>(user_param));
    ei::EventManager::getInstance().unbind(ei::ei_ev_mouse_buttonup, NULL, "all", stop_move_widget, static_cast<infos_t*>(user_param));
    ei::EventManager::getInstance(). bind(ei::ei_ev_mouse_move, nullptr, "ei_tooltip", show_tool_tip, ei::Application::getInstance());
    return ei::EI_TRUE;
}

ei::bool_t move_widget(ei::Widget* widget, ei::Event* event, void* user_param)
{
    if(ei::Application::VERBOSE)
        std::cout<<"=====> allowing to move widget"<<std::endl;

    //if theye is actived tooltip, we desable it before allowing to move the widget
    ei::info_tooltip_t info_tool_tip = ei::Application::get_info_tooltip();
    if(info_tool_tip.tooltip != nullptr){
        ei::MouseEvent event;
        event.where = info_tool_tip.point;
        hide_tool_tip(ei::Application::getInstance()->root_widget(), &event, info_tool_tip.tooltip);
    }
    ei::EventManager::getInstance().unbind(ei::ei_ev_mouse_move, nullptr, "ei_tooltip", show_tool_tip, ei::Application::getInstance());

    // keep infos about the click position
    infos_t* info = new infos_t;
    ei::MouseEvent* e = static_cast<ei::MouseEvent*>(event);
    info->widget = widget;
    info->x = static_cast<ei::MouseEvent*>(event)->where.x();
    info->y = static_cast<ei::MouseEvent*>(event)->where.y();
    ei::Point topLeft;
    topLeft = widget->get_top_left();
    // the toplevel can't be moved if the click is not the in bar menu
    if((widget->get_type() == "Toplevel") && (topLeft.x() > e->where.x() || (topLeft.y() + 42)< e->where.y()))
        return ei::EI_FALSE;

    ei::EventManager::getInstance().bind(ei::ei_ev_mouse_move, nullptr, "all", move_widget_bis, info);
    ei::EventManager::getInstance().bind(ei::ei_ev_mouse_buttonup, nullptr, "all", stop_move_widget, info);

    return ei::EI_TRUE;
}

ei::bool_t set_window_size(ei::Widget* widget, ei::Event* event, void* user_param)
{
    if(ei::Application::VERBOSE)
        std::cout<<"=====> allowing to set size for TopLevel :"<<widget->get_name()<<std::endl;

    ei::EventManager::getInstance().bind(ei::ei_ev_mouse_move, nullptr, "all", move_mouse_resize, widget);
    ei::EventManager::getInstance().bind(ei::ei_ev_mouse_buttonup, nullptr, "all", stop_resize, widget);
    return ei::EI_FALSE;
}

ei::bool_t closeTopLevel(ei::Widget* widget, ei::Event* event, void* user_param)
{
    if(ei::Application::VERBOSE)
        std::cout<<"=====> closing TopLevel"<<std::endl;

    widget->getParent()->get_geom_manager()->release(widget->getParent());
    ei::Rect rect;
    rect.top_left = widget->getParent()->get_top_left();
    rect.size = ei::Size(widget->getParent()->get_screen_location().size.width() + 1, widget->getParent()->get_screen_location().size.height());
    static_cast<ei::Application*>(user_param)->invalidate_rect(rect);
    return ei::EI_FALSE;
}

ei::bool_t select_button_radio(ei::Widget* widget, ei::Event* event, void* user_param)
{
    if(ei::Application::VERBOSE)
        std::cout<<"=====> selecting button radio"<<std::endl;

    std::list<ei::Button_radio*>::iterator it;
    ei::Button_radio *br = static_cast<ei::Button_radio*>(widget);
    for(it=br->getGroup().get_list().begin(); it!=br->getGroup().get_list().end(); it++){
        // if it's the button radio where the user has clicked
        if((*it)->getPick_id() == br->getPick_id()){
            if(br->is_checked())
                br->set_checked(false);
            else {
                br->set_checked(true);
            }
        }
        else{   // else if the radio button is checked, we deselect it
            if((*it)->is_checked()){
                (*it)->set_checked(false);
                static_cast<ei::Application*>(user_param)->invalidate_rect(ei::Rect((*it)->get_top_left(), (*it)->get_screen_location().size + (*it)->get_screen_location().size));
            }
        }
    }
    static_cast<ei::Application*>(user_param)->invalidate_rect(ei::Rect(br->get_top_left(), br->get_screen_location().size + br->get_screen_location().size));
    return ei::EI_TRUE;
}

ei::bool_t select_check_box(ei::Widget* widget, ei::Event* event, void* user_param)
{
    if(ei::Application::VERBOSE)
        std::cout<<"=====> selecting button radio"<<std::endl;

    ei::Check_box *check = static_cast<ei::Check_box*>(widget);
    if(check->is_checked()){
        check->set_checked(false);
    }else{
        check->set_checked(true);
    }
    static_cast<ei::Application*>(user_param)->invalidate_rect(ei::Rect(check->get_top_left(), check->get_screen_location().size));
    return ei::EI_TRUE;
}

ei::bool_t select_entry(ei::Widget* widget, ei::Event* event, void* user_param){
    if(ei::Application::VERBOSE)
        std::cout<<"=====> selecting an entry"<<std::endl;

    ei::Entry *entry = static_cast<ei::Entry*>(widget);
    if(ei::Entry::get_has_entry() != nullptr && ei::Entry::get_has_entry()->getPick_id() != entry->getPick_id())
        static_cast<ei::Application*>(user_param)->invalidate_rect(ei::Rect(ei::Entry::get_has_entry()->get_top_left(), ei::Entry::get_has_entry()->get_screen_location().size));
    ei::Entry::set_has_focus(entry);
    static_cast<ei::Application*>(user_param)->invalidate_rect(ei::Rect(entry->get_top_left(), entry->get_screen_location().size));
    return ei::EI_TRUE;
}

ei::bool_t key_event_down(ei::Widget* widget, ei::Event* event, void* user_param){
    if(ei::Entry::get_has_entry() != nullptr){
        switch (static_cast<ei::KeyEvent*>(event)->key_sym) {
        case ALLEGRO_KEY_BACKSPACE:
            ei::Entry::get_has_entry()->delete_char();
            break;
        case ALLEGRO_KEY_SPACE:
            ei::Entry::get_has_entry()->add_char(' ');
            break;
        case ALLEGRO_KEY_LEFT:
            ei::Entry::get_has_entry()->set_cursor_position(-1);
            break;
        case ALLEGRO_KEY_RIGHT:
            ei::Entry::get_has_entry()->set_cursor_position(1);
            break;
        case ALLEGRO_KEY_A ... ALLEGRO_KEY_Z:
        case ALLEGRO_KEY_PAD_0 ... ALLEGRO_KEY_PAD_9:
        case ALLEGRO_KEY_0 ... ALLEGRO_KEY_9:
            const char *c = al_keycode_to_name(static_cast<ei::KeyEvent*>(event)->key_sym);
            ei::Entry::get_has_entry()->add_char(*c);
            break;
        }
    }

    if(ei::Entry::get_has_entry() != nullptr)
        static_cast<ei::Application*>(user_param)->invalidate_rect(ei::Rect(ei::Entry::get_has_entry()->get_top_left(), ei::Entry::get_has_entry()->get_screen_location().size));

    return ei::EI_TRUE;
}


ei::bool_t check_to_desable(ei::Widget* widget, ei::Event* event, void* user_param)
{
    if(ei::Entry::get_has_entry() != nullptr && ei::Entry::get_has_entry()->getPick_id() != widget->getPick_id())
    {
        static_cast<ei::Application*>(user_param)->invalidate_rect(ei::Rect(ei::Entry::get_has_entry()->get_top_left(), ei::Entry::get_has_entry()->get_screen_location().size));
        ei::Entry::set_has_focus(nullptr);
    }
    return ei::EI_TRUE;
}

ei::bool_t hide_tool_tip(ei::Widget* widget, ei::Event* event, void* user_param){
    ei::Widget* tooltip = static_cast<ei::Widget*>(user_param);
    if(widget->getPick_id() != tooltip->getParent()->getPick_id()){
        if(ei::Application::VERBOSE)
            std::cout<<"=====> hidding a tooltip for: "<<tooltip->getParent()->get_name()<<std::endl;

        if(tooltip->get_geom_manager() != nullptr)
            tooltip->get_geom_manager()->release(tooltip);

        ei::Application::set_info_tooltip(nullptr, 0, ei::Point()); // inform the Application tha there is no active tooltip

        ei::EventManager::getInstance().unbind(ei::ei_ev_mouse_move, nullptr, "all", hide_tool_tip, user_param);

        // compute the clipper
        float widht_clilpper = (tooltip->getParent()->get_screen_location().size.width() > tooltip->get_screen_location().size.width()) ? tooltip->getParent()->get_screen_location().size.width() : tooltip->get_screen_location().size.width();
        float height_clipper(tooltip->getParent()->get_screen_location().size.height() + tooltip->get_screen_location().size.height());

        ei::Application::getInstance()->invalidate_rect(ei::Rect(tooltip->get_top_left(), ei::Size(widht_clilpper, height_clipper)));
    }
    return ei::EI_TRUE;
}

ei::bool_t show_tool_tip(ei::Widget* widget, ei::Event* event, void* user_param){
    if(widget->get_tooltip()->get_geom_manager() == nullptr){
        if(ei::Application::VERBOSE)
            std::cout<<"=====> showing a tooltip for: "<<widget->get_name()<<std::endl;

        widget->get_tooltip()->set_screen_location(&widget->get_top_left().x(), &widget->get_top_left().y(), nullptr, nullptr);

        ei::Application::set_info_tooltip(widget->get_tooltip(), hw_now(), ei::Point(-1, -1));  // give to the Application some informations about the tooltip
        widget->get_tooltip()->show_tool_tipe();

        ei::EventManager::getInstance().bind(ei::ei_ev_mouse_move, nullptr, "all", hide_tool_tip, widget->get_tooltip());

        // compute the clipper
        float widht_clilpper = (widget->get_screen_location().size.width() > widget->get_tooltip()->get_screen_location().size.width()) ? widget->get_screen_location().size.width() : widget->get_tooltip()->get_screen_location().size.width();
        float height_clipper(widget->get_screen_location().size.height() + widget->get_tooltip()->get_screen_location().size.height());
        ei::Application::getInstance()->invalidate_rect(ei::Rect(widget->get_tooltip()->get_top_left(), ei::Size(widht_clilpper, height_clipper)));
    }
    return ei::EI_TRUE;
}
