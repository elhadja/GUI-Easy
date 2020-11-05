/**
 *  @file ei_eventmanager.h
 *  @brief  Manages event callbacks.
 *
 *  \author
 *  Created by François Bérard on 18.12.11.
 *  Modified by Pierre Bénard and Aurélie Bugeau
 *  Modified by Bah elahdj amadou and Rémi
 *
 */

#ifndef EI_EVENTMANAGER_H
#define EI_EVENTMANAGER_H

#include "ei_event.h"

#include <map>

namespace ei {

/*!
  *\struct info_event_callback
  * \brief contain informations which bind an event to a widget/tag
  *
  * fiedls are the bind parameters \ref bind
  */
typedef   struct name{
    ei_eventtype_t event;
    Widget *widget;
    tag_t tag;
    ei_callback_t callback;
    void* user_param;
}info_event_callback;

/**
 * \brief Class that represents the event manager.
 */
class EventManager
{
public:
    /**
     * @return the singleton instance
     */
    static EventManager& getInstance() {
        static EventManager instance;
        return instance;
    }
private:
    EventManager();
public:
    EventManager(EventManager const&)    = delete;
    void operator=(EventManager const&)  = delete;

    /**
     * \brief	Binds a callback to an event type and a widget or a tag.
     *
     * @param	eventtype	The type of the event.
     * @param	widget		The callback is only called if the event is related to this widget.
     *                      This parameter must be NULL if the "tag" parameter is not NULL.
     * @param	tag		The callback is only called if the event is related to a widget that
     *                  has this tag. A tag can be a widget class name, or the tag "all".
     *      			This parameter must be NULL is the "widget" parameter is not NULL.
     * @param	callback	The callback (i.e. the function to call).
     * @param	user_param	A user parameter that will be passed to the callback when it is called.
     */
    void bind (ei_eventtype_t eventtype,
               Widget*        widget,
               tag_t          tag,
               ei_callback_t  callback,
               void*          user_param);

    /**
     * \brief	Unbinds a callback from an event type and widget or tag.
     *
     * @param	eventtype, widget, tag, callback, user_param
     *			All parameters must have the same value as when
     *          \ref ei::EventManager::bind was called to create the binding.
     */
    void unbind (ei_eventtype_t eventtype,
                 Widget*        widget,
                 tag_t          tag,
                 ei_callback_t  callback,
                 void*          user_param);
    /**
     * @brief check_event_callback  check if an event and a widget are related
     * and then call the callback or return silently
     * @param eventtype the type of the event to check
     * @param widget the widget to check
     * return the number of corresponding callbacks founded
     */
    int check_event_callback(Event *eventtype, Widget* widget);
    /**
     * @brief print print the informations about current widget and their callback \ref list_event_callback
     * just for debug
     */
    void print();

private:
    std::map<int, std::list<info_event_callback>> map_event_callback; ///< contain informations about widget/tag and their callback
    std::list<info_event_callback> to_keep; ///< will be used to delete a calbacks \ref unbind
};

}

#endif // EI_EVENTMANAGER_H
