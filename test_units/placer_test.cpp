/**
  * \file placer_test.cpp
  * \brief contains class \ref ei::Placer_test definition
  * \author Bah elhadj amadou
  */


#include "placer_test.h"

#include <iostream>

ei::Placer_test::Placer_test(){
    app_size = Size(1000, 1000);
    app = new Application(&app_size);
}

ei::Placer_test::~Placer_test(){
    //delete app;   /*provok a sigsegv*/
}

bool ei::Placer_test::actualize_size_test(){
    bool is_correct(true);
    Frame* parent = new Frame(nullptr);
    Frame* frame = new Frame(parent);
    float width(200), height(200);
    float rel_widht(0.5f), rel_height(0.5);
    std::cout<<"test actualize_size"<<std::endl;
    parent->set_content_rec(nullptr, nullptr, &width, &height);
    frame->set_screen_rel_location(nullptr, nullptr, &rel_widht, &rel_height);
    actualize_size(frame);
    ei::Size current_size = frame->get_screen_location().size;
    is_correct = is_correct && current_size.width() == 100.f && current_size.height() == 100.f;
    delete  parent;
    return is_correct;
}

bool ei::Placer_test::actualize_pos_test(){
    bool is_correct(true);
    Frame* parent = new Frame(nullptr);
    Frame* frame = new Frame(parent);
    int parent_x(100), parent_y(100);
    int abs_x(10), abs_y(10);
    float rel_x(0.5f), rel_y(0.5f);
    float parent_width(200), parent_height(200);
    parent->set_content_rec(&parent_x, &parent_y, &parent_width, &parent_height);
    frame->set_screen_abs_location(&abs_x, &abs_y, nullptr, nullptr);
    frame->set_screen_rel_location(&rel_x, &rel_y, nullptr, nullptr);
    actualize_pos(frame);
    ei::Point current_pos = frame->get_screen_location().top_left;
    is_correct = is_correct && current_pos.x() == 210 && current_pos.y() == 210;
    delete parent;
    return is_correct;
}

bool ei::Placer_test::configure_test(){
    bool is_correct(true);
    Frame* parent = new Frame(nullptr);
    Frame* frame = new Frame(parent);
    Point abs_pos(10, 10);
    ei::Size abs_size(100, 100);
    float rel_x(0.5f), rel_y(0.7f), rel_width(0.2f), rel_height(0.3f);
    anchor_t anchor(ei_anc_west);
    frame->configure(&abs_size, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,nullptr, nullptr);
    //test1
    configure(frame, &anchor, &abs_pos.x(), &abs_pos.y(), &abs_size.width(), &abs_size.height(), &rel_x, &rel_y, &rel_width, &rel_height);
    is_correct = is_correct && (frame->get_screen_abs_location().top_left == abs_pos) && (frame->get_screen_abs_location().size == abs_size);
    //test2
    configure(frame, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    is_correct = is_correct && (frame->get_screen_abs_location().top_left == abs_pos) && (frame->get_screen_abs_location().size == abs_size);
    delete parent;
    return is_correct;
}

bool ei::Placer_test::run_test(){
    bool is_correct(true);
    is_correct = is_correct && actualize_pos_test();
    is_correct = is_correct && actualize_size_test();
    return is_correct;
}

bool ei::Placer_test::release_test(){
    bool is_correct(true);
    Frame* frame = new Frame(nullptr);
    ei::Application::getInstance()->invalidate_rect_list.clear();
    this->configure(frame, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    frame->get_geom_manager()->release(frame);
    is_correct = is_correct && frame->get_geom_manager() == nullptr;
    return is_correct;
}
