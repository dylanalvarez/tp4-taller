#ifndef __MENUTORRE_H__
#define __MENUTORRE_H__

#include <gtkmm.h>
#include <iostream>
#include "Fichas.h"


class MenuTorres{
private:
	Glib::RefPtr<Gtk::Builder> ventana; //ams facil pasar esto que pasar todos los subs.
  const FichaTorre *torre;
  Gtk::Label* titulo;
  Gtk::Label* rango;
  Gtk::Button* upgradeRango;
  Gtk::Label* danio; //por no usar Ñ
  Gtk::Button* upgradeDanio;
  Gtk::Label* especial;
  Gtk::Button* upgradeEspecial;
protected:
public:
	void avisarUpgradeDanio();
	void avisarUpgradeRango();
	void avisarUpgradeEspecial();
  MenuTorres (Glib::RefPtr<Gtk::Builder> &ventana2);
  void selecionarTorre(const FichaTorre &torre2);
  void decelecionarTorre();
};
#endif
