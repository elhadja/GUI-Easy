/**
  *\file ei_widget.cpp
  *\brief contains definitions of Widget class Widget\ref ei_widget.h
  *\author Pierre Benard, Modified by Bah elhad amadou and Remi
  */


#include <iostream>
#include <assert.h>

#include "ei_widget.h"
#include "ei_application.h"
#include "ei_geometrymanager.h"

uint32_t ei::Widget::s_idGenerator = 0;

ei::Widget::Widget(const widgetclass_name_t &class_name, Widget *parent):
    name(class_name), parent(parent)
{
    set_s_id_generator();
    pick_id = get_s_idGenerator();
    int RED=16, GREEN=8, BLUE=0;
    pick_color.red = pick_id >> RED & 0xff;
    pick_color.green = pick_id >> GREEN & 0xff;
    pick_color.blue = pick_id >> BLUE & 0xff;
    pick_color.alpha = 255;
    bckground_color = default_background_color;
    requested_size = Size(0.f, 0.f);
    screen_location.size = Size(0.f, 0.f);
    screen_location.top_left = Point(0, 0);
    anchor = ei_anc_none;
    screen_rel_location.top_left = Point(0.f, 0.f);
    screen_rel_location.size = Size(0.f, 0.f);
    geom_manager = nullptr;
    content_rect = new Rect();
    border_color_top = {0x00, 0x00, 0x00, 0xff};
    border_color_bottom = {0xff, 0x00, 0xff, 0xff};
    out = false;
    tooltip = nullptr;
}

ei::Widget::~Widget(){
    if(ei::Application::VERBOSE)
        std::cout<<"=====> destruction des Widgets: "<<name<<std::endl;
    delete content_rect;
    std::list<ei::Widget*>::iterator it;
    for(it=children.begin(); it!=children.end(); it++){
        delete (*it);
    }
}

void ei::Widget::geomnotify (Rect rect){
    screen_location = rect;
}

const ei::Size& ei::Widget::get_requested_size() const{
    return requested_size;
}

uint32_t ei::Widget::get_s_idGenerator(){
    return Widget::s_idGenerator;
}

void ei::Widget::set_s_id_generator()
{
    Widget::s_idGenerator += 1;
}

void ei::Widget::pick(uint32_t id, ei::Widget** w)
{
    if(pick_id == id){
        *w = this;
    }
    std::list<ei::Widget*>::iterator it;
    for(it=children.begin(); (it!=children.end() && (*w)->pick_id!=id); it++){
        (*it)->pick(id, w);
    }
}

uint32_t ei::Widget::getPick_id() const
{
    return pick_id;
}

ei::Widget *ei::Widget::getParent() const
{
    return parent;
}

