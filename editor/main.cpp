#include "yaml-cpp/yaml.h"
#include "SaveButton.h"
#include "Map.h"
#include "NameEntry.h"
#include "AmbianceGrid.h"
#include "HordeFrequencySpinButton.h"
#include "AddHordeGrid.h"
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

    NameEntry *nameEntry;
    builder->get_widget_derived("name", nameEntry, map);

    AmbianceGrid *ambianceGrid;
    builder->get_widget_derived("ambiance", ambianceGrid, map);

    HordeFrequencySpinButton *hordeFrequencySpinButton;
    builder->get_widget_derived(
            "time-between-hordes", hordeFrequencySpinButton, map);

    AddHordeGrid *addHordeGrid;
    builder->get_widget_derived("add-horde-grid", addHordeGrid, map);

    auto returnCode = app->run(*mainWindow);
    delete mainWindow;
    return returnCode;
}