/**
 * @file    ei_widget.h
 *
 * @brief   API for widgets management: creation, configuration, hierarchy, redisplay.
 *
 *  Created by François Bérard on 30.12.11.
 *  Modified by Pierre Bénard and Aurélie Bugeau
 *  Modified by Bah elhadj amadou
 */

#ifndef EI_WIDGET_H
#define EI_WIDGET_H

#include "ei_draw.h"

#include <functional>

namespace ei {

struct Event;

/**
 * \brief   A name of a class of widget.
 */
typedef std::string widgetclass_name_t;


class GeometryManager;
class Placer;
class Frame;
class Tooltip;

/**
 * \brief   Abstract class representing a widget
 *          Every widget class specializes this base class by adding its own attributs.
 */
class Widget
{
public:

    /**
     * @brief   Construct a new instance of a widget of some particular class, as a descendant of an existing widget.
     *
     *      The widget is not displayed on screen until it is managed by a geometry manager.
     *
     * @param   class_name  The name of the class of the widget that is to be created.
     * @param   parent      A pointer to the parent widget. Cannot be NULL except for the root widget.
     */
    Widget(const widgetclass_name_t& class_name, Widget* parent);
    /**
     * @brief   Destroys the widget. Removes it from screen if it is managed by a geometry manager.
     *          Destroys all its descendants.
     */
    virtual ~Widget();

    /**
     * \brief   calls for all children of a widget the related method draw
     *
     * @param   surface     Where to draw the widget. The actual location of the widget in the
     *                      surface is stored in its "screen_location" field.
     * @param   pick_surface  Offscreen buffer to draw the widget \ref pick_id
     * @param   clipper     If not NULL, the drawing is restricted within this rectangle
     *                      (expressed in the surface reference frame).
     */
    virtual void draw (surface_t surface, surface_t pick_surface, Rect* clipper);
    /**
     * @brief draw_in_offscreen draw widgets in offscreen
     * @param offscreen the offscreen
     * @param clipper   the clipper
     */
    void draw_in_offscreen(surface_t offscreen, Rect* clipper);

    /**
     * \brief   Method that is called to notify the widget that its geometry has been modified
     *      by its geometry manager.e
     *
     * @param   rect        The new rectangular screen location of the widget
     *                      (i.e., = widget->screen_location).
     */
    virtual void geomnotify (Rect rect);

    /**
     * @brief   print a widget
     * just for debug
     */
    void print() const;
    /**
     * @brief use_anchor apply the anchor to widget's text or image \ref anchor_t
     * @param top_left  widget's position
     * @param size  widget's size
     * @param size_surface the size of the text or the image in the widget
     * @param anchor the anchor to apply \ref anchor_t
     * @return the position of the text or the image related to the anchor
     */
    Point use_anchor(Point top_left, Size size, Size size_surface, anchor_t anchor);
    /**
     * @brief get_top_left determine the topleft of the widget
     * @param pos the position of the widget
     * @param size the size of the widget
     * @return the point at the top left of the widget (not to be confused with the position of the widget)
     */
    Point get_top_left() const;
    /**
     * @brief swap_borer_color swap top and bottom border color
     */
    void swap_borer_color();

    /**
     * @brief set_content_rec set the width or the position of a widget's content rect \ref content_rect
     * to just modify the position, width and height can take null.
     * to just modify the size, x and y can take null
     * @param x abscisse
     * @param y ordonnate
     * @param width the width of the content rect
     * @param height the height of the content rect
     */
    virtual void set_content_rec(int *x, int *y, float* width, float* height) = 0;
    /**
     * @brief pick search the widget who have the parameter id as pick_id
     * @param id the id used for the search
     * @param w will content the adress of the widget if it is found or null
     */
    void pick(uint32_t id, Widget** w);
    /**
     * @brief add_tag add a tag to the list of tag
     * @param tag1, tag2 ..., tagn tags to add
     */
    void add_tag(tag_t tag1="", tag_t tag2="", tag_t tag3="", tag_t tag4="", tag_t tag5="");
    /**
     * @brief remove_tag remove a tag in the list of tag
     * @param t the tag to remove
     */
    void remove_tag(tag_t t);
    /**
     * @brief overflow check if a widget exceeds his parent and modified the clipper
     * if the widget is completly out of his parent, this function actualize the attribut "out" to true)
     * @param clipper the clipper where the widget must be draw
     * @return true if the widget exceeds his parent else return false
     */
    bool overflow(Rect **clipper);
    /**
     * @brief get_type return the classe name of the widget
     * @return  the classe name of the widget
     */
    virtual std::string get_type() const;

