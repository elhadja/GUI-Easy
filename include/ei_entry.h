/**
 * @file    ei_entry.h
 *
 * @brief   contains classes statements: \ref Entry \ref Entry_pwd
 *  created by Bah elhadj amadou
 */


#ifndef EI_ENTRY_H
#define EI_ENTRY_H

#include "ei_widget.h"

namespace ei {
class Entry : public Frame
{
public:
    /**
     * @brief Entry Construct a new instance of a Entry.
     *
     *      The widget is not displayed on screen until it is managed by a geometry manager.
     * @param parent the parent of the Frame
     */
    Entry(Widget* parent);
    /**
     * @brief ~Entry \ref Widget::~Widget
     */
    ~Entry();
    /**
     * @brief \ref Frame::draw
     */
    virtual void draw (surface_t surface,
                       surface_t pick_surface,
                       Rect*     clipper);
    /**
     * @brief configure the entry
     * @param requested_size    the requested size
     * @param color the color of the entry
     * @param border_width  the border width
     * @param relief    the relielf
     * @param text      the text of the entry (the default text is "entry")
     * @param text_font the text font
     * @param text_color    the text_color
     * @param text_anchor   the text anchor
     */
    void configure (Size*           requested_size,
                    const color_t*  color,
                    int*            border_width,
                    relief_t*       relief,
                    const char **text,
                    font_t*         text_font,
                    color_t*        text_color,
                    anchor_t*       text_anchor);
    /**
     * @brief get_has_entry get the widget (entry) which has the focus
     * @return the entry or nullptr if all entries haven't the focus
     */
    static Entry* get_has_entry();
    /**
     * @brief set_has_focus set the value \ref has_focus
     * @param entry the entry which has the focus (it can be nullptr)
     */
    static void set_has_focus(ei::Entry* entry);
    /**
     * @brief add_char add a character in the entry and increase the position of the cursor
     * @param c the charactere to add
     */
    virtual void add_char(char c);
    /**
     * @brief delete_char delete a character in the entry and decrease the position of the cursor
     */
    virtual void delete_char();
    /**
     * @brief set_cursor_position set \ref cursor_position
     * @param val
     */
    void set_cursor_position(int val);
protected:
    static Entry* has_focus;        ///< the entry which has the focus
    unsigned long cursor_position;  ///< the position of the cursor in the entry (0 if there is not text)
    std::string text_bis;           ///< a string which contains the entered text in the entry
    unsigned long pos_to_read;      ///< the position where the text must be read to display it (when the text exceed the entry)

};

class Entry_pwd : public Entry
{
public:
    /**
     * @brief Entry_pwd Construct a new instance of a Entry_pwd.
     *
     *      The widget is not displayed on screen until it is managed by a geometry manager.
     * @param parent the parent of the Frame
     */
    Entry_pwd(Widget* parent);
    /**
     * @brief ~Entry_pwd \ref Entry::~Entry
     */
    ~Entry_pwd();
    /**
     * @brief add_char \ref Entry::add_char
     */
    virtual void add_char(char c);
    /**
     * @brief delete_char \ref Entry::delete_char
     */
    virtual void delete_char();
protected:
    std::string passwrd;    ///< contains "*" wich is equal than size of entered text (this string will be displayed in the entry)
};

}

#endif // EI_ENTRY_H
