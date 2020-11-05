/**
 *  @file ei_application.h
 *  @brief  Manages the main steps of a graphical application: initialization, main window,
 *    main loop, quitting, resource freeing.
 *
 *  \author
 *  Created by François Bérard on 30.12.11.
 *  Modified by Pierre Bénard and Aurélie Bugeau
 *  Modified by Bah elhadj amadou and Remi
 *
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include "ei_types.h"
#include "ei_event.h"
#include "ei_widget.h"

#include <allegro5/allegro_primitives.h>
#include <list>

namespace ei {

/**
  *\struct info_tooltip is used to keep informations about a tooltip
  */
typedef struct info_tooltip{
    ei::Widget* tooltip;    ///<the tooltip
    double timer;           ///<the start time for the tooltip
    ei::Point point;
}info_tooltip_t;

/**
  *\struct info_thread_s is used as argument for the trhead function (ref \fun_thread)
  */
typedef struct info_thread_s{
    surface_t pick_surface;     ///<the offscreen
    ei::Rect *clipper;          ///<the clipper
} info_thread_t;

/**
 * @brief fun_thread draw widgets in the offscreen in parallel with the main thread
 * @param arg the offscreen and the clipper (\ref info_thread
 * @return
 */
void* fun_thread(void *arg);


class Application
{
public:
    /**
     * \brief Creates an application.
     *    <ul>
     *      <li> initializes the hardware (calls \ref hw_init), </li>
     *      <li> creates the root window, </li>
     *      <li> creates the root widget to access the root window. </li>
     *    </ul>
     *
     * @param main_window_size  the size of the root window of the application.
     */
    Application(Size* main_window_size);

    /**
     * \brief Releases all the resources of the application, and releases the hardware
     *    (eventually calls \ref hw_quit).
     */
    ~Application();

    /**
     * \brief Returns a pointer to the application's instance. If no instance has been allocated, NULL is returned.
     * @return the instance
     */
    static Application* getInstance() {
        return instance;
    }

    /**
     * \brief Runs the application: enters the main event loop. Exits when
     *    \ref app_quit_request is called.
     */
    void run();

    /**
     * \brief Adds a rectangle to the list of rectangles that must be updated on screen. The real
     *    update on the screen will be done at the right moment in the main loop.
     *
     * @param rect    The rectangle to add, expressed in the root window coordinates.
     *        A copy is made, so it is safe to release the rectangle on return.
     */
    void invalidate_rect(const Rect &rect);

    /**
     * \brief Tells the application to quite. Is usually called by an event handler (for example
     *    when pressing the "Escape" key).
     */
    void quit_request();

    /**
     * \brief Returns the "root widget" of the application: a "frame" widget that encapsulate the
     *    root window.
     *
     * @return      The root widget.
     */
    Frame* root_widget();

    /**
     * \brief Returns the surface of the root window. Used to create surfaces with similar r, g, b
     *    channels.
     *
     * @return      The surface of the root window.
     */
    surface_t root_surface();

    /**
     * @brief   Returns the widget that is at a given location on screen.
     *
     * @param   where       The location on screen, expressed in the root window coordinates.
     *
     * @return      The top-most widget at this location, or NULL if there is no widget
     *              at this location (except for the root widget).
     */
    Widget* widget_pick (const Point& where);
    /**
     * @brief check_intersection check if there is intersection between two rectangles
     * @param rect_widget the first rectangle (usually the rect of a widget)
     * @param clipper   the second rectangle (usually the clipper used to actualize screen)
     * @return true if there is intersection or false
     */
    static bool check_intersection(const Rect& rect_widget, const Rect& clipper);
    /**
     * @brief fusion merges two rectangles
     * @param rect1 the first rectangle
     * @param rect2 the second rectangle
     * @return the new rectangle
     */
    static ei::Rect fusion(const ei::Rect &rect1, const ei::Rect &rect2);
    Application(Application const&)     = delete; // prevents  this  method  to be used
    void operator=(Application const&)  = delete; // prevents  this  method  to be used
    /**
     * @brief get_start_time return the last time when the application has drew in the screen
     * @return the start time
     */
    static double get_start_time();
    /**
     * @brief set_start_time set start_time (\ref start_time)
     * @param new_time  the new time
     */
    static void set_start_time(double new_time);
    /**
     * @brief get_default_font return the default
     * @return the default font
     */
    static font_t get_default_font();
    /**
     * @brief set_info_tooltip set inforamtions about the current tooltip
     * @param widget    the tooltip
     * @param timer     the time when the tooltip is showed
     * @param point     the point
     */
    static void set_info_tooltip(Widget* widget,double timer, ei::Point point);
    /**
     * @brief get_info_tooltip return informations about the current tooltip
     * @return info_tooltip
     */
    static info_tooltip& get_info_tooltip();

    static const bool VERBOSE;  ///< to see message about what the application is doing
    static const bool DEBUG;    ///< just for debug (like printing a message)
    static const color_t DEBUG_COLOR_FRAME;     ///< A debug color for a frame
    static const color_t DEBUG_COLOR_BUTTON;    ///< A debug color for a button
    static const color_t DEBUG_COLOR_TOPLEVEL;  ///< A debug color for a toplevel
    static const color_t DEBUG_COLOR_CHECK;     ///< A debug color for a check_box
protected:
    /**
     * @brief max calculates the maximum between two numbers
     * @param val1  the first number
     * @param val2  the second number
     * @return  the max numer
     */
    static float max(float val1, float val2);
    /**
     * @brief min   calculates the minimum between two numbers
     * @param val1  the first number
     * @param val2  the second number
     * @return      the min number
     */
    static float min(float val1, float val2);

    static Application *instance;
    Frame* root_wid;                            ///< The root widget
    surface_t root_surf;                        ///< The root surface \ref hw_create_window
    std::list<Rect> invalidate_rect_list;       ///<a list of all Rectangles to actualize
    bool running;               ///< true if the application is runnig and false at the end \ref quit_request
    surface_t offscreen;        ///< the surface used to pick widget
    static double start_time;   ///< the last time when the application has drew in the screen
    Widget* picked_widget;      ///< will containt the adress of the returned by \ref widget_pick
    static const double refresh_time;        ///< refresh time of the application
    static font_t default_font;
    static info_tooltip_t info_tool_type;       ///< informations about the current tooltip

    friend class Application_test;
    friend class Placer_test;
};

}

#endif

