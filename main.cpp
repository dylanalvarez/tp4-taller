#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <iostream>

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
    Gtk::Window window;
    window.set_default_size(200, 200);
    Gtk::Button button("Hello world!");
    window.add(button);
    button.signal_clicked().connect(
            sigc::slot<void>(
                    []() { std::cout << "Hello world!" << std::endl; }));
    button.show();
    return app->run(window);
}
