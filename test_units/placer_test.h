/**
  * \file placer_test.h
  * \brief contains class \ref ei::Placer_test statements
  * \author Bah elhadj amadou
  */


#ifndef PLACER_TEST_H
#define PLACER_TEST_H

#include "../include/ei_geometrymanager.h"
#include "../include/ei_application.h"

namespace ei {
/**
 * @brief The Placer_test class tests ei::Placer methods \ref (ei_geometrymanager.h).
 *
 * Each methode has a test function : function_name_test
 */

class Placer_test : public Placer{
public:
    Placer_test();
    ~Placer_test();
    /**
     * @brief actualize_size_test tes actualize_size
     * @return  return true if success else false
     */
    bool actualize_size_test();
    /**
     * @brief actualize_pos_test test actualize_pos
     * @return  return true if success else false
     */
    bool actualize_pos_test();
    /**
     * @brief configure_test test configure
     * @return  return true if success else false
     */
    bool configure_test();
    /**
     * @brief run_test test run
     * @return return true if success else false
     */
    bool run_test();
    /**
     * @brief release_test test release
     * @return  return true if success else false
     */
    bool release_test();
protected:
    ei::Size app_size;
    ei::Application* app;
};
}

#endif // PLACER_TEST_H
