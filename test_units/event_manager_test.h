/**
  * \file event_manager_test.h
  * \brief contains class \ref Event_manager_test statements
  * \author Bah elhadj amadou
  */


#include "../include/ei_eventmanager.h"

namespace ei {

/**
 * @brief The Event_manager_test class tests ei::Event_manager's methods (\ref ei_eventmanager.h)
 * Each methode has a test function : function_name_test
 */

class Event_manager_test{
public:
    Event_manager_test();
    ~Event_manager_test();
    /**
     * @brief bind_test test bind
     * @return return true if sucess
     */
    bool bind_test();
    /**
     * @brief unbind_test test unbind
     * @return return true if sucess
     */
    bool unbind_test();
    /**
     * @brief check_event_callback_test test check_event_calback
     * @return  return true if sucess
     */
    bool check_event_callback_test();
    /**
     * @brief test_callback is used by other methods in this class to make their tests
     * @param widget    any widget
     * @param event     any event
     * @param user_param    any parameter
     * @return
     */
    static bool_t test_callback(Widget* widget, Event* event, void* user_param);
};
}
