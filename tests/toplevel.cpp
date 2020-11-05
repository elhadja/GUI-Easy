#include <stdio.h>
#include <stdlib.h>

#include "ei_application.h"
#include "ei_eventmanager.h"
#include "hw_interface.h"
#include "ei_widget.h"
#include "ei_geometrymanager.h"
#include "ei_button_radio.h"
#include "ei_check_box.h"
#include "ei_entry.h"

#include <iostream>

using namespace ei;

bool_t process_br1(Widget* widget, Event* event, void* user_param)
{
    color_t color = {255, 255, 0, 255};
    static_cast<Toplevel*>(static_cast<Button_radio*>(widget)->getParent())->configure(nullptr, &color, nullptr, nullptr, nullptr, nullptr, nullptr);
    return EI_FALSE;
}

bool_t process_br2(Widget* widget, Event* event, void* user_param)
{
    color_t color = {255, 0, 255, 255};
    static_cast<Toplevel*>(static_cast<Button_radio*>(widget)->getParent())->configure(nullptr, &color, nullptr, nullptr, nullptr, nullptr, nullptr);
    return EI_FALSE;
}

bool_t process_key(Widget* widget, Event* event, void* user_param)
{
    if (static_cast<KeyEvent*>(event)->key_sym == ALLEGRO_KEY_ESCAPE) {
        static_cast<Application*>(user_param)->quit_request();
        return EI_TRUE;
    }

    return EI_FALSE;
}
bool_t process_display(Widget* widget, Event* event, void* user_param)
{
    if (static_cast<DisplayEvent*>(event)->closed == EI_TRUE) {
        static_cast<Application*>(user_param)->quit_request();
        return EI_TRUE;
    }

    return EI_FALSE;
}

