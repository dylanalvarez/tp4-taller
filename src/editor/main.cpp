#include "SaveButton.h"
#include "AmbianceGrid.h"
#include "AddHordeGrid.h"
#include "ChooseSizeGrid.h"
#include "FileChooser.h"
#include "MainWindow.h"

int main(int argc, char **argv) {
    Glib::RefPtr<Gtk::Application> app =
            Gtk::Application::create(argc, argv);
    Glib::RefPtr<Gtk::Builder> gtkBuilder = Gtk::Builder::create_from_file(
            "../Resources/assets/glade/editor.glade");
    Builder builder(gtkBuilder);
    Map map;

    MainWindow *mainWindow;
    builder.get_widget_derived("main-window", mainWindow);

    SaveButton *saveButton;
    builder.get_widget_derived("save", saveButton, map, mainWindow);

    AmbianceGrid *ambianceGrid;
    builder.get_widget_derived("ambiance", ambianceGrid, map);

    AddHordeGrid *addHordeGrid;
    builder.get_widget_derived("add-horde-grid", addHordeGrid, map);

    NameEntry *nameEntry;
    builder.get_widget_derived("name", nameEntry, map);

    ChooseSizeGrid *chooseSizeGrid;
    builder.get_widget_derived("choose-size-grid", chooseSizeGrid, map,
                               saveButton, ambianceGrid, addHordeGrid,
                               nameEntry);

    FileChooser *fileChooserButton;
    builder.get_widget_derived("filechooserbutton1", fileChooserButton, map,
                               saveButton, ambianceGrid, addHordeGrid,
                               nameEntry);

    auto returnCode = app->run(*mainWindow);
    delete mainWindow;
    return returnCode;
}