    uint32_t getPick_id() const;
    Widget *getParent() const;
    const Size& get_requested_size() const;
    const Rect& get_screen_location() const;
    void set_screen_location(int *x, int *y, float* width, float* height);
    void set_children(Widget *child);
    std::list<Widget*>& get_children();
    widgetclass_name_t get_name() const;
    void set_name(widgetclass_name_t new_name);
    static uint32_t get_s_idGenerator();
    static void set_s_id_generator();
    void set_color(const color_t &color);
    void set_screen_rel_location(float *x, float *y, float* width, float* height);
    const Rect_f &get_screen_rel_location() const;
    const anchor_t& get_anchor() const;
    void set_anchor(const anchor_t anc);
    void set_screen_abs_location(int *x, int *y, float* width, float* height);
    const ei::Rect& get_screen_abs_location() const;
    GeometryManager *get_geom_manager();
    void set_geom_manager(GeometryManager *geom_manager);
    int get_border_width() const;
    const Rect& get_content_rect() const;
    void set_requested_size(float* width, float* height);
    const linked_tag_t& get_tag() const;
    void set_tool_tip(const char *tooltip);
    Tooltip *get_tooltip();
    color_t get_border_color_top() const;
    color_t get_border_color_bottom() const;

protected:

    widgetclass_name_t name; ///< The string name of this class of widget.

    static uint32_t s_idGenerator; ///< Static counter to assure the uniqueness of the generated Ids
    uint32_t     pick_id;    ///< Id of this widget in the picking offscreen.
    color_t   pick_color;    ///< pick_id encoded as a color.

    /* Widget Hierachy Management */
    Widget*  parent;             ///< Pointer to the parent of this widget.
    std::list<Widget*> children; ///< List of this widget's children

    /* Geometry Management */
    GeometryManager* geom_manager; ///< Pointer to the geometry management for this widget.
    ///  If NULL, the widget is not currently managed and thus, is not mapped on the screen.
    Size  requested_size;  ///< Size requested by the widget (big enough for its label, for example), or by the programmer. This can be different than its screen size defined by the placer.
    Rect  screen_location; ///< Position and size of the widget expressed in the root window reference.
    Rect* content_rect;    ///< Where to place children, when this widget is used as a container. By defaults, points to the screen_location.
    color_t bckground_color;      ///<the background color of the widget
    Rect_f screen_rel_location;     ///<informations about relative size and width (like 1.0, 0.0, ...)
    Rect screen_abs_location;     ///<absolute position and size
    anchor_t anchor;              ///<indicated how widget will be fixed at his position \ref anchor_t
    int border_width;               ///< widget's border width
    std::list<tag_t> tag_id;                 ///<the tag of this widget (many widgets can have the same tag)
    color_t border_color_top;           ///< the widget's top border color
    color_t border_color_bottom;        ///< the widget's bottom border color
    bool out;                       ///< a boolean witch is true if the widget is out of his parent
    char* tool_top_text;            ///< tooltip's text
    Tooltip *tooltip;               ///< the tooltip of the widget
};


/**
 * @brief   A function that is called in response to a user event.
 *          Usually passed as a parameter to \ref ei::EventManager::bind.
 *
 * @param   widget      The widget for which the event was generated.
 * @param   event       The event containing all its parameters (type, etc.)
 * @param   user_param  The user parameters that was provided by the caller when registering this callback.
 *
 * @return      A boolean telling if the event was consumed by the callback or not.
 *              If TRUE, the library does not try to call other callbacks for this
 *              event. If FALSE, the library will call the next callback registered
 *              for this event, if any.
 *              Note: The callback may execute many operations and still return
 *              FALSE, or return TRUE without having done anything.
 */
typedef std::function<bool_t(Widget*,Event*,void*)> ei_callback_t;

class Frame : public Widget
{
public:
    /**
     * @brief Frame Construct a new instance of a Frame.
     *
     *      The widget is not displayed on screen until it is managed by a geometry manager.
     * @param parent the parent of the Frame
     */
    Frame(Widget* parent);

    /**
     * @brief ~Frame \ref Widget::~Widget
     */
    virtual ~Frame();

    /**
     * @brief \ref Widget::draw
     */
    virtual void draw (surface_t surface,
                       surface_t pick_surface,
                       Rect*     clipper);

