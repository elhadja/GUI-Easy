#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "ei_main.h"
#include "ei_draw.h"
#include "hw_interface.h"
#include "ei_application.h"
#include "../test_units/application_test.h"
#include "../test_units/widget_test.h"
#include "../test_units/event_manager_test.h"
#include "../test_units/placer_test.h"
#include "../test_units/toplevel_test.h"
#include "../test_units/entry_test.h"
#include "../test_units/internals_calback_test.h"

using namespace ei;

TEST_CASE("create_window", "[unit]")
{
    hw_init();
    surface_t main_window = nullptr;
    Size main_window_size(640,480), query_size;

    main_window = hw_create_window(&main_window_size, EI_FALSE);
    REQUIRE( main_window != NULL );

    query_size = hw_surface_get_size(main_window);
    REQUIRE( main_window_size.width()  == query_size.width() );
    REQUIRE( main_window_size.height() == query_size.height() );
    hw_quit();
}

TEST_CASE("fill_window", "[unit]")
{
    hw_init();
    surface_t main_window = nullptr;
    Size main_window_size(640,480), query_size;
    color_t red = {0xff, 0x00, 0x00, 0xff}, query_color;
    Point origin;

    main_window = hw_create_window(&main_window_size, EI_FALSE);

    SECTION( "fill_red" ) {
        fill(main_window, &red, EI_FALSE);
        hw_surface_update_rects(linked_rect_t());

        query_color = hw_get_pixel(main_window, origin);
        //REQUIRE( query_color.red == red.red );
        REQUIRE( query_color.green == red.green );
        REQUIRE( query_color.blue == red.blue );
    }

    SECTION( "fill_default" ) {
        fill(main_window, nullptr, EI_FALSE);
        hw_surface_update_rects(linked_rect_t());

        query_color = hw_get_pixel(main_window, origin);
        REQUIRE( query_color.red == font_default_color.red );
        REQUIRE( query_color.green == font_default_color.green );
        REQUIRE( query_color.blue == font_default_color.blue ); 
    }
    hw_quit();
}

TEST_CASE("create_application", "[unit]")
{
    hw_init();
    Size screen_size = Size(600, 600);
    ei::Application* app = new ei::Application(&screen_size);
    hw_quit();
}

TEST_CASE("class_Application", "[unit]")
{
    ei::Size size(500, 500);
    Application_test *test = new Application_test(&size);
    REQUIRE(test->application_test());
    REQUIRE(test->fusion_test());
    REQUIRE(test->invalidate_rect_test());
    REQUIRE(test->check_intersection_test());
    REQUIRE(test->quit_request_test());
    REQUIRE(test->get_info_tool_tip_test());
    REQUIRE(test->set_info_tool_tip_test());
    REQUIRE(test->get_start_time_test());
    REQUIRE(test->root_widget_test());
    REQUIRE(test->max_test());
    REQUIRE(test->min_test());
    REQUIRE(test->root_surface_test());
    delete  test;
}

TEST_CASE("class_Widget", "[unit]")
{
    Widget_test *test = new Widget_test();
    REQUIRE(test->get_top_left_test());
    REQUIRE(test->pick_test());
    REQUIRE(test->swap_borer_color_test());
    REQUIRE(test->use_anhor_test());
    REQUIRE(test->configure_frame_test());
    REQUIRE(test->configure_button_test());
    REQUIRE(test->configure_topLevel_test());
    REQUIRE(test->overflow_test());
    REQUIRE(test->set_screen_location_test());
    REQUIRE(test->set_screen_abs_location_test());
    REQUIRE(test->set_screen_rel_location_test());
    REQUIRE(test->get_parent_test());
    REQUIRE(test->set_children_test());
    REQUIRE(test->get_border_width_test());
    REQUIRE(test->add_tag_test());
    REQUIRE(test->remove_tag_test());
    REQUIRE(test->get_requested_size_test());
    REQUIRE(test->get_content_rect_test());
    REQUIRE(test->get_anchor_test());
    REQUIRE(test->get_type_test());
    REQUIRE(test->Frame_test());
    REQUIRE(test->Button_test());
    delete test;
}

TEST_CASE("class_GeometryManager_and_Placer", "[unit]")
{
    Placer_test *test = new Placer_test();
    REQUIRE(test->actualize_pos_test());
    REQUIRE(test->actualize_size_test());
    REQUIRE(test->run_test());
    REQUIRE(test->configure_test());
    REQUIRE(test->release_test());
    delete test;
}

TEST_CASE("class_EventManager", "[unit]")
{
    Event_manager_test *test = new Event_manager_test();
    REQUIRE(test->bind_test());
    REQUIRE(test->unbind_test());
    REQUIRE(test->check_event_callback_test());
    delete test;
}

TEST_CASE("class_TopLevel", "[unit]")
{
    Toplevel_test *test = new Toplevel_test();
    REQUIRE(test->get_resizable_test());
    REQUIRE(test->get_minimum_size_test());
    REQUIRE(test->set_content_rect_test());
    REQUIRE(test->ToplevelTest());
    delete test;
}

TEST_CASE("class_Entry", "[unit]")
{
    Entry_test *test = new Entry_test();
    REQUIRE(test->add_char_test());
    REQUIRE(test->delete_char_test());
    REQUIRE(test->set_has_focus_test());
    REQUIRE(test->set_cursor_position_test());
    delete test;
}

TEST_CASE("internals_calbacks", "[unit]")
{
    ei::Size size(500, 500);
    Internals_calback_test *test = new Internals_calback_test(&size);
    REQUIRE(test->button_pressed_test());
    REQUIRE(test->close_toplevel_test());
    REQUIRE(test->select_entry_test());
    REQUIRE(test->select_check_box_test());
    REQUIRE(test->select_button_radio_test());
    REQUIRE(test->check_to_desable_test());
    delete test;
}

int ei_main(int argc, char* argv[])
{
    int result = Catch::Session().run( argc, argv );
    return result;
}
