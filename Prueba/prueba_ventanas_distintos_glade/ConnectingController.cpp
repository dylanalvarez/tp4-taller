#include <gtkmm/button.h>
#include <gtkmm/builder.h>
#include <string>
#include "ConnectingController.h"
#include "ErrorWithRetryController.h"

ConnectingController::ConnectingController(
        Gtk::Bin *bin, std::unique_ptr<Controller> &currentController) :
        Controller(bin, "connecting", currentController) {
    Gtk::Button *button = nullptr;
    builder->get_widget("button", button);
    button->signal_clicked().connect(
            sigc::mem_fun(this, &ConnectingController::onConnectionError));
}

void ConnectingController::onConnectionError() {
    currentController.reset(
            new ErrorWithRetryController(parent, currentController));
}
