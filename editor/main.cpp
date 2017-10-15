#include "yaml-cpp/yaml.h"
#include "SaveButton.h"
#include "Map.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>

int main(int argc, char **argv) {
    Glib::RefPtr<Gtk::Application> app =
            Gtk::Application::create(argc, argv);
    auto builder = Gtk::Builder::create_from_file("assets/glade/editor.glade");
    Map map;

    Gtk::Window *mainWindow;
    builder->get_widget("main-window", mainWindow);

    SaveButton *saveButton;
    builder->get_widget_derived("save", saveButton, map);

    auto returnCode = app->run(*mainWindow);
    delete mainWindow;
    return returnCode;
}
