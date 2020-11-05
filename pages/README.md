Readme
======

## What is this library ?
it is a software library facilitating the programming of graphical user interfaces (GUI). The library will allow a user to easily create and display a graphical interface (creating windows, buttons, image display, text, resizing and moving the window).

## Builds the application
The library uses threads. For compilation add this flag: *pthread*

    set (CMAKE_CXX_FLAGS "-pthread")

## Execution modes

these modes of execution are useful only to the developer of the library and not to the user

*   VERBOSE mode    (ref ei::Application::VERBOSE)
*   DEBUG mode      (ref ei::Application::DEBUG)

## Main features
###   Drawing widgets (Toplevel, frame, button, radio button, check_box, entry, entry_pwd, ...)
###   internals calbacks
*   move a widget
*   click on a widget
*   resize a toplevel
*   tooltips
*   management of multitags 
*   etc

##  Known bugs
*   If a widget contains an overflowing text and this widget overflows its father, the screen refresh will not be correct
*   If two widgets each have a tooltip and if these two widget intersects, the passage of a widget to another generates a SIGSEGV. However, this error is not deterministic, sometimes it happens and sometimes it does not happen.

## Contanct us for suggestions:

    elhadj-amadou.bah@etu.u-bordeaux.fr