    /**
     * @brief   Configures the attributes of widgets of the class "frame".
     *
     *      Parameters obey the "default" protocol: if a parameter is "NULL" and it has never
     *      been defined before, then a default value should be used (default values are
     *      specified for each parameter). If the parameter is "NULL" but was defined on a
     *      previous call, then its value must not be changed.
     *
     * @param   requested_size  The size requested for this widget. The geometry manager may
     *                  override this size due to other constraints.
     *                  Defaults to the "natural size" of the widget, ie. big enough to
     *                  display the text or the image, or (0, 0) if the widget has no text
     *                  and no image.
     * @param   color       The color of the background of the widget. Defaults to
     *                      \ref ei_default_background_color.
     * @param   border_width    The width in pixel of the border decoration of the widget. The final
     *                          appearance depends on the "relief" parameter. Defaults to 0.
     * @param   relief      Appearance of the border of the widget. Defaults to \ref ei_relief_none.
     * @param   text        The text to display in the widget, or NULL. Only one of the
     *                      parameter "text" and "img" should be used (i.e. non-NULL). Defaults
     *                      to NULL.
     * @param   text_font   The font used to display the text. Defaults to \ref ei_default_font.
     * @param   text_color  The color used to display the text. Defaults to
     *                      \ref ei_font_default_color.
     * @param   text_anchor The anchor of the text, i.e. where it is placed whithin the widget
     *                      when the size of the widget is bigger than the size of the text.
     *                      Defaults to \ref ei_anc_center.
     * @param   img     The image to display in the widget, or NULL. Any surface can be
     *                  used, but usually a surface returned by \ref hw_image_load. Only one
     *                  of the parameter "text" and "img" should be used (i.e. non-NULL).
     *                  Defaults to NULL.
     * @param   img_rect    If not NULL, this rectangle defines a subpart of "img" to use as the
     *                      image displayed in the widget. Defaults to NULL.
     * @param   img_anchor  The anchor of the image, i.e. where it is placed whithin the widget
     *                      when the size of the widget is bigger than the size of the image.
     *                      Defaults to \ref ei_anc_center.
     */
    void configure (Size*           requested_size,
                    const color_t*  color,
                    int*            border_width,
                    relief_t*       relief,
                    const char **text,
                    font_t*         text_font,
                    color_t*        text_color,
                    anchor_t*       text_anchor,
                    surface_t*      img,
                    Rect**          img_rect,
                    anchor_t*       img_anchor);
    /**
     * @brief set_content_rec \ref Widget::set_content_rec
     */
    virtual void set_content_rec(int *x, int *y, float* width, float* height);
    /**
     * @brief set_content_rec \ref Widget::get_type
     */
    virtual std::string get_type() const;
protected:
    relief_t relief;            ///<Appearance of the border of the widget
    const char* text;                 ///<The text to display
    font_t text_font;           ///<The font used to display the text
    color_t text_color;         ///<the color used to display the text
    anchor_t text_anchor;       ///<The anchor of the text, i.e. where it is placed whithin the widget
    surface_t img;              ///<The image to display in the widget
    Rect* img_rect;             ///<If not NULL, this rectangle defines a subpart of "img" to use as the image displayed in the widget.
    anchor_t img_anchor;        ///<The anchor of the image, i.e. where it is placed whithin the widget

    friend class Widget_test;
    friend class Application_test;
};


struct MouseEvent;

class Button : public Widget
{
public:
    /**
     * @brief Button Construct a new instance of a Button.
     *
     *      The widget is not displayed on screen until it is managed by a geometry manager.
     * @param parent the parent of the Frame
     */
    Button(Widget* parent);
    /**
     * @brief ~Button \ref Widget::~Widget
     */
    virtual ~Button();
    /**
     * @brief draw \ref Widget::draw
     */
    virtual void draw (surface_t surface,
                       surface_t pick_surface,
                       Rect*     clipper);

    /**
     * @brief   Configures the attributes of widgets of the class "button".
     *
     * @param   widget, requested_size, color, border_width, relief, text, text_font,
     *          text_color, text_anchor, img, img_rect, img_anchor
     *              See the parameter definition of \ref Frame::configure. The only
     *              difference is that relief defaults to \ref ei_relief_raised
     *              and border_width defaults to \ref k_default_button_border_width.
     * @param   corner_radius   The radius (in pixels) of the rounded corners of the button.
     *                          0 means straight corners. Defaults to k_default_button_corner_radius.
     */
    void configure (Size*            requested_size,
                    const color_t*   color,
                    int*             border_width,
                    int*             corner_radius,
                    relief_t*        relief,
                    const char **    text,
                    font_t*          text_font,
                    color_t*         text_color,
                    anchor_t*        text_anchor,
                    surface_t*       img,
                    Rect**           img_rect,
                    anchor_t*        img_anchor);
    /**
     * @brief set_content_rec \ref Widget::set_content_rect
     */
    virtual void set_content_rec(int *x, int *y, float* width, float* height);
    /**
     * @brief get_type \ref Widget::get_type
     */
    virtual std::string get_type() const;
protected:
    int corner_radius;     ///<The radius (in pixels) of the rounded corners of the button.
    relief_t relief;       ///<Appearance of the border of the widget
    const char* text;      ///<The text to display in the Button
    font_t text_font;      ///<The font used to display the text
    color_t text_color;    ///<the color of the text
    anchor_t text_anchor;  ///<The anchor of the text, i.e. where it is placed whithin the widget
    surface_t img;         ///<The anchor of the img, i.e. where it is placed whithin the widget
    Rect* img_rect;        ///<this rectangle defines a subpart of "img" to use as the image displayed in the widget.
    anchor_t img_anchor;   ///<The anchor of the image, i.e. where it is placed whithin the widget


