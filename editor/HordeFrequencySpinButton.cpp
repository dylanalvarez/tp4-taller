#include "HordeFrequencySpinButton.h"

HordeFrequencySpinButton::HordeFrequencySpinButton(
        BaseObjectType *obj,
        const Glib::RefPtr<Gtk::Builder> &builder,
        Map &map) : Gtk::SpinButton(obj), map(map) {
    this->signal_value_changed().connect(
            sigc::mem_fun(this, &HordeFrequencySpinButton::onChange));
}

void HordeFrequencySpinButton::onChange() {
    map.setSecondsBetweenHordes(this->get_value_as_int());
}
