#include <stdio.h>
#include <stdlib.h>

#include "ei_main.h"
#include "ei_application.h"
#include "ei_event.h"
#include "ei_geometrymanager.h"
#include "ei_widget.h"
#include "hw_interface.h"
#include "ei_types.h"

using namespace ei;

/*
 * ei_main --
 *
 *	Main function of the application.
 */
int ei_main(int argc, char** argv)
{
    Size screen_size = Size(600, 600);
    color_t root_bgcol = { 0x52, 0x7f, 0xb4, 0xff };

    Size frame_size = Size(300, 200);
    int frame_x = 150;
    int frame_y = 200;
    color_t frame_color = { 0x88, 0x88, 0x88, 0xff };
    relief_t frame_relief = ei_relief_raised;
    int frame_border_width = 5;
    anchor_t img_anchor = ei_anc_center;

    /* Create the application and change the color of the background. */
    Application* app = new Application(&screen_size);
    app->root_widget()->configure(&screen_size, &root_bgcol, NULL, NULL, NULL, NULL,
                                  NULL, NULL, NULL, NULL, NULL);

    /* Create, configure and place another frame */
    surface_t image = hw_image_load(DATA_DIR"ordi_mini.jpg");
    Frame* frame = new Frame(app->root_widget());
    frame->configure(&frame_size, &frame_color, &frame_border_width,
                     &frame_relief, NULL, NULL, NULL, NULL, &image, NULL, &img_anchor);
    frame->set_name("frame_child2");
    Placer* p = new Placer();
    p->configure(frame, NULL, &frame_x, &frame_y, NULL, NULL, NULL, NULL, NULL, NULL);
    frame->print();
    /* Run the application's main loop. */
    app->run();

    /* We just exited from the main loop. Terminate the application (cleanup). */
    delete app;
    delete p;

    return (EXIT_SUCCESS);
}