bool_t process_test(Widget* widget, Event* event, void* user_param)
{
   std::cout<<"test"<<std::endl;
   return EI_TRUE;
}
int ei_main(int argc, char* argv[])
{
    Size         screen_size(1400, 900);
    color_t      root_bgcol      = {0x52, 0x7f, 0xb4, 0xff};

    color_t      button_color    = {0x88, 0x88, 0x88, 0xff};
    color_t      text_color      = {0x00, 0x00, 0x00, 0xff};
    Size         button_size     = Size(100,40);
    relief_t     relief          = ei_relief_raised;
    int          button_border_width = 3;
    const char*  button_title_ok     = "Okkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk";
    const char*  button_title_cancel = "Cancel";
    const char*  button_title_cut = "Cutttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt";

    anchor_t button_anchor   = ei_anc_southeast;
    anchor_t button_anchor_2   = ei_anc_southwest;
    float   button_rel_x    = 1.0;
    float   button_rel_y    = 1.0;
    float   button_rel_x2    = 0.0;
    int     button_x    = -10;
    int     button_y    = -10;
    int     button_x2   = 10;
    int     button_y2   = -262;
    float   button_rel_size_x = 0.45f;

    Size         window_size(600,500);
    const char*  window_title    = "Window";
    color_t      window_color    = {0xA0,0xA0,0xA0, 0xff};
    int          window_border_width    = 3;
    bool_t       closable        = EI_TRUE;
    axis_set_t   window_resizable = ei_axis_both;
    Point        window_position(400, 400);
    anchor_t window_anchor(ei_anc_center);

    int entry_border(1);

    Application* app = new Application(&screen_size);
    app->root_widget()->configure(&screen_size, &root_bgcol, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    Toplevel* toplevel = new Toplevel(app->root_widget());
    toplevel->configure(&window_size, &window_color, &window_border_width, &window_title, &closable, &window_resizable, NULL);

    Button* button_ok = new Button(toplevel);
    button_ok->set_name("bouton_ok");
    button_ok->configure (&button_size, &button_color, &button_border_width, NULL, &relief, &button_title_ok, NULL, &text_color, NULL, NULL, NULL, NULL);
    button_ok->add_tag("ei_movable");

    Button* button_cancel = new Button(toplevel);
    button_cancel->set_name("bouton_cancel");
    button_cancel->configure (&button_size, &button_color, &button_border_width, NULL, &relief, &button_title_cancel, NULL, &text_color, NULL, NULL, NULL, NULL);
    button_cancel->add_tag("ei_movable", "ei_tooltip");

    Button* button_cut = new Button(toplevel);
    button_cut->set_name("button_cut");
    button_cut->configure (&button_size, &button_color, &button_border_width, NULL, &relief, &button_title_cut, NULL, &text_color, NULL, NULL, NULL, NULL);
    button_cut->add_tag("test");
    button_cut->add_tag("ei_movable", "ei_tooltip");
    button_cut->set_tool_tip("un bouton qui deborde");

    RB_Groupe group;
    int br_x(10), br_y(10);
    int br2_y(40);
    Button_radio *bt_radio1 = new Button_radio(toplevel, &group);
    Button_radio *bt_radio2 = new Button_radio(toplevel, &group);
    bt_radio1->add_tag("ei_movable");

    Placer* p_br = new Placer();

    int c_box1_y(110), c_box2_y(140);
    Check_box* c_box1 = new Check_box(toplevel);
    Check_box* c_box2 = new Check_box(toplevel);
    c_box1->add_tag("ei_movable");
    c_box2->add_tag("ei_movable");
    c_box2->set_tool_tip("faites votre choix");
    Placer* p_check = new Placer();


    int entry_y1(170), entry_y2(220), entry_y3(270);
    ei::Size entry_size(200, 40);
    Entry *entry1 = new Entry(toplevel);
    Entry *entry2 = new Entry(toplevel);
    Entry_pwd *entry3 = new Entry_pwd(toplevel);
    const char* entry_text = "entry";
    Placer* p_entry = new Placer();
    entry1->configure(&entry_size, nullptr, &entry_border, nullptr, &entry_text, nullptr, nullptr, nullptr);
    entry1->add_tag("ei_tooltip");
    entry1->set_tool_tip("un champs de texte");
    entry2->configure(&entry_size, nullptr, &entry_border, nullptr, &entry_text, nullptr, nullptr, nullptr);
    entry2->add_tag("ei_movable");
    entry3->configure(&entry_size, nullptr, &entry_border, nullptr, nullptr, nullptr, nullptr, nullptr);
    entry3->add_tag("ei_tooltip");
    entry3->set_tool_tip("un champs de saisie pour mot de passe");

    Placer* p1 = new Placer();
    p1->configure(toplevel, &window_anchor, &(window_position.x()), &(window_position.y()), NULL, NULL, nullptr, nullptr, NULL, NULL);
    Placer* p2 = new Placer();
    p2->configure(button_ok, &button_anchor, &button_x, &button_y, NULL,NULL, &button_rel_x, &button_rel_y, &button_rel_size_x, NULL);
    Placer* p3 = new Placer();
    p3->configure(button_cancel, &button_anchor_2, &button_x2, &button_y, NULL,NULL, &button_rel_x2, &button_rel_y, &button_rel_size_x, NULL);
    Placer* p4 = new Placer();
    p4->configure(button_cut, &button_anchor, &button_x2, &button_y2, NULL,NULL, &button_rel_x, &button_rel_y, &button_rel_size_x, NULL);

    p_br->configure(bt_radio1, NULL, &br_x, &br_y, nullptr, nullptr, nullptr,nullptr, nullptr, nullptr);
    p_br->configure(bt_radio2, NULL, &br_x, &br2_y, nullptr, nullptr, nullptr,nullptr, nullptr, nullptr);

    p_check->configure(c_box1, NULL, &br_x, &c_box1_y, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    p_check->configure(c_box2, NULL, &br_x, &c_box2_y, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);

    p_entry->configure(entry1, nullptr, &br_x, &entry_y1, &entry_size.width(), &entry_size.height(), nullptr, nullptr, nullptr, nullptr);
    p_entry->configure(entry2, nullptr, &br_x, &entry_y2, &entry_size.width(), &entry_size.height(), nullptr, nullptr, nullptr, nullptr);
    p_entry->configure(entry3, nullptr, &br_x, &entry_y3, &entry_size.width(), &entry_size.height(), nullptr, nullptr, nullptr, nullptr);


    EventManager::getInstance().bind(ei_ev_keydown, NULL, "all", process_key, app);
    EventManager::getInstance().bind(ei_ev_display, NULL, "all", process_display, app);
    EventManager::getInstance().bind(ei_ev_mouse_buttondown, NULL, "test", process_test, app);

    EventManager::getInstance().bind(ei_ev_mouse_buttondown, bt_radio1, "", process_br1, app);
    EventManager::getInstance().bind(ei_ev_mouse_buttondown, bt_radio2, "", process_br2, app);


    app->run();

    delete app;
    delete p1;
    delete p2;
    delete p3;
    delete p4;
    delete p_check;
    delete p_entry;
    delete p_br;

    return (EXIT_SUCCESS);
}
