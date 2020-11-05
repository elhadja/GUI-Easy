/**
  * \file toplevel_test.h
  * \brief contains class \ref ei::Toplevel_test statements
  * \author Bah elhadj amadou
  */


#ifndef TOPLEVEL_TEST_H
#define TOPLEVEL_TEST_H

#include "../include/ei_widget.h"
#include "../include/ei_application.h"

namespace ei {

/**
 * @brief The Toplevel_test class tests ei::Toplevel's methods \ref (ei_widget.h).
 *
 * Each methode has a test function : function_name_test
 */
class Toplevel_test : public Toplevel{
public:
    Toplevel_test();
    ~Toplevel_test();
    /**
     * @brief get_resizable_test test get_resizable
     * @return  true if sucess else false
     */
    bool get_resizable_test();
    /**
     * @brief get_minimum_size_test test get_minimum_szie
     * @return  true if sucess else false
     */
    bool get_minimum_size_test();
    /**
     * @brief set_content_rect_test test set_content_rect
     * @return  true if sucess else false
     */
    bool set_content_rect_test();
    /**
     * @brief ToplevelTest test toplevel (The constructor)
     * @return  true if sucess else false
     */
    bool ToplevelTest();
private:
    ei::Size app_size;
    ei::Application* app;

};

}


#endif // TOPLEVEL_TEST_H
