/**
  * \file widget_test.cpp
  * \brief contains class \ref ei::Widget_test definition
  * \author Bah elhadj amadou
  */


#include "widget_test.h"

using namespace ei;

Widget_test::Widget_test() : Frame(nullptr)
{
    app_size = Size(1000, 1000);
    app = new Application(&app_size);
}

Widget_test::~Widget_test(){
    delete app;
}

bool ei::Widget_test::get_top_left_test(){
    bool is_correct(true);
    ei::Rect screen(ei::Point(0, 0), ei::Size(300, 300));
    ei::Point top_left;
    // test1
    Frame *w = new Frame(app->getInstance()->root_widget());
    w->anchor = ei_anc_none;
    w->set_screen_location(&screen.top_left.x(), &screen.top_left.y(), &screen.size.width(), &screen.size.height());
    top_left = w->get_top_left();
    is_correct = is_correct && (top_left.x() == 0 && top_left.y() == 0);
    // test2
    w->set_anchor(ei_anc_center);
    top_left = w->get_top_left();
    is_correct = is_correct && (top_left.x() == (-150) && top_left.y() == (-150));

    return is_correct;
}

bool ei::Widget_test::pick_test(){
    bool is_correct(true);
    Widget *picked = new Frame(nullptr);
    Frame* frame1 = new Frame(app->getInstance()->root_widget());
    Frame* frame2 = new Frame(app->getInstance()->root_widget());

    app->getInstance()->root_widget()->pick(frame1->getPick_id(), &picked);
    is_correct = is_correct && (picked->getPick_id() == frame1->getPick_id());

    app->getInstance()->root_widget()->pick(frame2->getPick_id(), &picked);
    is_correct = is_correct && (picked->getPick_id() == frame2->getPick_id());

    return is_correct;
}

bool ei::Widget_test::swap_borer_color_test(){
    bool is_correct(true);
    color_t color_top_copy = {border_color_top.red, border_color_top.green, border_color_top.blue, border_color_top.alpha};
    color_t color_bottom_copy = {border_color_bottom.red, border_color_bottom.green, border_color_bottom.blue, border_color_bottom.alpha};

    swap_borer_color();

    is_correct = is_correct && (color_top_copy.red == border_color_bottom.red) && (color_top_copy.green == border_color_bottom.green) && (color_top_copy.blue == border_color_bottom.blue) && (color_top_copy.alpha == border_color_bottom.alpha);

    is_correct = is_correct && (color_bottom_copy.red == border_color_top.red) && (color_bottom_copy.green == border_color_top.green) && (color_bottom_copy.blue == border_color_top.blue) && (color_bottom_copy.alpha == border_color_top.alpha);

    return is_correct;
}

bool ei::Widget_test::use_anhor_test(){
    bool is_correct(true);
    ei::Point widget_top_left(100, 100);
    ei::Size widget_size(200, 200);
    ei::Size text_surface(50, 50);
    ei::Point pos;
    //test1
    pos = use_anchor(widget_top_left, widget_size, text_surface, ei_anc_none);
    is_correct = is_correct && (pos.x() == 100 && pos.y() == 100);
    //test2
    pos = use_anchor(widget_top_left, widget_size, text_surface, ei_anc_center);
    is_correct = is_correct && (pos.x() == 175 && pos.y() == 175);
    //test3
    pos = use_anchor(widget_top_left, widget_size, text_surface, ei_anc_southeast);
    is_correct = is_correct && (pos.x() == 250 && pos.y() == 250);

    return is_correct;
}

