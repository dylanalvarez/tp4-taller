#include "SelectionBox.h"

SelectionBox::SelectionBox(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : 
			Gtk::Box(cobject),
  			m_refGlade(refGlade),
  			m_pButton(nullptr),
  			back_button(nullptr) {
    m_refGlade->get_widget("b_newGame", m_pButton);
    m_refGlade->get_widget("b_back", back_button);
    if (m_pButton){
    	m_pButton->signal_clicked().connect(sigc::mem_fun(*this, &SelectionBox::on_new_game_click));
    }
    if (back_button){
    	back_button->signal_clicked().connect(sigc::mem_fun(*this, &SelectionBox::on_back_click));
    }
}

void SelectionBox::on_new_game_click(){
	Gtk::Box* main_menu;
	Gtk::Box* selection_menu;
	m_refGlade->get_widget("main_menu", main_menu);
	m_refGlade->get_widget("selection_menu", selection_menu);

	main_menu->hide();
	selection_menu->show();
}

void SelectionBox::on_back_click(){
	Gtk::Box* main_menu;
	Gtk::Box* selection_menu;
	m_refGlade->get_widget("main_menu", main_menu);
	m_refGlade->get_widget("selection_menu", selection_menu);

	main_menu->show();
	selection_menu->hide();
}
