#ifndef TP4_TALLER_CONNECTINGCONTROLLER_H
#define TP4_TALLER_CONNECTINGCONTROLLER_H

#include <string>
#include <gtkmm/window.h>
#include "Controller.h"

class ConnectingController : public Controller {
public:
    ConnectingController(Gtk::Bin *bin,
                         std::unique_ptr<Controller> &currentController);

private:
    void onConnectionError();
};


#endif //TP4_TALLER_CONNECTINGCONTROLLER_H
