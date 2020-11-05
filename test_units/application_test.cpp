/**
  * \file application_test.cpp
  * \brief contains class \ref ei::Application_test definition
  * \author Bah elhadj amadou
  */


#include "application_test.h"
#include "../include/ei_widget.h"

using namespace ei;

Application_test::Application_test(ei::Size* size) : Application(size)
{
    app_size = ei::Size(1000, 1000);
    app = ei::Application::getInstance();
}

Application_test::~Application_test(){}

bool ei::Application_test::invalidate_rect_test(){
    bool is_correct(true);
    ei::Rect rect1(ei::Point(50, 50), ei::Size(100, 100));
    ei::Rect rect2(ei::Point(60, 60), ei::Size(200, 200));
    ei::Rect rect3(ei::Point(300, 300), ei::Size(50, 50));
    // test1
    app->getInstance()->invalidate_rect(rect1);
    is_correct = is_correct && app->invalidate_rect_list.size() == 1;
    // test2
    app->getInstance()->invalidate_rect(rect2);
    is_correct = is_correct && app->invalidate_rect_list.size() == 1;
    //test3
    app->getInstance()->invalidate_rect(rect3);
    is_correct = is_correct && app->invalidate_rect_list.size() == 2;

    return is_correct;
}

bool ei::Application_test::check_intersection_test(){
    bool is_correct(true);
    ei::Rect rect1(ei::Point(50, 50), ei::Size(100, 100));
    ei::Rect rect2(ei::Point(60, 60), ei::Size(200, 200));
    is_correct = is_correct && ei::Application::check_intersection(rect1, rect2);
    rect2.top_left = ei::Point(300, 300);
    is_correct = is_correct && (!ei::Application::check_intersection(rect1, rect2));
    return is_correct;
}

bool Application_test::fusion_test(){
    bool is_correct = true;
    float width(0), height(0);

    ei::Rect rect1(ei::Point(5,5), ei::Size(70, 50));
    ei::Rect rect2(ei::Point(5,5), ei::Size(50, 50));

    // test1
    ei::Rect result = fusion(rect1, rect2);
    is_correct = is_correct && ((result.top_left == rect1.top_left) && (result.size == rect1.size));
    // test2
    rect1.top_left = ei::Point(5, 0);
    rect1.size = ei::Size(70, 55);
    result = fusion(rect1, rect2);
    is_correct = is_correct && ((result.top_left == rect1.top_left) && (result.size == rect1.size));
    assert(is_correct == true);

    // test3
    rect2.top_left = ei::Point(20, 20);
    rect2.size = ei::Size(100, 100);
    result = fusion(rect1, rect2);
    width = 115;
    height = 120;
    is_correct = is_correct && ((result.top_left == rect1.top_left) && (result.size.width() == width) && (result.size.height() == height));

    return is_correct;
}

bool ei::Application_test::quit_request_test(){
    running = true;
    quit_request();
    return running == false;
}

bool ei::Application_test::get_info_tool_tip_test(){
    set_info_tooltip(nullptr, 1000, ei::Point(0, 0));
    ei::info_tooltip info = get_info_tooltip();

    return info.point == ei::Point(0, 0) && info.timer == 1000. && info.tooltip == nullptr;
}

bool ei::Application_test::set_info_tool_tip_test(){
    set_info_tooltip(nullptr, 1000, ei::Point(0, 0));
    ei::info_tooltip info = get_info_tooltip();

    return info.point == ei::Point(0, 0) && info.timer == 1000. && info.tooltip == nullptr;
}

bool ei::Application_test::get_start_time_test(){
    ei::Application::set_start_time(1000);
    return ei::Application::get_start_time() == 1000.;
}

bool ei::Application_test::root_widget_test(){
    root_wid->set_name("root");
    return  root_widget()->get_name() == "root";
}

bool ei::Application_test::max_test(){
    return ei::Application::max(5, 6) == 6.f && ei::Application::max(5, 5) == 5.f;

}

bool ei::Application_test::min_test(){
    return ei::Application::max(1, 2) == 2.f && ei::Application::min(1, 1) == 1.f;
}

bool ei::Application_test::root_surface_test(){
    surface_t adresse_root_surface = root_surf;
    return root_surface() == adresse_root_surface;
}

bool ei::Application_test::application_test(){
    bool is_correct(true);
    is_correct = is_correct && root_surf != nullptr;
    is_correct = is_correct && root_widget() != nullptr;
    is_correct = is_correct && offscreen != nullptr;
    is_correct = is_correct && instance != nullptr;
    is_correct = is_correct && running == true;
    return true;
}
