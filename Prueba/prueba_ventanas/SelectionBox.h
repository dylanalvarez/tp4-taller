#ifndef __SELECTION_BOX_H__
#define __SELECTION_BOX_H__

#include <gtkmm.h>

class SelectionBox: public Gtk::Box{
public:
	SelectionBox(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);

protected:
	void on_new_game_click();
	void on_back_click();

	Glib::RefPtr<Gtk::Builder> m_refGlade;
  	Gtk::Button* m_pButton;
  	Gtk::Button* back_button;
};

#endif /*__SELECTION_BOX_H__*/