bool ei::Widget::overflow(ei::Rect** clipper)
{
    if(parent == nullptr || name == "tooltip")
        return false;

    ei::Rect parent_rect(getParent()->get_content_rect().top_left, getParent()->get_content_rect().size);
    ei::Rect *new_clipper = new ei::Rect(get_top_left(), get_screen_location().size);
    bool overflow_b = false;
    if(new_clipper->top_left.x() < parent_rect.top_left.x()){ // overflow left
        overflow_b = true;
        new_clipper->size = ei::Size(new_clipper->size.width() - (parent_rect.top_left.x() - new_clipper->top_left.x()), new_clipper->size.height());
        new_clipper->top_left = ei::Point(parent_rect.top_left.x(), new_clipper->top_left.y());
    }
    if((new_clipper->top_left.x() + new_clipper->size.width()) > (parent_rect.top_left.x() + parent_rect.size.width())){ // overflow right
        overflow_b = true;
        new_clipper->size = ei::Size(parent_rect.size.width() - (new_clipper->top_left.x() - parent_rect.top_left.x()), new_clipper->size.height());
    }
    if(new_clipper->top_left.y() < parent_rect.top_left.y() && get_name()!="bouton_close"){ // overflow top
        overflow_b = true;
        new_clipper->size = ei::Size(new_clipper->size.width(), new_clipper->size.height() - (parent_rect.top_left.y() - new_clipper->top_left.y()));
        new_clipper->top_left = ei::Point(new_clipper->top_left.x(), parent_rect.top_left.y());
    }
    if((new_clipper->top_left.y() + new_clipper->size.height()) > (parent_rect.top_left.y() + parent_rect.size.height())){ // overflow bottom
        overflow_b = true;
        new_clipper->size = ei::Size(new_clipper->size.width(), parent_rect.size.height() - (new_clipper->top_left.y() - parent_rect.top_left.y()));
    }
    if(!overflow_b){
        delete new_clipper;
        out = false;
    }else{
        if(parent_rect.top_left.y() + parent_rect.size.height() <= get_top_left().y()
                || get_top_left().y() + screen_location.size.height() <= parent_rect.top_left.y()
                || parent_rect.top_left.x() + parent_rect.size.width() <= get_top_left().x()
                || get_top_left().x() + screen_location.size.width() <= parent_rect.top_left.x()){
            out = true;
        }else{
            out = false;
        }
        if(clipper != nullptr)
            *clipper = new_clipper;
        else {
            delete new_clipper;
        }
    }
    return overflow_b;
}

void ei::Widget::draw (surface_t surface, surface_t pick_surface, Rect* clipper)
{
    std::list<Widget*>::iterator it;
    for(it=children.begin(); it!=children.end(); it++){
        std::string name = (*it)->get_name();
        if(name == "button_cut"){
            std::cout<<"std::endl";
        }

        if((*it)->geom_manager!=nullptr){
            ei::Rect rect((*it)->get_top_left(), (*it)->screen_location.size);
            if(clipper == nullptr ||
                    (((*it)->get_tooltip() != nullptr && (*it)->get_tooltip()->get_geom_manager() != nullptr) || (*it)->name == "tooltip") ||
                    (clipper != nullptr && ei::Application::check_intersection(rect, *clipper))){
                (*it)->draw(surface, pick_surface, clipper);
            }
        }else if(ei::Application::VERBOSE){
            std::cout<<"=====> not managed widget: "<<name<<std::endl;
        }
    }
}

const ei::linked_tag_t& ei::Widget::get_tag() const{
    return tag_id;
}

const ei::Rect& ei::Widget::get_screen_location() const
{
    return screen_location;
}

void ei::Widget::set_screen_location(int *x, int *y, float* width, float* height)
{
    if(x!=nullptr && y!=nullptr)
        screen_location.top_left = Point(*x, *y);
    if(width!=nullptr && height!=nullptr)
        screen_location.size = Size(*width, *height);
}

void ei::Widget::set_children(Widget *child)
{
    children.push_back(child);
}

std::list<ei::Widget *> &ei::Widget::get_children()
{
    return children;
}

ei::widgetclass_name_t ei::Widget::get_name() const
{
    return name;
}

void ei::Widget::set_name(widgetclass_name_t new_name){
    name = new_name;
}

void ei::Widget::print() const
{
    std::cout <<name<<" ==>"<<std::endl<<"\trequested_size["<<requested_size.width()<<", "<<requested_size.height()<<"]\tscreen_location[size["<<screen_location.size.width()<<", "<<screen_location.size.height()<<"]  , topLeft["<<screen_location.top_left.x()<<", "<<screen_location.top_left.y()<<"]]\n\ts_id_generator["<<s_idGenerator<<"]  ,   pick_id["<<pick_id<<"]"<<", content_rect[size["<<content_rect->size.width()<<", "<<content_rect->size.height()<<"]  , topLeft["<<content_rect->top_left.x()<<", "<<content_rect->top_left.y()<<"]] , "<<std::endl<<"\tGeom_manager: "<<geom_manager<<", border_width: "<<border_width<<std::endl<<std::endl;
}

