#ifndef TP4_TALLER_LOADFILEGRID_H
#define TP4_TALLER_LOADFILEGRID_H

#include <gtkmm/grid.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include "Builder.h"
#include "Map.h"
#include "SaveButton.h"
#include "AmbianceGrid.h"
#include "HordeFrequencySpinButton.h"
#include "AddHordeGrid.h"

class LoadFileGrid : public Gtk::Grid {
public:
    LoadFileGrid(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> &builder);

    void init(Map &map, SaveButton* saveButton,
              AmbianceGrid *ambianceGrid,
              HordeFrequencySpinButton *hordeFrequencySpinButton,
              AddHordeGrid *addHordeGrid);

private:
    void loadFile();

    Map *map = nullptr;
    Builder builder;
    Gtk::Entry* fileNameEntry;
    Gtk::Button* loadButton;
    SaveButton* saveButton;
    AmbianceGrid *ambianceGrid;
    HordeFrequencySpinButton *hordeFrequencySpinButton;
    AddHordeGrid *addHordeGrid;
};


#endif //TP4_TALLER_LOADFILEGRID_H
