/**
  
  *\file ei_application.cpp
  *\brief contains the definitions of the Application class \ref ei_application.h
  *
  * \author Pierre Benard
  * Modified by Bah elhadj amadou and Remi
  */

#include "ei_application.h"
#include "hw_interface.h"
#include "ei_eventmanager.h"
#include "ei_geometrymanager.h"
#include "ei_types.h"
#include "ei_internals_calbacks.h"

#include <list>
#include <iterator>
#include <iostream>
#include <cassert>
#include <pthread.h>

ei::Application* ei::Application::instance = nullptr;
double ei::Application::start_time = 0;
const double ei::Application::refresh_time = 0.08;
const bool ei::Application::VERBOSE = false; // to see messages about what the application is doing
const bool ei::Application::DEBUG = false;  // just for debug (like print a message)
ei::font_t ei::Application::default_font = nullptr;
const ei::color_t ei::Application::DEBUG_COLOR_FRAME = {255, 0, 0, 255};
const ei::color_t ei::Application::DEBUG_COLOR_BUTTON = {0, 255, 0, 255};
const ei::color_t ei::Application::DEBUG_COLOR_TOPLEVEL= {0, 0, 255, 255};
const ei::color_t ei::Application::DEBUG_COLOR_CHECK = {200, 155, 0, 255};
ei::info_tooltip_t ei::Application::info_tool_type;

ei::Application::Application(Size* main_window_size)
{
    if(ei::Application::VERBOSE)
        std::cout<<"=====> initializing the application"<<std::endl;

    hw_init();
    assert(al_init_primitives_addon() != false);
    surface_t main_window = nullptr;
    main_window = hw_create_window(main_window_size, EI_FALSE);
    root_wid = new ei::Frame(nullptr);
    root_wid->set_name("frame_root");
    root_surf = main_window;
    offscreen = hw_surface_create(root_surf, main_window_size);
    picked_widget = new Frame(nullptr);

    EventManager::getInstance().bind(ei_ev_mouse_buttondown, nullptr, "ei_button", button_pressed, this);
    EventManager::getInstance().bind(ei_ev_mouse_buttonup, nullptr, "ei_button", button_pressed, this);
    EventManager::getInstance().bind(ei_ev_mouse_buttondown, nullptr, "bouton_close", closeTopLevel, this);
    EventManager::getInstance().bind(ei_ev_mouse_buttondown, nullptr, "button_resize", set_window_size, nullptr);
    EventManager::getInstance().bind(ei_ev_mouse_buttondown, nullptr, "ei_topLevel", move_widget, nullptr);
    EventManager::getInstance().bind(ei_ev_mouse_buttondown, nullptr, "ei_button_radio", select_button_radio, this);
    EventManager::getInstance().bind(ei_ev_mouse_buttondown, nullptr, "ei_check_box", select_check_box, this);
    EventManager::getInstance().bind(ei_ev_mouse_buttondown, nullptr, "ei_entry", select_entry, this);
    EventManager::getInstance().bind(ei_ev_mouse_buttondown, nullptr, "all", check_to_desable, this);
    EventManager::getInstance().bind(ei_ev_keydown, nullptr, "all", key_event_down, this);
    EventManager::getInstance().bind(ei_ev_mouse_move, nullptr, "ei_tooltip", show_tool_tip, this);
    EventManager::getInstance().bind(ei_ev_mouse_buttondown, nullptr, "ei_movable", move_widget, nullptr);


    default_font = hw_text_font_create(default_font_filename, font_default_size);

    instance = this;
    running = true;
}

ei::Application::~Application()
{
    if(ei::Application::VERBOSE)
        std::cout<<"=====> destruction de l'application: "<<std::endl;
    delete root_wid;
    hw_text_font_free(default_font);
    hw_surface_free(offscreen);
    hw_quit();
}

ei::Frame* ei::Application::root_widget(){
    return root_wid;
}

surface_t ei::Application::root_surface(){
    return root_surf;
}

