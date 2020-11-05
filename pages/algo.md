Description de quelques algorithmes
===================================


#   Algorithmes de dessin des widgets

Pour le dessin des widgets, voici les pricipales méthodes utilisées:
*   ei::Widget::draw :  parcourir tous les fils d'un widget et appeler la méthode draw correspondante
*   ei::Widget::draw_in_offscreen   : méthode qui dessine dans l'offcreen tous les fils d'un widget
*   la méthode draw propre à chaque widget: par exemple ei::Toplevel::draw
*   la fonction éxécutée par le thread lors du dessin en parallèle (voir ei::fun_thread dans ei_application.h)

##  Dessin en parallèle dans la surface et dans l'offscreen

Le dessin en parallèle des widgets dans l'offscreen et dans la surface est éffectué à partir du widget root à chaque fois qu'on doit actualiser l'écran. La parallélisation est effectuée avec des threads.

** il est important de signaler que la méthode draw d'un widget ne dessine plus dans l'offscreen mais seulement dans la surface réelle **

Pour plus d'informations voir ei::Application::run.

    algorithme pour le dessin en parallèle:
    {   
        1.  creer un thread et lui passer la fonction fun_thread    // dessine dans l'offscreen en appelant ei::Widget::draw_in_offscreen
        2.  dessiner dans la surface à partir du widget root
        3.  attendre la fin de l'éxécution du thread fils
    }
    

##  Principales étapes dans le dessin de n'importe quel widget

Description de la procédure suivante:
*   ligne 1-4:  pour gérer le débordement (partiel ou total) voir ei::Widget::overflow
*   ligne 5  :  partie propre à chaque widget
*   ligne 6  : ei::Widget::draw


attention ! cette méthode (la procédure ci dessous) n'éxiste pas, elle permet juste de voir le contenu en commun des méthodes de dessin des widgets.


    procedure draw_any_widget(...)
    {
        1.  si le widget déborde partiellement son père
        2.      adapter le clipper
        3.  Si le widget déborde totalement son père
        4.      fin procedure
        5.  dessiner le widget
        6.  dessiner tous ses fils
    }


------------------------------------------------------------------------------


#   Algorithmes sur les traitants internes (ei_internals_calbacks.h)

Pour voir la description de chacune des fonctions de cette section, clickez sur le lien ci dessu.

## 1.   Algorithme liés au tooltip:

Il y'a deux calbacks qui traitent les tooltips:
1.  show_tooltip:   Show tooltip est appelé uniquement lorqu'un widget a le tag *ei_tooltip* et que la souris est sur le widget
2.  hide_tooltip    Peut être appelé dans deux cas:
    *       par la méthode *ei::Application::run()* lorque le temps est écoulé
    *       par le déclenchement d'un événement (lorsque la souris n'est plus sur le widget)

