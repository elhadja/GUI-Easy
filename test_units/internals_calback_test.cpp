/**
  * \file internals_calback_test.cpp
  * \brief contains class \ref Internals_calback_test definition
  * \author Bah elhadj amadou
  * \date 04/19/2019
  */

#include "internals_calback_test.h"
#include "../include/ei_internals_calbacks.h"
#include "../include/ei_geometrymanager.h"
#include "../include/ei_eventmanager.h"
#include "../include/ei_entry.h"
#include "../include/ei_check_box.h"
#include "../include/ei_button_radio.h"

ei::Internals_calback_test::Internals_calback_test(ei::Size* size) : ei::Application(size)
{
    app_size = ei::Size(1000, 1000);
    app = ei::Application::getInstance();
}

ei::Internals_calback_test::~Internals_calback_test(){

}

bool ei::Internals_calback_test::close_toplevel_test(){
    ei::Toplevel *toplevel = new ei::Toplevel(nullptr);
    ei::Placer *p = new ei::Placer();
    p->configure(toplevel, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    Button *but_close = new Button(toplevel);
    closeTopLevel(but_close, nullptr, ei::Application::getInstance());
    return toplevel->get_geom_manager() == nullptr;
}

bool ei::Internals_calback_test::button_pressed_test(){
    bool is_correct(true);
    Widget *button = new Button(nullptr);
    color_t last_border_color_top = button->get_border_color_top();
    color_t last_border_color_bottom = button->get_border_color_bottom();
    unsigned long last_invalide_rect_size(invalidate_rect_list.size());
    button_pressed(button, nullptr, ei::Application::getInstance());
    //test1: the border color must be swept
    is_correct = is_correct && last_border_color_top.red == button->get_border_color_bottom().red && last_border_color_top.green == button->get_border_color_bottom().green &&
            last_border_color_top.blue == button->get_border_color_bottom().blue;
    is_correct = is_correct && last_border_color_bottom.red == button->get_border_color_top().red && last_border_color_bottom.green == button->get_border_color_top().green &&
            last_border_color_bottom.blue == button->get_border_color_top().blue;
    //test2: the invalidect_list's size must increase to 1
    is_correct = is_correct && (last_invalide_rect_size == (invalidate_rect_list.size() - 1));
    delete  button;
    return is_correct;
}

bool ei::Internals_calback_test::select_entry_test(){
    bool is_correct(true);
    ei::Entry *entry = new ei::Entry(nullptr);
    select_entry(entry, nullptr, ei::Application::getInstance());
    is_correct = ei::Entry::get_has_entry()->getPick_id() == entry->getPick_id();
    delete  entry;
    return  is_correct;
}

bool ei::Internals_calback_test::select_check_box_test(){
    bool is_correct(true);
    Check_box* checkbox = new Check_box(nullptr);
    checkbox->set_checked(false);
    select_check_box(checkbox, nullptr, ei::Application::getInstance());
    is_correct = checkbox->is_checked();
    delete  checkbox;
    return is_correct;
}

bool ei::Internals_calback_test::select_button_radio_test(){
    bool is_correct(true);
    RB_Groupe *group = new RB_Groupe();
    Button_radio* radio_button = new Button_radio(nullptr, group);
    radio_button->set_checked(false);
    select_button_radio(radio_button, nullptr, ei::Application::getInstance());
    is_correct = radio_button->is_checked();
    delete  radio_button;
    return is_correct;
}

bool ei::Internals_calback_test::check_to_desable_test(){
    /* when the user click in other wiget, the entry wich has the focus lost it */
    bool is_correct(true);
    Frame* frame = new Frame(nullptr);  // other widget
    ei::Entry *entry = new ei::Entry(nullptr);
    select_entry(entry, nullptr, ei::Application::getInstance());
    is_correct = ei::Entry::get_has_entry()->getPick_id() == entry->getPick_id();
    check_to_desable(frame, nullptr, ei::Application::getInstance());
    // test: the entry must lost the focus
    is_correct = ei::Entry::get_has_entry() == nullptr;
    delete  entry;
    return  is_correct;
}
