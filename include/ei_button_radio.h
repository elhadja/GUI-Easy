/**
 * @file    ei_button_radio.h
 *
 * @brief   contains classes statements: \ref button_radio, \ref RB_Group
 *  created by Bah elhadj amadou
 */


#ifndef EI_BUTTON_RADIO_H
#define EI_BUTTON_RADIO_H

#endif // EI_BUTTON_RADIO_H

#include "ei_widget.h"

namespace ei {

class RB_Groupe;

class Button_radio : public ei::Widget
{
public:
    /**
     * @brief Button_radio Construct a new instance of a Button_radio.
     *
     *      The widget is not displayed on screen until it is managed by a geometry manager.
     * @param parent the parent of the Frame
     */
    Button_radio(ei::Widget* parent, RB_Groupe* group=nullptr, bool checked = false);
    /**
     * @brief ~Button_radio \ref Widget::~Widget
     */
    ~Button_radio();
    /**
     * @brief \ref Widget::draw
     */
    virtual void draw (surface_t surface,
                       surface_t pick_surface,
                       Rect*     clipper);
    /**
     * @brief set_content_rec \ref Widget::set_content_rec
     */
    virtual void set_content_rec(int *x, int *y, float* width, float* height);
    /**
     * @brief configure configure the radio button
     * @param requested_size    the requested size (it can be modified by the geometry manager)
     * @param border_color      the border color of the radio button
     * @param bckground_color   the bckground color of the button radio
     *
     * all these parameters can be NULL
     */
    void configure(ei::Size *requested_size, color_t *border_color, color_t *bckground_color);
    /**
     * @brief is_checked check if the radio button is selected
     * @return true if the radio button is selected
     */
    bool is_checked() const;
    /**
     * @brief set_checked set the value of attribut \ref checked
     * @param val the new value
     */
    void set_checked(bool val);
    /**
     * @brief getGroup return the group of the radio button
     * @return
     */
    RB_Groupe &getGroup();
    /**
     * @brief set_content_rec \ref Widget::get_type
     */
    virtual std::string get_type() const;
protected:
   RB_Groupe* group;    ///< the group of the radio button
   float radius;        ///< the radius of the radio button
   bool checked;        ///< is true if the radio button is selected

};

/**
 * @brief The RB_Groupe class represents a radio button group
 */
class RB_Groupe{
public:
    RB_Groupe();
    ~RB_Groupe();
    /**
     * @brief add this function add a radio button to the group
     * @param button the button to add
     */
    void add(Button_radio* button);
    /**
     * @brief get_list get the group of the radio button
     * @return group of the radio button
     */
    std::list<Button_radio *> &get_list();
protected:
    std::list<Button_radio*> group_button;  ///< the list of the group
};

}
