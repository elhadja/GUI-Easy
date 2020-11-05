/**
  * \file application_test.h
  * \brief contains class \ref ei::Application_test statements
  * \author Bah elhadj amadou
  */


#ifndef APPLICATION_TEST_H
#define APPLICATION_TEST_H

#endif // APPLICATION_TEST_H

#include "../include/ei_application.h"
namespace ei {

/**
 * @brief The Application_test class tests ei::Application's methods (\ref ei_application.h).
 * Each methode has a test function : function_name_test
 */
class Application_test : public ei::Application{
public:
    Application_test(ei::Size* size);
    ~Application_test();
    /**
     * @brief invalidate_rect_test test invalidate_rect()
     * @return true if succes else false
     */
    bool invalidate_rect_test();
    /**
     * @brief fusion_test test fusiion
     * @return true if succes else false
     */
    bool fusion_test();
    /**
     * @brief check_intersection_test test check_intersection
     * @return true if succes else false
     */
    bool check_intersection_test();
    /**
     * @brief quit_request_test test quit_request
     * @return true if succes else false
     */
    bool quit_request_test();
    /**
     * @brief get_info_tool_tip_test test get_info_tool_tip
     * @return true if succes else false
     */
    bool get_info_tool_tip_test();
    /**
     * @brief set_info_tool_tip_test test set_info_tool_tip
     * @return  true if succes else false
     */
    bool set_info_tool_tip_test();
    /**
     * @brief get_start_time_test test get_start_time
     * @return true if succes else false
     */
    bool get_start_time_test();
    /**
     * @brief root_widget_test test root_widget
     * @return true if succes else false
     */
    bool root_widget_test();
    /**
     * @brief max_test test max
     * @return true if succes else false
     */
    bool max_test();
    /**
     * @brief min_test test min
     * @return  true if succes else false
     */
    bool min_test();
    /**
     * @brief root_surface_test test root_surface
     * @return true if succes else false
     */
    bool root_surface_test();
    /**
     * @brief application_test test application (the constructor of ei::Application)
     * @return  true if succes else false
     */
    bool application_test();
private:
    ei::Size app_size;
    ei::Application* app;
    
};

}
