/**
 * @file    ei_entry.cpp
 *
 * @brief   contains classes statements: \ref Entry, \ref Entry_pwd
 *  created by Bah elhadj amadou
 */


#include "ei_entry.h"

#include <iostream>

ei::Entry* ei::Entry::has_focus = nullptr;

ei::Entry::Entry(Widget* parent): ei::Frame(parent)
{
    cursor_position = 0;
    border_color_top.red = 0x0;
    border_color_top.green = 0x0;
    border_color_top.blue = 0x0;
    border_color_bottom.red = 0x0;
    border_color_bottom.green = 0x0;
    border_color_bottom.blue = 0x0;

    add_tag("ei_entry");
    pos_to_read = 0;

    if(parent != nullptr){
        tooltip = new Tooltip(this);
    }
}
ei::Entry::~Entry(){}

void ei::Entry::configure (Size*           requested_size,
                           const color_t*  color,
                           int*            border_width,
                           relief_t*       relief,
                           const char**          text,
                           font_t*         text_font,
                           color_t*        text_color,
                           anchor_t*       text_anchor){
    if(text != nullptr && *text != nullptr){
        text_bis.erase();
        text_bis.assign(*text);
        cursor_position = text_bis.size();
    }
    Frame::configure(requested_size, color, border_width, relief, text, text_font, text_color, text_anchor, nullptr, nullptr,nullptr);
}

void ei::Entry::draw (surface_t surface,
                      surface_t pick_surface,
                      Rect*     clipper){
    /*
     *check if the text size is more than the size of the entry.
     * if it is, we use 'pos_to_read' to display last text in the entry
     */
    if(ei::Entry::get_has_entry() != nullptr && ei::Entry::get_has_entry()->getPick_id() == getPick_id()){
        text_bis.insert(cursor_position, sizeof (char), '|');
        ei::Size text_size;
        hw_text_compute_size(text_bis.c_str(), text_font, text_size);
        if(text_size.width() >= (content_rect->size.width() - 8)){
            hw_text_compute_size(text_bis.substr(pos_to_read, text_bis.size()).c_str(), text_font, text_size);
            if(text_size.width() >= (content_rect->size.width() - 8)){
                pos_to_read += 1;
            }else{
                if(pos_to_read > 0)
                    pos_to_read -= 1;
            }
        }else{
            pos_to_read = 0;
        }
        const char* help = text_bis.c_str();
        text = help + pos_to_read;
    }
    Frame::draw(surface, pick_surface, clipper);
    text_bis.erase(cursor_position, 1);
}

ei::Entry* ei::Entry::get_has_entry(){
    return has_focus;
}

void ei::Entry::set_has_focus(ei::Entry* entry){
    has_focus = entry;
}

void ei::Entry::add_char(char c){
    text_bis.insert(cursor_position, sizeof(char), c);
    cursor_position++;
}

void ei::Entry::delete_char(){
    if(cursor_position > 0){
        std::string copy(text_bis);
        copy.erase(cursor_position - 1, 1);
        text_bis.assign(copy);
        cursor_position--;
    }
}

void ei::Entry::set_cursor_position(int val){
    cursor_position += static_cast<unsigned long>(val);
    if(cursor_position < 0.l)
        cursor_position = 0;
    if(cursor_position > text_bis.size())
        cursor_position = text_bis.size();
}


// -----------------------------

ei::Entry_pwd::Entry_pwd(Widget* parent) : ei::Entry(parent){}

ei::Entry_pwd::~Entry_pwd(){}

void ei::Entry_pwd::add_char(char c){
    text_bis.insert(cursor_position, sizeof(char), '*');
    passwrd.insert(pos_to_read, sizeof(char), c);
    cursor_position++;
}
void ei::Entry_pwd::delete_char(){
    if(cursor_position > 0){
        std::string copy(text_bis);
        copy.erase(cursor_position - 1, 1);
        text_bis.assign(copy);

        copy = passwrd;
        copy.erase(cursor_position - 1, 1);
        passwrd.assign(copy);

        cursor_position--;
    }
}
