#include "ErrorWithRetryController.h"
#include "ConnectingController.h"
#include <string>
#include <gtkmm/button.h>

ErrorWithRetryController::ErrorWithRetryController(
        Gtk::Bin *bin, std::unique_ptr<Controller> &currentController) :
        Controller(bin, "errorWithRetry", currentController) {
    Gtk::Button *button = nullptr;
    builder->get_widget("button", button);
    button->signal_clicked().connect(
            sigc::mem_fun(this, &ErrorWithRetryController::onRetry));
}

void ErrorWithRetryController::onRetry() {
    currentController.reset(
            new ConnectingController(parent, currentController));
}