bool ei::Widget_test::configure_frame_test(){
    bool is_correct(true);
    // test1: default values (without text and image)
    Size req_size(0, 0);
    color_t color = default_background_color;
    int b_width = 0;
    relief_t reli = ei_relief_none;
    anchor_t t_anc(ei_anc_center);
    anchor_t img_anc(ei_anc_center);
    configure(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    is_correct = is_correct && requested_size == req_size && text == nullptr && text_anchor == ei_anc_center && img_anc == ei_anc_center && border_width == b_width && relief == reli && text_anchor == t_anc;

    // test2: overrides last values
    req_size = ei::Size(50, 50);
    b_width = 5;
    reli = ei_relief_raised;
    t_anc = ei_anc_east;
    img_anc = ei_anc_south;
    configure(&req_size, &color, &b_width, &reli, nullptr, nullptr,nullptr,&t_anc, nullptr, nullptr, &img_anc);
    is_correct = is_correct && requested_size == req_size && text == nullptr && text_anchor == t_anc && img_anchor == img_anc && border_width == b_width && relief == reli && text_anchor == t_anc;

    return is_correct;
}

bool ei::Widget_test::configure_button_test(){
    bool is_correct(true);
    // test1: default values (without text and image)
    Button *button = new Button(nullptr);
    Size req_size(0, 0);
    color_t color = default_background_color;
    int b_width = 0;
    relief_t reli = ei_relief_none;
    anchor_t t_anc(ei_anc_center);
    anchor_t img_anc(ei_anc_center);
    int cor_radius = default_button_corner_radius;
    button->configure(nullptr, nullptr, nullptr, &cor_radius, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    is_correct = is_correct && button->requested_size == req_size && button->text_anchor == t_anc && button->img_anchor == img_anc && button->border_width == b_width && button->relief == reli && button->text_anchor == t_anc && button->corner_radius == cor_radius;

    // test2: overrides last values
    req_size = ei::Size(50, 50);
    b_width = 5;
    reli = ei_relief_raised;
    t_anc = ei_anc_east;
    img_anc = ei_anc_south;
    cor_radius = 20;
    button->configure(&req_size, &color, &b_width, &cor_radius,&reli, nullptr, nullptr,nullptr,&t_anc, nullptr, nullptr, &img_anc);
    is_correct = is_correct && requested_size == req_size && text == nullptr && text_anchor == t_anc && img_anchor == img_anc && border_width == b_width && relief == reli && text_anchor == t_anc && button->corner_radius == cor_radius;

    delete button;
    return is_correct;
}

bool ei::Widget_test::configure_topLevel_test(){
    bool is_correct(true);
    Toplevel *toplevel = new Toplevel(nullptr);
    // test1: default value
    int b_width(4);
    Size req_size(320 + (b_width * 2), 240 + ei::Toplevel::title_bar_height);
    const char* tit = "Toplevel";
    bool_t clos(EI_TRUE);
    axis_set_t resiz(ei_axis_both);
    Size min(160, 120);
    toplevel->configure(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    is_correct = is_correct && toplevel->requested_size == req_size && toplevel->border_width == b_width && toplevel->is_closable == clos && toplevel->resizable == resiz && toplevel->min_size == min;
    // test2: overrides values
    req_size = ei::Size(500, 500);
    b_width = 5;
    clos = EI_FALSE;
    resiz = ei_axis_x;
    toplevel->configure(&req_size, nullptr, &b_width, &tit, &clos, &resiz, &min);
    return is_correct;
}

bool ei::Widget_test::overflow_test(){
    bool is_correct(true);
    Frame* parent = new Frame(nullptr);
    Frame* child = new Frame(parent);
    parent->content_rect->top_left = ei::Point(200, 200);
    parent->content_rect->size = ei::Size(300, 300);
    // test1
    child->screen_location.top_left = ei::Point(100, 00);
    child->screen_location.size = ei::Size(50, 50);
    is_correct = is_correct && child->overflow(&parent->content_rect) && child->out;
    // test2
    child->screen_location.top_left = ei::Point(600, 600);
    is_correct = is_correct && child->overflow(&parent->content_rect) && child->out;

    return is_correct;
}

bool ei::Widget_test::set_screen_location_test(){
    bool is_correct(true);
    int x(5), y(10);
    float width(100), height(100);
    set_screen_location(&x, &y, &width, &height);
    is_correct = is_correct && (screen_location.top_left.x() == 5) && (screen_location.top_left.y() == 10) && (screen_location.size.width() == width) && (screen_location.size.height() == height);
    return is_correct;
}

bool ei::Widget_test::set_screen_abs_location_test(){
    bool is_correct(true);
    int x(5), y(10);
    float width(100), height(100);
    set_screen_abs_location(&x, &y, &width, &height);
    is_correct = is_correct && (screen_abs_location.top_left.x() == 5) && (screen_abs_location.top_left.y() == 10) && (screen_abs_location.size.width() == width) && (screen_abs_location.size.height() == height);
    return is_correct;
}

bool ei::Widget_test::set_screen_rel_location_test(){
    bool is_correct(true);
    float x(5), y(10);
    float width(100), height(100);
    set_screen_rel_location(&x, &y, &width, &height);
    is_correct = is_correct && (screen_rel_location.top_left.x() == x) && (screen_rel_location.top_left.y() == y) && (screen_rel_location.size.width() == width) && (screen_rel_location.size.height() == height);
    return is_correct;
}

bool ei::Widget_test::get_parent_test(){
    bool is_correct(true);
    Frame* parent = new Frame(nullptr);
    parent->set_name("father!");
    this->parent = parent;
    is_correct = is_correct && getParent()->get_name()=="father!";
    return is_correct;
}

bool ei::Widget_test::set_children_test(){
    bool is_correct(true);
    Frame* child = new Frame(nullptr);
    child->set_name("child");
    set_children(child);
    is_correct =  is_correct && children.front()->get_name()=="child";
    return is_correct;
}

bool ei::Widget_test::get_border_width_test(){
    bool is_correct(true);
    this->border_width = 5000;
    return is_correct && border_width == 5000;
}

bool ei::Widget_test::add_tag_test(){
    bool is_correct(true);
    tag_id.clear();
    add_tag("c++");
    is_correct = is_correct && tag_id.front() == "c++";
    return is_correct;

}

bool ei::Widget_test::remove_tag_test(){
    tag_id.clear();
    add_tag("zuckerberg");
    add_tag("bordeaux university");
    add_tag("jack daniel");

    remove_tag("zuckerberg");
    remove_tag("bordeaux university");
    remove_tag("jack daniel");
    return tag_id.size() == 0;
}


bool ei::Widget_test::get_requested_size_test(){
    requested_size = ei::Size(500, 150);
    return get_requested_size().width() == 500.f && get_requested_size().height() == 150.f;
}

bool ei::Widget_test::get_content_rect_test(){
    int x(5), y(5);
    float width(500), height(500);
    border_width = 0;
    set_content_rec(&x, &y, &width, &height);
    return content_rect->top_left.x() == 5 && content_rect->top_left.y() == 5 && content_rect->size.width() == width && content_rect->size.height() == height;
}

bool ei::Widget_test::get_anchor_test(){
    anchor = ei_anc_none;
    return get_anchor() == ei_anc_none;
}

bool ei::Widget_test::get_type_test(){
    bool is_correct(true);
    Frame* frame = new Frame(nullptr);
    Button *button = new Button(nullptr);
    Toplevel *toplevel = new Toplevel(nullptr);
    is_correct = is_correct && frame->get_type()=="Frame" && button->get_type()=="Button" && toplevel->get_type()=="Toplevel";
    return  is_correct;
}

bool ei::Widget_test::Frame_test(){
    bool is_correct(true);
    set_name("father");
    Frame* frame = new Frame(this);
    frame->set_name("child");
    is_correct = is_correct && frame->parent->get_name() == "father";
    is_correct = is_correct && frame->getParent()->get_children().front()->get_name() == "child";
    return is_correct;
}

bool ei::Widget_test::Button_test(){
    Button* button = new Button(nullptr);
    delete button;
    return true;
}
