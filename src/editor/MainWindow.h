#ifndef TOWERDEFENSE_MAINWINDOW_H
#define TOWERDEFENSE_MAINWINDOW_H

#include <gtkmm/window.h>
#include "Builder.h"

class MainWindow : public Gtk::Window {
public:
    MainWindow(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> &builder);

    void init();
};


#endif //TOWERDEFENSE_MAINWINDOW_H