    friend class Widget_test;
};

class Toplevel : public Widget
{
public:
    /**
     * @brief Toplevel Construct a new instance of a Toplevel.
     *
     *      The widget is not displayed on screen until it is managed by a geometry manager.
     * @param parent the parent of the Frame
     */
    Toplevel(Widget* parent);
    /**
     * @brief ~Toplevel \ref Widget::~Widget
     */
    virtual ~Toplevel();
    /**
     * @brief draw \ref Widget::draw
     */
    virtual void draw (surface_t surface,
                       surface_t pick_surface,
                       Rect*     clipper);

    /**
     * @brief   Configures the attributes of widgets of the class "toplevel".
     *
     * @param   widget      The widget to configure.
     * @param   requested_size  The content size requested for this widget, this does not include
     *              the decorations (border, title bar). The geometry manager may
     *              override this size due to other constraints.
     *              Defaults to (320x240).
     * @param   color       The color of the background of the content of the widget. Defaults     *                      to \ref ei_default_background_color.
     * @param   border_width    The width in pixel of the border of the widget. Defaults to 4.
     * @param   title       The string title diplayed in the title bar. Defaults to "Toplevel".
     * @param   closable    If true, the toplevel is closable by the user, the toplevel must
     *                      show a close button in its title bar. Defaults to \ref EI_TRUE.
     * @param   resizable   Defines if the widget can be resized horizontally and/or vertically
     *                      by the user. Defaults to \ref ei_axis_both.
     * @param   min_size    For resizable widgets, defines the minimum size. Defaults to (160, 120).
     */
    void configure (Size*           requested_size,
                    color_t*        color,
                    int*            border_width,
                    const char**    title,
                    bool_t*         closable,
                    axis_set_t*     resizable,
                    Size*           min_size);
    /**
     * @brief set_content_rec \ref Widget::content_rect
     */
    virtual void set_content_rec(int *x, int *y, float* width, float* height);
    /**
     * @brief get_type \ref Widget::get_type
     * @return
     */
    virtual std::string get_type() const;

    ei::axis_set_t get_resizable();
    const Size &get_minimum_size() const;
protected:
    const char* title;  ///<The string title diplayed in the title bar. Defaults to "Toplevel".
    void* title_font;
    bool is_closable;   ///<If true, the toplevel is closable by the user, the toplevel must show a close button in its title bar. Defaults to \ref EI_TRUE.
    axis_set_t resizable;   ///<Defines if the widget can be resized horizontally and/or vertically
    Size min_size;          ///<The mininmum size of the TopLevel
    Button* but_close;      ///<The button at the top right of the TopLevel used to close the topLevel
    Button* but_resize;     ///<The button at the bottom right of the TopLevel used to resize the window
    Placer* btn_resize_placer;              ///< the placer for the button resize
    Placer* btn_close_placer;               ///< the placer for the button close
    const static int title_bar_height;      ///<the height of the menu bar
    const static int default_width;        ///< the default width
    const static int default_height;       ///<the default height

    friend class Widget_test;
};

class Button_radio;

class Tooltip : public Frame{
public:
    /**
     * @brief Tooltip Construct a new instance of a Tooltip.
     *
     *      The widget is not displayed on screen until it is managed by a geometry manager.
     * @param parent the parent of the Frame
     */
    Tooltip(Widget *parent);
    /**
     * @brief ~Tooltip \ref Widget::~Widget
     */
    ~Tooltip();
    /**
     * @brief set_tooltip_text set the text of the tooltip
     * @param text the text
     */
    void set_tooltip_text(const char *text);
    /**
     * @brief show_tool_tipe give a geometry manager to the tooltip for display it
     */
    void show_tool_tipe();
    /**
     * @brief draw \ref Frame::draw
     */
    virtual void draw (surface_t surface,
                       surface_t pick_surface,
                       Rect*     clipper);
    /**
     * @brief get_type \ref Widget::get_type
     * @return
     */
    virtual std::string get_type() const;
private:
    GeometryManager *geom_manager_copy;
};
}

#endif