void ei::Application::run()
{
    /* at the begining, draw all widgets */
    // drawing in offscreen using a thread
    info_thread_t info_thread = {offscreen, nullptr};
    pthread_t thread;
    pthread_create(&thread, nullptr, ei::fun_thread, &info_thread);
    // drawing in surface
    root_wid->draw(root_surf, offscreen, nullptr);
    hw_surface_update_rects(linked_rect_t());

    if(pthread_join(thread, nullptr)){
        perror("pthread_join\n");
        exit(EXIT_FAILURE);
    }

    start_time = hw_now();
    while (running == EI_TRUE) {
        if(info_tool_type.tooltip != nullptr && (hw_now() - info_tool_type.timer)>2){   // if tooltip's time is over, hide the tooltip
            ei::MouseEvent event;
            event.where = info_tool_type.point;
            hide_tool_tip(root_wid, &event, info_tool_type.tooltip);
        }

        std::list<Rect>::iterator it;
        if(((hw_now() - start_time) > ei::Application::refresh_time) && (invalidate_rect_list.size() > 0)){
            for(it=invalidate_rect_list.begin(); it!=invalidate_rect_list.end(); it++){
                // drawing in offscreen using a thread
                info_thread_t info_thread = {offscreen, &(*it)};
                pthread_t thread;
                pthread_create(&thread, nullptr, ei::fun_thread, &info_thread);
                // draw in surface
                root_wid->draw(root_surf, offscreen, &(*it));

                if(pthread_join(thread, nullptr)){
                    perror("pthread_join\n");
                    exit(EXIT_FAILURE);
                }
            }

            if(invalidate_rect_list.size()>0){
                hw_surface_update_rects(invalidate_rect_list);
                invalidate_rect_list.clear();
            }

            start_time = hw_now();
        }

        Event* event = hw_event_wait_next();
        switch (event->type) {
        case ei_ev_mouse_move:
        case ei_ev_keydown:
        case ei_ev_mouse_buttondown:
        case ei_ev_mouse_buttonup:
        case ei_ev_display:
            widget_pick(Point(static_cast<MouseEvent*>(event)->where.x(), static_cast<MouseEvent*>(event)->where.y()));
            EventManager::getInstance().check_event_callback(event, picked_widget);
            break;
        default:
            break;
        }

        delete event;
    }
}

void ei::Application::quit_request(){
    running = false;
}

ei::Rect ei::Application::fusion(const ei::Rect &rect1, const ei::Rect &rect2){
    int start_x = static_cast<int>(min(rect1.top_left.x(), rect2.top_left.x()));
    int end_x = static_cast<int>(max(rect1.top_left.x() + rect1.size.width(), rect2.top_left.x() + rect2.size.width()));
    int start_y = static_cast<int>(min(rect1.top_left.y(), rect2.top_left.y()));
    int end_y = static_cast<int>(max(rect1.top_left.y() + rect1.size.height(), rect2.top_left.y() + rect2.size.height()));

    return ei::Rect(ei::Point(start_x, start_y), ei::Size(end_x - start_x, end_y - start_y));
}

void ei::Application::invalidate_rect(const Rect &rect)
{
    bool intersection(false);
    if(invalidate_rect_list.size() > 0){
        std::list<ei::Rect>::iterator it = invalidate_rect_list.begin();
        ei::Rect new_rect(rect.top_left, rect.size);
        while(it!=invalidate_rect_list.end()){
            if(ei::Application::check_intersection(new_rect, *it)){
                invalidate_rect_list.push_front(fusion(new_rect, *it));
                new_rect.top_left = invalidate_rect_list.front().top_left;
                new_rect.size = invalidate_rect_list.front().size;
                it = invalidate_rect_list.erase(it);
                intersection = true;
            }else{
                it++;
            }
        }
        if(!intersection){
            invalidate_rect_list.push_back(rect);
        }

    }else{
        invalidate_rect_list.push_back(rect);
    }
}


ei::Widget* ei::Application::widget_pick (const Point& where){
    color_t color = hw_get_pixel(offscreen, where);
    uint32_t pick_id = static_cast<uint32_t>((color.red << 16) + (color.green << 8) + (color.blue << 0));
    root_widget()->pick(pick_id, &picked_widget);
    return picked_widget;
}

double ei::Application::get_start_time(){
    return Application::start_time;
}

void ei::Application::set_start_time(double new_time){
    ei::Application::start_time = new_time;
}


float ei::Application::max(float val1, float val2){
    return (val1 > val2) ? val1 : val2 ;
}

float ei::Application::min(float val1, float val2){
    return (val1 < val2) ? val1 : val2;
}

bool ei::Application::check_intersection(const ei::Rect& rect_widget, const ei::Rect& clipper) {
    float max_gauche = max(rect_widget.top_left.x(), clipper.top_left.x());
    float min_droit = min(rect_widget.top_left.x() + rect_widget.size.width(), clipper.top_left.x() + clipper.size.width());
    float max_bas = max(rect_widget.top_left.y(), clipper.top_left.y());
    float min_haut = min(rect_widget.top_left.y() + rect_widget.size.height(), clipper.top_left.y() + clipper.size.height());
    return (max_gauche<min_droit) && (max_bas < min_haut);
}

ei::font_t ei::Application::get_default_font(){
    return default_font;
}

void ei::Application::set_info_tooltip(Widget* widget,double timer, ei::Point point){
    info_tool_type.point = point;
    info_tool_type.timer = timer;
    info_tool_type.tooltip = widget;
}

ei::info_tooltip& ei::Application::get_info_tooltip(){
    return info_tool_type;
}

void* ei::fun_thread(void *arg){
    ei::info_thread_t *merde = static_cast<ei::info_thread_t*>(arg);
    ei::Application::getInstance()->root_widget()->draw_in_offscreen(merde->pick_surface, merde->clipper);
    pthread_exit(nullptr);
}
