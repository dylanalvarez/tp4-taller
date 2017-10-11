#include <gtkmm.h>
#include <iostream>
#include "SelectionBox.h"

int main(int argc, char** argv){
	auto app = Gtk::Application::create(argc, argv);

	Gtk::Window* window;
	SelectionBox* main_menu;

	auto refBuilder = Gtk::Builder::create();
	refBuilder->add_from_file("basic.glade");

	refBuilder->get_widget("window1", window);
	refBuilder->get_widget_derived("main_menu", main_menu);

	app->run(*window);
}