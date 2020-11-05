cmake_minimum_required(VERSION 3.0)

set (CMAKE_CXX_FLAGS "-pthread -Wall -g")

# minimal target
add_executable(minimal minimal.cpp)
target_link_libraries(minimal ei eibase ${Allegro_LIBRARIES} m)

#add_executable(test_bah test_bah.cpp)
# add_executable(test_frame_img test_frame_img.cpp)
# add_executable(test_frame_text test_frame_text.cpp)
# add_executable(test_button_sample test_button_sample.cpp)
 add_executable(test_draw_recursivite test_draw_recursivite.cpp)
#target_link_libraries(test_bah ei eibase ${Allegro_LIBRARIES} m)
#target_link_libraries(test_frame_text ei eibase ${Allegro_LIBRARIES} m)
#target_link_libraries(test_frame_img ei eibase ${Allegro_LIBRARIES} m)
#target_link_libraries(test_button_sample ei eibase ${Allegro_LIBRARIES} m)
 target_link_libraries(test_draw_recursivite ei eibase ${Allegro_LIBRARIES} m)

# Targets disabled until the basic functionalities of the library are implemented


add_executable(frame frame.cpp)
target_link_libraries(frame ei eibase ${Allegro_LIBRARIES} m)

add_executable(button button.cpp)
target_link_libraries(button ei eibase ${Allegro_LIBRARIES} m)

add_executable(toplevel toplevel.cpp)
target_link_libraries(toplevel ei eibase ${Allegro_LIBRARIES} m)


add_executable(demo demo.cpp)
target_link_libraries(demo ei eibase ${Allegro_LIBRARIES} m)


# Unit tests
add_executable(unit_tests unit_tests.cpp
    ../test_units/application_test.cpp
    ../test_units/application_test.h
    ../test_units/widget_test.h
    ../test_units/widget_test.cpp
    ../test_units/event_manager_test.cpp
    ../test_units/event_manager_test.h
    ../test_units/placer_test.cpp
    ../test_units/placer_test.h
    ../test_units/toplevel_test.cpp
    ../test_units/toplevel_test.h
    ../test_units/entry_test.cpp
    ../test_units/entry_test.h
    ../test_units/internals_calback_test.cpp
    ../test_units/internals_calback_test.h)

target_link_libraries(unit_tests ei eibase ${Allegro_LIBRARIES} m)

enable_testing()
ms_add_catch_tests(unit_tests) 
