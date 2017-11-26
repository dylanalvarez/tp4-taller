#ifndef TOWERDEFENSE_FILECHOOSER_H
#define TOWERDEFENSE_FILECHOOSER_H


#include <gtkmm/filechooserbutton.h>
#include "Builder.h"
#include "SaveButton.h"
#include "AmbianceGrid.h"
#include "AddHordeGrid.h"
#include "NameEntry.h"

class FileChooser : public Gtk::FileChooserButton {
public:
    FileChooser(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> &builder);

    void init(Map &map, SaveButton *saveButton,
              AmbianceGrid *ambianceGrid,
              AddHordeGrid *addHordeGrid, NameEntry *nameEntry);

protected:
    void on_file_set() override;

    Map *map = nullptr;
    Builder builder;
    Gtk::Button *loadButton;
    SaveButton *saveButton;
    AmbianceGrid *ambianceGrid;
    AddHordeGrid *addHordeGrid;
    NameEntry *nameEntry;
};


#endif //TOWERDEFENSE_FILECHOOSER_H
