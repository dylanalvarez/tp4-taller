#include "HordeFrequencySpinButton.h"

HordeFrequencySpinButton::HordeFrequencySpinButton(
        BaseObjectType *obj,
        const Glib::RefPtr<Gtk::Builder> &builder) : Gtk::SpinButton(obj) {
    this->signal_value_changed().connect(
            sigc::mem_fun(this, &HordeFrequencySpinButton::onChange));
}

void HordeFrequencySpinButton::onChange() {
    map->setSecondsBetweenHordes(this->get_value_as_int());
}

void HordeFrequencySpinButton::init(Map &map) { this->map = &map; }

void HordeFrequencySpinButton::setFromMap() {
    this->set_value(map->getSecondsBetweenHordes());
}
