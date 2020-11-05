#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "ei_main.h"
#include "ei_application.h"
#include "ei_event.h"
#include "ei_geometrymanager.h"
#include "ei_widget.h"
#include "hw_interface.h"

using namespace ei;

/*
 * ei_main --
 *
 *	Main function of the application.
 */
int ei_main(int argc, char** argv)
{
    Size screen_size = Size(600, 600);
    color_t root_bgcol = { 255, 255, 255, 255 };

    Size frame_size = Size(300, 200);
    int frame_x = 150;
    int frame_y = 200;
    color_t frame_color = { 255, 0, 0, 255};
    relief_t frame_relief = ei_relief_raised;
    int frame_border_width = 6;

    /* Create the application and change the color of the background. */
    Application* app = new Application(&screen_size);
    app->root_widget()->configure(&screen_size, &root_bgcol, NULL, NULL, NULL, NULL,
                                  NULL, NULL, NULL, NULL, NULL);
    app->root_widget()->print();
    /* Create, configure and place the frame on screen. */
    Frame* frame = new Frame(app->root_widget());
    frame->configure(&frame_size, &frame_color, &frame_border_width,
                     &frame_relief, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    frame->set_name("frame_child");
    Placer* p = new Placer();
    p->configure(frame, NULL, &frame_x, &frame_y, NULL, NULL, NULL, NULL, NULL, NULL);
    frame->print();
//    /* Create, configure and place another frame */
//    Size frameSize2 = Size(100, 100);
//    color_t frameColor2 = {0, 255, 0, 255};
//    color_t text_color = {0, 0, 0, 176};
//    int frame2_x = 200;
//    int frame2_y = 250;
//    char *text;
//    text = new char[10];
//    strcpy(text,"salut");
//    Frame* frame2 = new Frame(app->root_widget());
//    frame2->configure(&frameSize2, &frameColor2, &frame_border_width,
//                     &frame_relief, &text, NULL, &text_color, NULL, NULL, NULL, NULL);
//    frame2->set_name("frame_child2");
//    Placer* p2 = new Placer();
//    p2->configure(frame2, NULL, &frame2_x, &frame2_y, NULL, NULL, NULL, NULL, NULL, NULL);
//    frame2->print();
    /* Create, configure and place another frame */
    Size frameSize2 = Size(100, 100);
    color_t frameColor2 = {0, 255, 0, 255};
    int frame2_x = 200;
    int frame2_y = 250;
    surface_t image = hw_image_load(DATA_DIR"cross.png");
    Frame* frame2 = new Frame(app->root_widget());
    frame2->configure(&frameSize2, &frameColor2, &frame_border_width,
                     &frame_relief, NULL, NULL, NULL, NULL, &image, NULL, NULL);
    frame2->set_name("frame_child2");
    Placer* p2 = new Placer();
    p2->configure(frame2, NULL, &frame2_x, &frame2_y, NULL, NULL, NULL, NULL, NULL, NULL);
    frame2->print();
    /* Run the application's main loop. */
    app->run();

    /* We just exited from the main loop. Terminate the application (cleanup). */
    delete app;
    delete p;

    return (EXIT_SUCCESS);
}
