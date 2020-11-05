#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "ei_main.h"
#include "ei_application.h"
#include "ei_event.h"
#include "ei_geometrymanager.h"
#include "ei_widget.h"
#include "hw_interface.h"
#include "ei_eventmanager.h"

using namespace ei;


/*
 * button_press --
 *
 *  Callback called when a user clicks on the button.
 */
bool_t enlarge(Widget* widget, Event* event, void* user_param)
{
    //std::cout << "enlarge " << e->button_number << std::endl;
    Size size1(widget->getParent()->get_screen_abs_location().size);
    Size size(size1.width()+5, size1.height()+5);
    widget->getParent()->set_screen_abs_location(nullptr, nullptr, &size.width(), &size.height());
    Placer *p = new Placer();
    p->run(widget->getParent());
    static_cast<Application*>(user_param)->invalidate_rect(static_cast<Application*>(user_param)->root_widget()->get_screen_location());
    return EI_TRUE;
}



bool_t reduce(Widget* widget, Event* event, void* user_param)
{
    //std::cout << "reduce " << e->button_number << std::endl;
        Size size1(widget->getParent()->get_screen_abs_location().size);
    Size size(size1.width()-5, size1.height()-5);
    widget->getParent()->set_screen_abs_location(nullptr, nullptr, &size.width(), &size.height());
    Placer *p = new Placer();
    p->run(widget->getParent());
    static_cast<Application*>(user_param)->invalidate_rect(static_cast<Application*>(user_param)->root_widget()->get_screen_location());
    return EI_TRUE;
}

/*
 * process_key --
 *
 *  Callback called when any key is pressed by the user.
 *  Simply looks for the "Escape" key to request the application to quit.
 */
bool_t process_key(Widget* widget, Event* event, void* user_param)
{
    if (static_cast<KeyEvent*>(event)->key_sym == ALLEGRO_KEY_ESCAPE) {
        static_cast<Application*>(user_param)->quit_request();
        return EI_TRUE;
    }

    return EI_FALSE;
}

/*
 * process_display --
 *
 *  Callback called when a display event occur.
 */
bool_t process_display(Widget* widget, Event* event, void* user_param)
{
    if (static_cast<DisplayEvent*>(event)->closed == EI_TRUE) {
        static_cast<Application*>(user_param)->quit_request();
        return EI_TRUE;
    }

    return EI_FALSE;
}



/*
 * ei_main --
 *
 *	Main function of the application.
 */
int ei_main(int argc, char** argv)
{
    Size screen_size = Size(600, 600);
    color_t root_bgcol = { 127, 127, 127, 255 };

    Size frame_size = Size(250, 250);
    int frame_x = 10;
    int frame_y = 10;
    color_t frame_color = { 255, 0, 0, 255 };
    relief_t frame_relief = ei_relief_raised;
    anchor_t frame_anchor = ei_anc_northwest;
    int frame_border_width = 6;

    /* Create the application and change the color of the background. */
    Application* app = new Application(&screen_size);
    app->root_widget()->configure(&screen_size, &root_bgcol, NULL, NULL, NULL, NULL,
                                  NULL, NULL, NULL, NULL, NULL);
    /* Create, configure and place the frame on screen. */
    Frame* frame = new Frame(app->root_widget());
     surface_t image = hw_image_load(DATA_DIR"ordi.jpg");
    frame->configure(&frame_size, &frame_color, &frame_border_width,
                     &frame_relief, NULL, NULL, NULL, NULL, &image, NULL, NULL);
    frame->set_name("frame_child_root1");
    Placer* p = new Placer();
    p->configure(frame, &frame_anchor, &frame_x, &frame_y, NULL, NULL, NULL, NULL, NULL, NULL);

    /* Create, configure and place the frame on screen. */
    Size frame2_size = Size(250, 250);
    int frame2_x = 270;
    int frame2_y = 10;
    color_t frame2_color = { 0, 255, 0, 255 };
    relief_t frame2_relief = ei_relief_raised;
    int frame2_border_width = 0;
    Frame* frame2 = new Frame(app->root_widget());
    frame2->configure(&frame2_size, &frame2_color, &frame2_border_width,
                     &frame2_relief, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    frame2->set_name("frame_child_root2");
    Placer* p2 = new Placer();
    p2->configure(frame2, NULL, &frame2_x, &frame2_y, NULL, NULL, NULL, NULL, NULL, NULL);

    /* Create and configure the button */
    Size    button_size = Size(200,200);
    int     button_x    = 0;
    int     button_y    = 0;
    color_t  button_color        = {0x88, 0x88, 0x88, 0xff};
    const char* button_title        = "2pacccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc";
    color_t  button_text_color   = {0x00, 0x00, 0x00, 0xff};
    int button_corner_radius        = 10;
    relief_t button_relief       = ei_relief_raised;
    int button_border_width      = 6;
    anchor_t text_anchor = ei_anc_center;
    anchor_t but_anchor = ei_anc_none;
    Button* button = new Button(frame2);
    button->configure (&button_size, &button_color,
                       &button_border_width, &button_corner_radius, &button_relief, &button_title, NULL, &button_text_color, &text_anchor,
                       NULL, NULL, NULL);
    button->set_name("bouton1");
    /* Place the button on screen. */
    Placer* p3 = new Placer();
    p3->configure(button, &but_anchor, &button_x, &button_y, NULL, NULL, NULL, NULL, nullptr, nullptr );

    /* Create and configure the button */
    int     button2_x    = -170;
    int     button2_y    = -40;
    float   button2_rel_x =1.0f, button2_rel_y=1.0;
    const char* button2_title        = "Eminem";
    Button* button2 = new Button(frame2);
    button2->configure (&button_size, &button_color,
                       &button_border_width, &button_corner_radius, &button_relief, &button2_title, NULL, &button_text_color, &text_anchor,
                       NULL, NULL, NULL);
    button2->set_name("bouton2");
    /* Place the button on screen. */
    Placer* p4 = new Placer();
    p4->configure(button2, &but_anchor, &button2_x, &button2_y, NULL, NULL, &button2_rel_x, &button2_rel_y, NULL, NULL );

    /* Bind the button callbacks to the mouse events */
    EventManager::getInstance().bind(ei_ev_mouse_buttondown, button, "", enlarge, app);
    EventManager::getInstance().bind(ei_ev_mouse_buttonup, button2, "", reduce, app);

    /* Hook the keypress and close button callbacks to the event. */
    EventManager::getInstance().bind(ei_ev_keydown, NULL, "all", process_key, app);
    EventManager::getInstance().bind(ei_ev_display, NULL, "all", process_display, app);


    /* Run the application's main loop. */
    app->run();

    /* We just exited from the main loop. Terminate the application (cleanup). */
    delete app;
    delete p;

    return (EXIT_SUCCESS);
}