ei::Point ei::Widget::use_anchor(Point top_left, Size size, Size size_surface, anchor_t anchor){
    float abs(0), ord(0);
    switch (anchor) {
    case ei_anc_center:
        abs = top_left.x() + (size.width()/2) - (size_surface.width()/2);
        ord = top_left.y() + (size.height()/2) - (size_surface.height()/2);
        break;
    case ei_anc_northeast:
        abs = top_left.x() + size.width() - (size_surface.width());
        ord = top_left.y();
        break;
    case ei_anc_southeast:
        abs = top_left.x() + size.width() - (size_surface.width());
        ord = top_left.y() + size.height() - size_surface.height();
        break;
    case ei_anc_southwest:
        abs = top_left.x();
        ord = top_left.y() + size.height() - size_surface.height();
        break;
    case ei_anc_north:
        abs = top_left.x() + (size.width()/2) - (size_surface.width()/2);
        ord = top_left.y();
        break;
    case ei_anc_south:
        abs = top_left.x() + (size.width()/2) - (size_surface.width()/2);
        ord = top_left.y() + size.height() - size_surface.height();
        break;
    case ei_anc_east:
        abs = top_left.x() + size.width() - size_surface.width();
        ord = top_left.y() + (size.height()/2) - (size_surface.height()/2);
        break;
    case ei_anc_west:
        abs = top_left.x();
        ord = top_left.y() + (size.height()/2) - (size_surface.height()/2);
        break;
    default:
        return  top_left;
    }
    return Point(static_cast<int>(abs), static_cast<int>(ord));
}

ei::Point ei::Widget::get_top_left() const{
    Point pos = get_screen_location().top_left;
    Point size = get_screen_location().size;
    float abs(0), ord(0);
    switch (anchor) {
    case ei_anc_southwest:
        abs = pos.x();
        ord = pos.y() - size.height();
        break;
    case ei_anc_southeast:
        abs = pos.x() - size.width();
        ord = pos.y() - size.height();
        break;
    case ei_anc_northeast:
        abs = pos.x() - size.width();
        ord = pos.y();
        break;
    case ei_anc_center:
        abs = pos.x() - (size.width()/2);
        ord = pos.y() - (size.height()/2);
        break;
    case ei_anc_north:
        abs = pos.x() - (size.width()/2);
        ord = pos.y();
        break;
    case ei_anc_south:
        abs = pos.x() - (size.width()/2);
        ord = pos.y() - size.height();
        break;
    case ei_anc_west:
        abs = pos.x();
        ord = pos.y() - (size.height()/2);
        break;
    case ei_anc_east:
        abs = pos.x() - size.width();
        ord = pos.y() - (size.height()/2);
        break;
    default:
        abs = pos.x();
        ord = pos.y();
    }
    return Point(static_cast<int>(abs), static_cast<int>(ord));
}

void ei::Widget::set_color(const color_t& color){
    bckground_color = color;
}

const ei::Rect_f& ei::Widget::get_screen_rel_location() const
{
    return screen_rel_location;
}

void ei::Widget::set_screen_rel_location(float *x, float *y, float* width, float* height)
{
    if(x!=nullptr && y!=nullptr)
        if(x!=nullptr && y!=nullptr)
            screen_rel_location.top_left = Point_f(*x, *y);
    if(width!=nullptr && height!=nullptr)
        screen_rel_location.size = Size(*width, *height);
}

const ei::anchor_t& ei::Widget::get_anchor() const{
    return anchor;
}

void ei::Widget::set_anchor(const anchor_t anc){
    anchor = anc;
}


void ei::Widget::set_screen_abs_location(int *x, int *y, float* width, float* height){
    if(x!=nullptr && y!=nullptr)
        if(x!=nullptr && y!=nullptr)
            screen_abs_location.top_left = Point(*x, *y);
    if(width!=nullptr && height!=nullptr)
        screen_abs_location.size = Size(*width, *height);
}
const ei::Rect& ei::Widget::get_screen_abs_location() const{
    return screen_abs_location;
}

