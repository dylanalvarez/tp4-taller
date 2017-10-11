#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/builder.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/spinner.h>
#include <gtkmm/box.h>
#include <iostream>
#include "ConnectingController.h"

int main(int argc, char *argv[]) {
    try {
        Glib::RefPtr<Gtk::Application> app =
                Gtk::Application::create(argc, argv);

        Gtk::Window *window = nullptr;
        Gtk::Builder::create_from_file("assets/glade/main.glade")->
                get_widget("window", window);

        std::unique_ptr<Controller> currentController;
        currentController.reset(
                new ConnectingController(window, currentController));

        auto returnCode = app->run(*window);
        delete window;
        return returnCode;
    } catch (Glib::Exception &e) {
        std::cout << e.what() << std::endl;
    }
}
