/**
  * \file entry_test.h
  * \brief contains class \ref ei::Entry_test statements
  * \author Bah elhadj amadou
  */


#ifndef ENTRY_TEST_H
#define ENTRY_TEST_H

#include "../include/ei_entry.h"
#include "../include/ei_application.h"

namespace ei {

/**
 * @brief The Entry_test class tests ei::Entry's methods (\ref ei_entry.h).
 * Each methode has a test function : function_name_test
 */
class Entry_test : public Entry{
public:
    /**
     * @brief Entry_test default constructor
     */
    Entry_test();
    ~Entry_test();
    /**
     * @brief add_char_test test add_char
     * @return true if succes else false
     */
    bool add_char_test();
    /**
     * @brief delete_char_test test delete_char
     * @return true if succes else false
     */
    bool delete_char_test();
    /**
     * @brief set_cursor_position_test test set_cursor_position
     * @return  true if succes else false
     */
    bool set_cursor_position_test();
    /**
     * @brief set_has_focus_test test set_has_focus
     * @return true if succes else false
     */
    bool set_has_focus_test();
private:
    ei::Size app_size;
    ei::Application* app;

};

}


#endif // ENTRY_TEST_H
