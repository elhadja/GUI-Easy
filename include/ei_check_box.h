/**
 * @file    ei_check_box.h
 *
 * @brief   contains classe \ref Check_box statement
 *  created by Bah elhadj amadou
 */


#ifndef EI_CHECK_BOX_H
#define EI_CHECK_BOX_H

#include "ei_widget.h"

namespace ei {
class Check_box : public Widget
{
public:
    /**
     * @brief Check_box  Construct a new instance of a Check_box.
     *
     *      The widget is not displayed on screen until it is managed by a geometry manager.
     * @param parent the parent of the Frame
     */
    Check_box(Widget* parent);
    /**
     * @brief ~Check_box \ref Widget::~Widget
     */
    ~Check_box();
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
     * @brief is_checked check if the check_box is selected
     * @return true if the radio button is selected
     */
    bool is_checked() const;
    /**
     * @brief set_checked set the value of attribut \ref checked
     * @param val the new value
     */
    void set_checked(bool val);
    /**
     * @brief set_content_rec \ref Widget::get_type
     */
    virtual std::string get_type() const;
protected:
    bool checked;   ///< is true if the radio button is selected
};
}

#endif // EI_CHECK_BOX_H
