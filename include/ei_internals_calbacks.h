/**
  *\file ei_internals_calbacks.h
  *\brief contains internals calbacks statements
  * \author Bah elhadj amadou, Remi
  */

#ifndef EI_INTERNALS_CALBACK_H
#define EI_INTERNALS_CALBACK_H

#include "ei_event.h"


/**
  *@struct infos_t
  *\brief contain informations
  *
  * this structure is used to allow inside callback to have more informations.
  */
typedef struct info{
    ei::Widget* widget;
    int x;   ///< the position in x for the click
    int y;   ///< the position in y for the click
} infos_t;

/**
 * @brief show_tool_tip show a tooltip when the mouse is inside the widget
 * @param widget    the widget where the mouse is
 * @param event     the event (a mouse event)
 * @param user_param    the user parameter
 * @return  true if success
 */
ei::bool_t show_tool_tip(ei::Widget* widget, ei::Event* event, void* user_param);
/**
 * @brief hide_tool_tip hide a tooltip
 * @param widget  any widget or nullptr
 * @param event the event
 * @param user_param the user parameter
 * @return true if success
 */
ei::bool_t hide_tool_tip(ei::Widget* widget, ei::Event* event, void* user_param);
/**
 * @brief button_pressed is called when some button is pressed or released
 * @param widget    the button
 * @param event     the event
 * @param user_param    the user parameter
 * @return true if success
 */
ei::bool_t button_pressed (ei::Widget* widget, ei::Event* event, void* user_param);
/**
 * @brief move_mouse_resize actualize the size of the TopLevel, each time it is resized.
 * If the TopLevel get the minimum size, it won't be resized
 * @param widget    the widget a the position of the mouse (it is not used in this call_back)
 * @param event     the event
 * @param user_param    the user parameter
 * @return true if success
 */
ei::bool_t move_mouse_resize(ei::Widget* widget, ei::Event* event, void* user_param);
/**
 * @brief stop_resize stop the resizing of the TopLevel by using unbind
 * @param widget    the widget at the position of the mouse
 * @param event     the event
 * @param user_param    the user parameter
 * @return true if sucess
 */
ei::bool_t stop_resize(ei::Widget* widget, ei::Event* event, void* user_param);
/**
 * @brief move_widget_bis is called each time the user move the mouse when he click in the widget
 * @param widget the widget at the position of the mouse
 * @param event the event (ei_ev_mouse_move)
 * @param user_param    the user parameter
 * @return true if success
 */
ei::bool_t move_widget_bis(ei::Widget* widget, ei::Event* event, void* user_param);
/**
 * @brief stop_move_widget stop to move the widget by disable (using \ref unbind) it self and \ref move_mouse_resize
 * @param widget    the widget at the position of the mouse
 * @param event     the event (ei_ev_mouse_button_up)
 * @param user_param    the user parameter
 * @return true if success
 */
ei::bool_t stop_move_widget(ei::Widget* widget, ei::Event* event, void* user_param);
/**
 * @brief move_widget allow to move the widget by using \ref bind
 * if the widget is a Toplevel (\ref ei_widget.h), the click must be in the menu bar
 * @param widget    the widget at the position of the mouse
 * @param event     the event (ei_ev_mouse_click_down)
 * @param user_param    the user parameter
 * @return true if success
 */
ei::bool_t move_widget(ei::Widget* widget, ei::Event* event, void* user_param);

/**
 * @brief set_window_size allow to resize the window by using \ref bind between the TopLevel and
 * events: ei_mouse_move and ei_mouse_buttonup
 * for other parameters \ref set_window_pos
*/
ei::bool_t set_window_size(ei::Widget* widget, ei::Event* event, void* user_param);

/**
 * @brief closeTopLevel is called when the user click on the close button
 * @param widget the close button
 * @param event the event (click down)
 * @param user_param  user parameter
 * @return true if success
 */
ei::bool_t closeTopLevel(ei::Widget* widget, ei::Event* event, void* user_param);
/**
 * @brief select_button_radio select a button radio and desable the others wictch is in the same group
 * @param widget    the button_radio
 * @param event     the event (ei_ev_mouse_buttun_down)
 * @param user_param    the user parameter
 * @return return true if success
 */
ei::bool_t select_button_radio(ei::Widget* widget, ei::Event* event, void* user_param);
/**
 * @brief select_check_box select a check_box
 * @param widget the check box
 * @param event the event (ei_ev_mouse_button_down)
 * @param user_param the user parameter
 * @return true if success
 */
ei::bool_t select_check_box(ei::Widget* widget, ei::Event* event, void* user_param);
/**
 * @brief select_entry select an entry when the user click in the entry
 * @param widget the entry
 * @param event the event (ei_ev_mouse_button_down)
 * @param user_param the user parameters
 * @return return true if success
 */
ei::bool_t select_entry(ei::Widget* widget, ei::Event* event, void* user_param);
/**
 * @brief key_event_down is called when the user click in the keybord
 * if it's a keychar and if an entry has the focus, this char will be put in the entry
 * if it's a left/right key, if an entry has the focus, the position of the cursor will changed
 * @param widget   any widget
 * @param event    the event (ei_ev_keydown)
 * @param user_param the user parameters
 * @return true if success
 */
ei::bool_t key_event_down(ei::Widget* widget, ei::Event* event, void* user_param);
/**
 * @brief check_to_desable if there is an entry, the function checks whether the entry should keep the focus or whether it should lose the focus
 * @param widget any widget
 * @param event the event (ei_ev_mouse_button_down)
 * @param user_param    the user parameters
 * @return true if success
 */
ei::bool_t check_to_desable(ei::Widget* widget, ei::Event* event, void* user_param);

#endif // EI_INTERNALS_CALBACK_H
