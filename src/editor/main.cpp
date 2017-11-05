#include "SaveButton.h"
#include "AmbianceGrid.h"
#include "AddHordeGrid.h"
#include "ChooseSizeGrid.h"
#include "LoadFileGrid.h"
#include <gtkmm/window.h>

int main(int argc, char **argv) {
    Glib::RefPtr<Gtk::Application> app =
            Gtk::Application::create(argc, argv);
    Glib::RefPtr<Gtk::Builder> gtkBuilder = Gtk::Builder::create_from_file(
            "assets/glade/editor.glade");
    Builder builder(gtkBuilder);
    Map map;

    Gtk::Window *mainWindow;
    builder.get_widget("main-window", mainWindow);

    SaveButton *saveButton;
    builder.get_widget_derived("save", saveButton, map);

    ChooseSizeGrid *chooseSizeGrid;
    builder.get_widget_derived("choose-size-grid", chooseSizeGrid, map,
                               saveButton);

    AmbianceGrid *ambianceGrid;
    builder.get_widget_derived("ambiance", ambianceGrid, map);

    AddHordeGrid *addHordeGrid;
    builder.get_widget_derived("add-horde-grid", addHordeGrid, map);

    LoadFileGrid *loadFileGrid;
    builder.get_widget_derived("load-file-grid", loadFileGrid, map, saveButton,
                               ambianceGrid, addHordeGrid);

    auto returnCode = app->run(*mainWindow);
    delete mainWindow;
    return returnCode;
}