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

Placer* p_generic = new Placer();

ei::bool_t process_key(Widget* widget, Event* event, void* user_param)
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

bool_t click_br1(Widget* widget, Event* event, void* user_param)
{
    ei::Button *buton = static_cast<ei::Button*>(user_param);
    anchor_t anchor(ei_anc_northwest);
    buton->configure(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,nullptr,nullptr, &anchor,nullptr, nullptr, nullptr);
    return EI_FALSE;
}

bool_t click_br2(Widget* widget, Event* event, void* user_param)
{
    ei::Button *buton = static_cast<ei::Button*>(user_param);
    anchor_t anchor(ei_anc_southwest);
    buton->configure(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,nullptr,nullptr, &anchor,nullptr, nullptr, nullptr);
    return EI_FALSE;
}

bool_t click_br3(Widget* widget, Event* event, void* user_param)
{
    ei::Button *buton = static_cast<ei::Button*>(user_param);
    anchor_t anchor(ei_anc_northeast);
    buton->configure(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,nullptr,nullptr, &anchor,nullptr, nullptr, nullptr);
    return EI_FALSE;
}

bool_t click_br4(Widget* widget, Event* event, void* user_param)
{
    ei::Button *buton = static_cast<ei::Button*>(user_param);
    anchor_t anchor(ei_anc_northwest);
    p_generic->configure(buton, &anchor, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    return EI_FALSE;
}

bool_t click_br5(Widget* widget, Event* event, void* user_param)
{
    ei::Button *buton = static_cast<ei::Button*>(user_param);
    anchor_t anchor(ei_anc_southwest);
    p_generic->configure(buton, &anchor, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    return EI_FALSE;
}

bool_t click_br6(Widget* widget, Event* event, void* user_param)
{
    ei::Button *buton = static_cast<ei::Button*>(user_param);
    anchor_t anchor(ei_anc_northeast);
    p_generic->configure(buton, &anchor, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    return EI_FALSE;
}

bool_t click_br7(Widget* widget, Event* event, void* user_param)
{
    ei::Button *buton = static_cast<ei::Button*>(user_param);
    float rel_y(0.0);
    p_generic->configure(buton, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, &rel_y, nullptr, nullptr);
    return EI_FALSE;
}

bool_t click_br8(Widget* widget, Event* event, void* user_param)
{
    ei::Button *buton = static_cast<ei::Button*>(user_param);
    float rel_y(0.8);
    p_generic->configure(buton, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, &rel_y, nullptr, nullptr);
    return EI_FALSE;
}

bool_t click_br9(Widget* widget, Event* event, void* user_param)
{
    ei::Button *buton = static_cast<ei::Button*>(user_param);
    float rel_x(0.0);
    p_generic->configure(buton, nullptr, nullptr, nullptr, nullptr, nullptr, &rel_x, nullptr, nullptr, nullptr);
    return EI_FALSE;
}

using namespace ei;

int ei_main(int argc, char* argv[]){
    Size         screen_size(1000, 800);
    color_t      root_bgcol      = {0x52, 0x7f, 0xb4, 0xff};

    float        button_rel_x    = 0.5;
    float        button_rel_y    = 0.5;
    color_t      button_color    = {0x88, 0x88, 0x88, 0xff};
    color_t      text_color      = {0x00, 0x00, 0x00, 0xff};
    Size         button_size     = Size(300,100);
    int          button_border_width = 3;
    const char         *bt_text = "un bouton";
    anchor_t    bt_anchor(ei_anc_center);
    int frame_border_width(2);

    color_t color_frame_bis_min = {255, 0, 0, 255};
    int br_x(5), br1_y(15);
    int br2_y(55), br3_y(100);
    int  frame_bis_min_x(10), frame_bis1_min_y(10);
    float frame_bis_min_width(210), frame_bis_min_height(150);

    int label_x(30), label1_y(10), label2_y(55), label3_y(100);


    const char* label1_text = "ei_anc_northwest";
    const char* label2_text = "ei_anc_south_west";
    const char* label3_text = "ei_anc_north_east";

    Application* app = new Application(&screen_size);
    app->root_widget()->configure(&screen_size, &root_bgcol, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    /************************ Version minimale fonctionnalités *****************************/
    ei::Size requested_size_frame_min(500, 500);
    int frame_min_x(10), frame_min_y(10);
    float frame_min_width(900), frame_min_height(600);
    Frame* frame_minimal = new Frame(app->root_widget());
    frame_minimal->configure(&requested_size_frame_min, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    Placer *p_frame_min = new Placer();
    p_frame_min->configure(frame_minimal, nullptr, &frame_min_x, &frame_min_y, &frame_min_width, &frame_min_height, nullptr, nullptr, nullptr, nullptr);

    // frame parent du bouton demo
    int frame_par_x(115);
    int bt_frame_min_x(0), bt_frame_min_y(0);
    ei::Size frame_par_size(600, 500);
    Frame* frame_par = new Frame(frame_minimal);
    frame_par->configure(&frame_par_size, &color_frame_bis_min, &frame_border_width, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    p_frame_min->configure(frame_par, &bt_anchor, &frame_par_x, &bt_frame_min_y, nullptr, nullptr, &button_rel_x, &button_rel_y, nullptr, nullptr);
    // un bouton du frame minimal
    Button *bt_frame_min = new Button(frame_par);
    bt_frame_min->configure(&button_size, &button_color, &button_border_width, nullptr, nullptr, &bt_text, nullptr, &text_color, nullptr, nullptr, nullptr, nullptr);
    Placer *p_bt_frame_min = new Placer();
    p_bt_frame_min->configure(bt_frame_min, &bt_anchor, &bt_frame_min_x, &bt_frame_min_y, nullptr, nullptr, &button_rel_x, &button_rel_y, nullptr, nullptr);

    // demo anchor text
    Frame *frame_anc_text = new Frame(frame_minimal);
    frame_anc_text->configure(&requested_size_frame_min, &color_frame_bis_min, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    p_frame_min->configure(frame_anc_text, nullptr, &frame_bis_min_x, &frame_bis1_min_y, &frame_bis_min_width, &frame_bis_min_height, nullptr, nullptr, nullptr, nullptr);
    RB_Groupe group;
    Button_radio *bt_radio1 = new Button_radio(frame_anc_text, &group);
    Frame* label1 = new Frame(frame_anc_text);
    label1->configure(nullptr, nullptr, nullptr, nullptr, &label1_text, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    Button_radio *bt_radio2 = new Button_radio(frame_anc_text, &group);
    Frame* label2 = new Frame(frame_anc_text);
    label2->configure(nullptr, nullptr, nullptr, nullptr, &label2_text, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    Button_radio *bt_radio3 = new Button_radio(frame_anc_text, &group);
    Frame* label3 = new Frame(frame_anc_text);
    label3->configure(nullptr, nullptr, nullptr, nullptr, &label3_text, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);

    Placer* p_br = new Placer();
    p_br->configure(bt_radio1, NULL, &br_x, &br1_y, nullptr, nullptr, nullptr,nullptr, nullptr, nullptr);
    p_br->configure(bt_radio2, NULL, &br_x, &br2_y, nullptr, nullptr, nullptr,nullptr, nullptr, nullptr);
    p_br->configure(bt_radio3, NULL, &br_x, &br3_y, nullptr, nullptr, nullptr,nullptr, nullptr, nullptr);

    p_frame_min->configure(label1, nullptr, &label_x, &label1_y, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    p_frame_min->configure(label2, nullptr, &label_x, &label2_y, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    p_frame_min->configure(label3, nullptr, &label_x, &label3_y, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);

    // demo widget anchor
    int frame_anc_widget_y(200);
    Frame *frame_anc_widget = new Frame(frame_minimal);
    frame_anc_widget->configure(&requested_size_frame_min, &color_frame_bis_min, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    p_frame_min->configure(frame_anc_widget, nullptr, &frame_bis_min_x, &frame_anc_widget_y, &frame_bis_min_width, &frame_bis_min_height, nullptr, nullptr, nullptr, nullptr);
    RB_Groupe group2;
    Button_radio *bt_radio4 = new Button_radio(frame_anc_widget, &group2);
    Frame* label4 = new Frame(frame_anc_widget);
    label4->configure(nullptr, nullptr, nullptr, nullptr, &label1_text, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    Button_radio *bt_radio5 = new Button_radio(frame_anc_widget, &group2);
    Frame* label5 = new Frame(frame_anc_widget);
    label5->configure(nullptr, nullptr, nullptr, nullptr, &label2_text, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    Button_radio *bt_radio6 = new Button_radio(frame_anc_widget, &group2);
    Frame* label6 = new Frame(frame_anc_widget);
    label6->configure(nullptr, nullptr, nullptr, nullptr, &label3_text, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);

    p_br->configure(bt_radio4, NULL, &br_x, &br1_y, nullptr, nullptr, nullptr,nullptr, nullptr, nullptr);
    p_br->configure(bt_radio5, NULL, &br_x, &br2_y, nullptr, nullptr, nullptr,nullptr, nullptr, nullptr);
    p_br->configure(bt_radio6, NULL, &br_x, &br3_y, nullptr, nullptr, nullptr,nullptr, nullptr, nullptr);

    p_frame_min->configure(label4, nullptr, &label_x, &label1_y, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    p_frame_min->configure(label5, nullptr, &label_x, &label2_y, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    p_frame_min->configure(label6, nullptr, &label_x, &label3_y, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);

    //demo positionnement rélatif
    const char *text_pos1 = "0.0 en Y";
    const char * text_pos2 = "0.8 en Y";
    const char * text_pos3 = "0.0 en X";
    int frame_anc_pos_y(370);
    Frame *frame_anc_pos = new Frame(frame_minimal);
    frame_anc_pos->configure(&requested_size_frame_min, &color_frame_bis_min, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    p_frame_min->configure(frame_anc_pos, nullptr, &frame_bis_min_x, &frame_anc_pos_y, &frame_bis_min_width, &frame_bis_min_height, nullptr, nullptr, nullptr, nullptr);
    RB_Groupe group3;
    Button_radio *bt_radio7 = new Button_radio(frame_anc_pos, &group3);
    Frame* label7 = new Frame(frame_anc_pos);
    label7->configure(nullptr, nullptr, nullptr, nullptr, &text_pos1, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    Button_radio *bt_radio8 = new Button_radio(frame_anc_pos, &group3);
    Frame* label8 = new Frame(frame_anc_pos);
    label8->configure(nullptr, nullptr, nullptr, nullptr, &text_pos2, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    Button_radio *bt_radio9 = new Button_radio(frame_anc_pos, &group3);
    Frame* label9 = new Frame(frame_anc_pos);
    label9->configure(nullptr, nullptr, nullptr, nullptr, &text_pos3, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);

    p_br->configure(bt_radio7, NULL, &br_x, &br1_y, nullptr, nullptr, nullptr,nullptr, nullptr, nullptr);
    p_br->configure(bt_radio8, NULL, &br_x, &br2_y, nullptr, nullptr, nullptr,nullptr, nullptr, nullptr);
    p_br->configure(bt_radio9, NULL, &br_x, &br3_y, nullptr, nullptr, nullptr,nullptr, nullptr, nullptr);

    p_frame_min->configure(label7, nullptr, &label_x, &label1_y, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    p_frame_min->configure(label8, nullptr, &label_x, &label2_y, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    p_frame_min->configure(label9, nullptr, &label_x, &label3_y, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);



    // binding
    EventManager::getInstance().bind(ei_ev_keydown, NULL, "all", process_key, app);
    EventManager::getInstance().bind(ei_ev_display, NULL, "all", process_display, app);

    EventManager::getInstance().bind(ei_ev_mouse_buttondown, bt_radio1, "", click_br1, bt_frame_min);
    EventManager::getInstance().bind(ei_ev_mouse_buttondown, bt_radio2, "", click_br2, bt_frame_min);
    EventManager::getInstance().bind(ei_ev_mouse_buttondown, bt_radio3, "", click_br3, bt_frame_min);

    EventManager::getInstance().bind(ei_ev_mouse_buttondown, bt_radio4, "", click_br4, bt_frame_min);
    EventManager::getInstance().bind(ei_ev_mouse_buttondown, bt_radio5, "", click_br5, bt_frame_min);
    EventManager::getInstance().bind(ei_ev_mouse_buttondown, bt_radio6, "", click_br6, bt_frame_min);

    EventManager::getInstance().bind(ei_ev_mouse_buttondown, bt_radio7, "", click_br7, bt_frame_min);
    EventManager::getInstance().bind(ei_ev_mouse_buttondown, bt_radio8, "", click_br8, bt_frame_min);
    EventManager::getInstance().bind(ei_ev_mouse_buttondown, bt_radio9, "", click_br9, bt_frame_min);


    app->run();

    delete p_br;
    delete p_frame_min;
    delete p_bt_frame_min;
    delete app;

    return 0;
}