ei::GeometryManager* ei::Widget::get_geom_manager()
{
    return geom_manager;
}

void ei::Widget::set_geom_manager(GeometryManager* geom_manager){
    this->geom_manager = geom_manager;
}

int ei::Widget::get_border_width() const
{
    return border_width;
}

const ei::Rect& ei::Widget::get_content_rect() const{
    return *content_rect;
}

void set_requested_size(float* width, float* height){
    assert(width!=nullptr && height!=nullptr);
}

void ei::Widget::swap_borer_color(){
    ei::color_t temp(border_color_top);
    border_color_top = border_color_bottom;
    border_color_bottom = temp;
}

void ei::Widget::add_tag(tag_t tag1, tag_t tag2, tag_t tag3, tag_t tag4, tag_t tag5){
    if(!tag1.empty())
        tag_id.push_back(tag1);
    if(!tag2.empty())
        tag_id.push_back(tag2);
    if(!tag3.empty())
        tag_id.push_back(tag3);
    if(!tag4.empty())
        tag_id.push_back(tag4);
    if(!tag5.empty())
        tag_id.push_back(tag5);
}

void ei::Widget::remove_tag(tag_t t){
    tag_id.remove(t);
}

void ei::Widget::set_tool_tip(const char* tooltip){
    this->tooltip->set_tooltip_text(tooltip);
}

ei::Tooltip* ei::Widget::get_tooltip(){
    return tooltip;
}

ei::Tooltip::Tooltip(Widget *parent): Frame(parent)
{
    Placer* p = new Placer();
    p->configure(this, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    anchor =ei_anc_southwest;
    text_anchor = ei_anc_none;
    geom_manager_copy = p;
    geom_manager->release(this);
    name = "tooltip";
    bckground_color.red = bckground_color.green = bckground_color.blue = 0x0;
    bckground_color.alpha = 255;
    border_width = 0;
}

ei::Tooltip::~Tooltip(){
    delete geom_manager_copy;
}

void ei::Tooltip::set_tooltip_text(const char* text){
    requested_size = ei::Size(0, 0);
    configure(nullptr, nullptr, nullptr, nullptr, &text, &text_font, nullptr, nullptr, nullptr, nullptr, nullptr);
}

void ei::Tooltip::show_tool_tipe(){
    geom_manager = geom_manager_copy;
}

void ei::Tooltip::draw (surface_t surface,
                        surface_t pick_surface,
                        Rect*     clipper)
{
    Rect new_clipper(get_top_left(), screen_location.size);
    Frame::draw(surface, pick_surface, &new_clipper);
}

std::string ei::Widget::get_type() const{
    return "Widget";
}

std::string ei::Tooltip::get_type() const{
    return "Tooltip";
}

void ei::Widget::draw_in_offscreen(surface_t offscreen, Rect* clipper){
    ei_draw_filled_rounded_rect(offscreen, clipper, ei::Rect(get_top_left(), screen_location.size), pick_color);
    std::list<Widget*>::iterator it;
    for(it=children.begin(); it!=children.end(); it++){
        if((*it)->geom_manager!=nullptr){
            ei::Rect rect((*it)->get_top_left(), (*it)->screen_location.size);
            if(clipper == nullptr ||
                    (((*it)->get_tooltip() != nullptr && (*it)->get_tooltip()->get_geom_manager() != nullptr) || (*it)->name == "tooltip") ||
                    (clipper != nullptr && ei::Application::check_intersection(rect, *clipper))){
                (*it)->draw_in_offscreen(offscreen, clipper);
            }
        }
    }
}

ei::color_t ei::Widget::get_border_color_top() const{
    return border_color_top;
}
ei::color_t ei::Widget::get_border_color_bottom() const{
    return border_color_bottom;
}
