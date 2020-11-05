/**
  * \file event_manager_test.cpp
  * \brief contains class \ref Event_manager_test definition
  * \author Bah elhadj amadou
  */


#include "event_manager_test.h"

using namespace ei;

bool_t ei::Event_manager_test::test_callback(Widget* widget, Event* event, void* user_param)
{
    int* param = static_cast<int*>(user_param);
    *param += 1;
    return EI_TRUE;
}

ei::Event_manager_test::Event_manager_test(){}

ei::Event_manager_test::~Event_manager_test(){}

bool ei::Event_manager_test::bind_test(){
    bool is_correct(true);
    Event event;
    event.type = ei_ev_mouse_move;
    int user_param = 0;
    Frame* frame = new Frame(nullptr);
    //test1: widget <-> event
    ei::EventManager::getInstance().bind(ei_ev_mouse_move, frame, "", test_callback, &user_param);
    ei::EventManager::getInstance().check_event_callback(&event, frame);
    is_correct = is_correct && (user_param == 1);
    user_param = 0;

    //test2 event <-> tag (name)
    ei::EventManager::getInstance().bind(ei_ev_mouse_move, nullptr, "Frame", test_callback, &user_param);
    ei::EventManager::getInstance().check_event_callback(&event, frame);
    is_correct = is_correct && (user_param == 2);
    user_param = 0;

    //test3 tag (all) <-> event
    ei::EventManager::getInstance().bind(ei_ev_mouse_move, nullptr, "all", test_callback, &user_param);
    ei::EventManager::getInstance().check_event_callback(&event, frame);
    is_correct = is_correct && (user_param == 3);
    user_param = 0;


    ei::EventManager::getInstance().unbind(ei_ev_mouse_move, frame, "", test_callback, &user_param);
    ei::EventManager::getInstance().unbind(ei_ev_mouse_move, nullptr, "Frame", test_callback, &user_param);
    ei::EventManager::getInstance().unbind(ei_ev_mouse_move, nullptr, "all", test_callback, &user_param);

    delete frame;

    return is_correct;
}

bool ei::Event_manager_test::unbind_test(){
    bool is_correct(true);
    Event event;
    event.type = ei_ev_mouse_move;
    int user_param = 0;
    Frame* frame = new Frame(nullptr);

    //test1:
    ei::EventManager::getInstance().bind(ei_ev_mouse_move, frame, "", test_callback, &user_param);
    ei::EventManager::getInstance().unbind(ei_ev_mouse_move, frame, "", test_callback, &user_param);
    ei::EventManager::getInstance().check_event_callback(&event, frame);
    is_correct = is_correct && (user_param == 0);

    //test2:
    ei::EventManager::getInstance().bind(ei_ev_mouse_move, nullptr, "tag", test_callback, &user_param);
    ei::EventManager::getInstance().unbind(ei_ev_mouse_move, nullptr, "tag", test_callback, &user_param);
    ei::EventManager::getInstance().check_event_callback(&event, frame);
    is_correct = is_correct && (user_param == 0);

    return is_correct;
}

bool ei::Event_manager_test::check_event_callback_test(){
    bool is_correct(true);
    Event event;
    event.type = ei_ev_mouse_move;
    int user_param = 0;
    Frame* frame = new Frame(nullptr);

    ei::EventManager::getInstance().bind(ei_ev_mouse_move, frame, "", test_callback, &user_param);
    ei::EventManager::getInstance().check_event_callback(&event, frame);
    is_correct = is_correct && (user_param == 1);
    ei::EventManager::getInstance().unbind(ei_ev_mouse_move, frame, "", test_callback, &user_param);
    ei::EventManager::getInstance().check_event_callback(&event, frame);
    is_correct = is_correct && (user_param == 1);

    return is_correct;
}
