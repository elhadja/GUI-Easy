/**
  * \file widget_test.h
  * \brief contains class \ref ei::Widget_test statement
  * \author Bah elhadj amadou
  */


#ifndef WIDGET_TEST_H
#define WIDGET_TEST_H

#include "../include/ei_widget.h"
#include "../include/ei_application.h"

namespace ei {

/**
 * @brief The Widget_test class tests ei::Widget's methods \ref (ei_widget.h).
 *
 * Each methode has a test function : function_name_test and return
 * true if success else false
 */

class Widget_test : public Frame{
public:
    Widget_test();
    ~Widget_test();
    bool get_top_left_test();
    bool pick_test();
    bool swap_borer_color_test();
    bool use_anhor_test();
    bool configure_frame_test();
    bool configure_button_test();
    bool configure_topLevel_test();
    bool overflow_test();
    bool set_screen_abs_location_test();
    bool set_screen_rel_location_test();
    bool set_screen_location_test();
    bool get_parent_test();
    bool set_children_test();
    bool get_border_width_test();
    bool add_tag_test();
    bool remove_tag_test();
    bool get_requested_size_test();
    bool get_content_rect_test();
    bool get_anchor_test();
    bool get_type_test();
    bool Frame_test();
    bool Button_test();
private:
    ei::Size app_size;
    ei::Application* app;

};

}

#endif // WIDGET_TEST_H
