#include "MainWindow.h"

MainWindow::MainWindow(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> &builder)
        : Gtk::Window(obj) {
    this->signal_show().connect(sigc::mem_fun(this, &MainWindow::maximize));
}

void MainWindow::init() {}
