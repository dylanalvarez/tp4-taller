#ifndef TP4_TALLER_ERRORWITHRETRYCONTROLLER_H
#define TP4_TALLER_ERRORWITHRETRYCONTROLLER_H

#include <string>
#include "Controller.h"

class ErrorWithRetryController : public Controller {
public:
    ErrorWithRetryController(Gtk::Bin *bin,
                             std::unique_ptr<Controller> &currentController);

private:
    void onRetry();
};


#endif //TP4_TALLER_ERRORWITHRETRYCONTROLLER_H
