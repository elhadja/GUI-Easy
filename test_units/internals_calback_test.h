/**
  * \file internals_calback_test.h
  * \brief contains class \ref Internals_calback_test statements
  * \author Bah elhadj amadou
  * \date 04/19/2019
  */

#ifndef INTERNALS_CALBACK_TEST_H
#define INTERNALS_CALBACK_TEST_H

#include "../include/ei_widget.h"
#include "../include/ei_application.h"

namespace ei {
/**
 * @brief The Internals_calback_test class tests all internals callback (\ref ei_internals_calbacks.h).
 * Each calbacks has a test function : calback_name_test
 */
class Internals_calback_test : public Application{
public:
    Internals_calback_test(ei::Size* size);
    ~Internals_calback_test();
    /**
     * @brief close_toplevel_test   test the internal calback close_top_level
     * @return true if sucess else false
     */
    bool close_toplevel_test();
    /**
     * @brief button_pressed_test   test the internal calback button_pressed
     * @return true if sucess else false
     */
    bool button_pressed_test();
    /**
     * @brief select_entry_test test the internal calback select_entry
     * @return true if sucess else false
     */
    bool select_entry_test();
    /**
     * @brief select_check_box_test test the internal calback select_check_box
     * @return  true if sucess else false
     */
    bool select_check_box_test();
    /**
     * @brief select_button_radio_test test the internal calback select_button_radio
     * @return  true if sucess else false
     */
    bool select_button_radio_test();
    /**
     * @brief check_to_desable_test test the internal calback check_to_desable
     * @return true if sucess else false
     */
    bool check_to_desable_test();
protected:
    ei::Size app_size;
    ei::Application* app;
};
}

#endif // INTERNALS_CALBACK_TEST_H