Il est important de signaler que *hide_tooltip* est enregistrer par *show_tool_tip* lorsque ce dernier est executer (voir ligne4 de la description ci-dessous).


        procedure show_tooltip(...)
        {
            1.  recupérer le tooltip
            2.  Modifier le *screen_location* du tooltip selon la position de son père  // toujour en haut à gauche
            3.  Donner à ei::Application des informations sur le tooltip (temps de création, l'adresse du tooltip)  
            4.  Faire le binding pour hide_tooltip
            5.  Invalider le tooltip et son père (dans un même clipper)
        }

        procedure hide_tooltip(...)
        {
            1.  Si le tooltip a un geom_manager, le rétirer
            2.  Informer à ei::Application qu'il n'y a plus de tooltip
            3.  Delier hide_tooltip // avec unbind
            4.  calculer le clipper
        }
        
## 2.   Déplacement d'un widget:

Il y'a 3 calbacks qui traitent le déplacement d'un widget:
1.  move_widget:   lors d'un click sur le widget
2.  move_widget_bis:    lorsque le user déplace la souris en maintenant le click
3.  stop_move_widget:   lorsque le user lâche le click

Il est important de signaler que *move_widget_bis et stop_move_widget* sont enregistrées par *move_widget* lorsque cette dernière est éxecutée.

    procedure move_widget(...)
    {
        1.  S'il y'a un tootip actif pour le widget, le désactiver  // cela permettra de réduire la taille du clipper lors du déplacement
        2.  Délier (avec unbind) le calback ei_show_tooltip         // Aucun tooltip ne doit apparaitre lors du déplacement
        3.  Garder les informations sur le click de la souris       // permettra de donner une position précise au widget
        4.  Si le widget est une toplevel && si le click n'est pas sur la bare de menu
        5.      fin procedure
        6.  Faire le binding pour le calback move_widget_bis
        7.  Faire le binding pour le calback stop_move_widget
    }

    procedure move_widget_bis(...)
    {
        1.  Garder une copie du screen_location du widget       // informations géometriques sur l'ecran
        2.  Garger une copie du screen_abs_location du widget   // inforamtions géometriques absolues
        3.  Calculer la nouvelle position du widget
        4.  Actualiser la position du widget ainsi que tous ses fils        // méthode ei::Geometrymanager::run
        5.  Si le widget déborde son père
        6.      restaurer l'ancienne position (voir ligne 2)
        7.      actualiser la géometrie du widget ainsi que tous ses fils   // méthode ei::Geometrymanager::run
        8.      fin procedure
        9.  Calculer le clipper (nouvelle position du rect + ancienne position du rect (ligne1))
        10. Invalider le clipper
        11. Garder en mémoire les coordonnées de souris         // permettra de donner une position précise lors du prochain déplacement
    }

    procedure stop_move_widget(...)
    {
        1.  Faire le binding pour le calback show_tooltip // qui était désactivé tout le long du déplacement du wiget
        2.  Délier (unbind) le calback move_widget_bis
        3.  Délier (unbind) le calback stop_move_widget
    }

## 3.  Changer la taille de la fênetre

Il y'a 3 calbacks qui traitent le changement de la taille d'une toplevel:
1.  set_window_size:   lors d'un click sur le button resize
2.  move_mouse_resize:    lorsque le user déplace la souris en maintenant le click
3.  stop_resize:   lorsque le user lâche le click   


    procedure set_window_size(...)
    {
        1.  Faire le binding pour le calback move_mouse_resize
        2.  Faire le binding pour le calback stop_resize
    }

    procedure move_mouse_resize(...)
    {
        1.  soit width et height deux variables
        2.  calculer la nouvelle taille (mettre le resultat dans width et dans height)     // position courante de la souris - le point en haut à gauche de la toplevel
        3.  Si Toplevel à déjà atteint la taille minimale
        4.      width et height prennent pour valeur l'ancienne taille de la toplevel
        5.  Actualiser la taille en absolue de la toplevel (en utilisant width et height)
        6.  calculer la nouvelle géometrie pour la toplevel ainsi que tous ses fils
        7.  calculer le clipper
        8.  invalider la toplevle
    }

    procedure stop_resize(...)
    {
        1.  Délier (unbind) le calback move_mouse_resize
        2.  Délier (unbind) le calback stop_resize
    }


##  4.  button_pressed : 

        procedure button_pressed(...)
        {
            1.   permuter les couleurs des bordures
            2.   invalider le bouton
        }

##  5.  close_top_level:

        procedure closeTopLevel(...)
        {
            1.   retirer le geom_manager de la toplevel
            2.   invalider la Toplevel
        }
        
## 6.   select_button_radio:

        procedure select_button_radio(...)
        {
            1.   Pour tous les boutons radio de ce groupe:
            2.       si c'est le bouton radio sur lequel l'utilisateur a clické:
            3.          si le bouton radio était selectionné, le déselectionner
            4.           sinon le selectionner
            5.       sinon si le bouton radio est selectionné, le deselectionner
            6.   invalider le bouton radio
        }

## 7.   select_check_box:

        procedure select_check_box(...)
        {
            1.  Si le check_box est selectionné, le déselectionner
            2.  sinon, le selectionner
            3.  invalider le check_box
        }

## 8.   select_entry:

        procedure select_entry(...)
        {
            1.  s'il y a un entry qui a le focus && l'utilisateur a clické sur un entry different de celui qui a le focus
            2.      invalider celui qui avait le focus // cela permettra de le redessiner sans focus
            3.  Donner le focus à l'entry sur lequel il y'a eu l'événement
            4.  Invalider celui qui à le focus  // cela permettra de le redessiner avec le focus
        }

## 9.   check_to_desable:

        proceduce check_to_desable(...)
        {
            1.  S'il y'a un entry qui a le focus && si le user a clické sur un autre widget
            2.      l'entry perd le focus
            3.  invalider l'entry       // pour le redessiner sans le curseur
        }    

## 10.   Key_event_down:

Dans cette procedure, on utilise deux fois la même condition (ligne1 et ligne3) parceque l'intruction à la ligne4 sera éxécutée à la ligne2 peut importe le type d'action. C'est pourquoi il faut le faire une seule fois à la fin.

        procedure key_event_down(...)
        {
            1.  S'il ya un entry qui a le focus
            2.      éxécuter l'action correspondante selon la touche appuyée (supprimer un caratère, déplacer le curseur ...)
            3.  S'il ya un entry qui a le focus
            4.  Invalider l'entry
        }