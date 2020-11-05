/**
  *\file ei_eventmanager.cpp
  * \brief contains definitions of class EventManager \ref ei_eventmanager.h
  * \author Bah elhadj amadou and Remi
  */

#include "ei_eventmanager.h"
#include "ei_application.h"

#include <iostream>
#include <assert.h>
#include <map>

ei::EventManager::EventManager(){}

void ei::EventManager::bind (ei_eventtype_t eventtype,
                             Widget*        widget,
                             tag_t          tag,
                             ei_callback_t  callback,
                             void*          user_param)
{
    if(widget != nullptr && tag.empty()==false){
        std::cerr<<"error: you must use only on parameter between widget and tag"<<std::endl;
        return;
    }
    assert(widget != nullptr || tag.empty()==false);
    info_event_callback info = {eventtype, widget, tag, callback, user_param};
    map_event_callback[eventtype].push_back(info);
}

void ei::EventManager::unbind (ei_eventtype_t eventtype,
                               Widget*        widget,
                               tag_t          tag,
                               ei_callback_t  callback,
                               void*          user_param)
{
    if(widget != nullptr && tag.empty()==false){
        std::cerr<<"error: you must use only on parameter between widget and tag"<<std::endl;
        return;
    }
    assert(widget != nullptr || tag.empty()==false);
    int i=0;
    std::list<info_event_callback>::iterator it;
    for(it=map_event_callback[eventtype].begin(); it!=map_event_callback[eventtype].end(); it++, i++){
        if(widget != nullptr){
            if((*it).widget != widget || (*it).tag != tag || (*it).user_param != user_param){
                to_keep.push_back((*it));
            }
        }else if(it->tag != tag){
            to_keep.push_back((*it));
        }
    }
    map_event_callback[eventtype].clear();
    for (it = to_keep.begin(); it!=to_keep.end(); it++) {
        map_event_callback[eventtype].push_back(*it);
    }
    to_keep.clear();

}

int ei::EventManager::check_event_callback(Event* event, Widget* widget){
    int found(0);   // counter for the number of callbacks founded
    try {
        std::list<info_event_callback>::iterator it;
        for(it=map_event_callback[event->type].begin(); it!=map_event_callback[event->type].end(); it++){
            if(it._M_node == nullptr || it._M_node->_M_next == nullptr)
                return false;
            if((*it).widget != nullptr){
                if((*it).widget->getPick_id() == widget->getPick_id()){
                    if(ei::Application::VERBOSE && event->type != ei_ev_mouse_move)
                        std::cout<<"\n\n=====> [matched binding] Event: "<<(*it).event<<", pick_id: "<<(*it).widget->getPick_id()<<std::endl;
                    (*it).callback(widget, event, (*it).user_param);
                    found += 1;
                }
            }else {
                if((*it).tag == "all" || (*it).tag == widget->get_name()){
                    if(ei::Application::VERBOSE && event->type != ei_ev_mouse_move)
                        std::cout<<"\n\n=====> [matched binding] Event: "<<(*it).event<<", tag_id: ,"<<(*it).tag<<std::endl;
                    (*it).callback(widget, event, (*it).user_param);
                    found += 1;
                }else{
                    linked_tag_t t = widget->get_tag();
                    linked_tag_t::iterator i;
                    for(i = t.begin(); i!=t.end(); i++){
                        if((*(i) == (*it).tag)){
                            if(ei::Application::VERBOSE && event->type != ei_ev_mouse_move)
                                std::cout<<"\n\n=====> [matched binding] Event: "<<(*it).event<<", tag_id: ,"<<(*it).tag<<std::endl;
                            (*it).callback(widget, event, (*it).user_param);
                            found += 1;
                        }
                    }
                }
            }

        }
    }
    catch (std::exception const& e) {
        std::cerr<<"exception catched: "<<e.what()<<std::endl;
    }
    return found;
}

void ei::EventManager::print()
{
    std::cout<<"number binding: "<<map_event_callback.size()<<std::endl;
    std::map<int, std::list<info_event_callback>>::iterator map_it;
    std::list<info_event_callback>::iterator it;
    for(unsigned long i=0; i<map_event_callback.size(); i++){
        for(it = map_event_callback[i].begin(); it != map_event_callback[i].end(); it++){
            std::cout<<"Event: "<<(*it).event<<", tag_id: "<<(*it).tag<<std::endl;
        }
    }
    std::cout<<std::endl;
}
