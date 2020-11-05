/**
  * \file entry_test.cpp
  * \brief contains class \ref ei::Entry_test definition
  * \author Bah elhadj amadou
  */


#include "entry_test.h"

#include <iostream>

ei::Entry_test::Entry_test() : Entry (nullptr)
{
    app_size = Size(1000, 1000);
    app = new Application(&app_size);
}

ei::Entry_test::~Entry_test(){
    delete app;
}

bool ei::Entry_test::add_char_test(){
    this->text_bis.clear();
    add_char('c');
    add_char('+');
    add_char('+');
    return text_bis == "c++";
}

bool ei::Entry_test::delete_char_test(){
    size_t last_size(text_bis.size());
    add_char('c');
    add_char('+');
    delete_char();
    delete_char();
    return text_bis.size() == last_size;
}

bool ei::Entry_test::set_cursor_position_test(){
    unsigned long last_cursor_position(this->cursor_position);
    add_char('c');
    add_char('+');
    add_char('+');
    set_cursor_position(-3);
    return cursor_position == last_cursor_position;
}

bool ei::Entry_test::set_has_focus_test(){
    ei::Entry *entry = new Entry(nullptr);
    entry->set_name("I want the focus");
    ei::Entry::set_has_focus(entry);

    return ei::Entry::get_has_entry()->get_name() == "I want the focus";
}
