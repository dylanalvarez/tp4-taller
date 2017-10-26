#ifndef __MENUTORRE_H__
#define __MENUTORRE_H__

#include <gtkmm.h>
#include <iostream>
#include "Fichas.h"
#include "TiposDeDatosExpeciales.h"

//nombre a cambiar A Menu
class MenuTorres{
private:
	std::vector<Elementos> elementos;
	bool casteando;
	Hechizo hechizoActual;
	Glib::RefPtr<Gtk::Builder> ventana; //ams facil pasar esto que pasar todos los subs.
  const FichaTorre *torre;
  const FichaTerreno *terreno;
  Gtk::Label* titulo;
  Gtk::Label* rango;
  Gtk::Button* upgradeRango;
  Gtk::Label* danio; //por no usar Ñ
  Gtk::Button* upgradeDanio;
  Gtk::Label* especial;
  Gtk::Button* upgradeEspecial;
  Gtk::ToggleButton* Terraforming;
  Gtk::ToggleButton* Congelacion;
  Gtk::ToggleButton* Grieta;
  Gtk::ToggleButton* Ventisca;
  Gtk::ToggleButton* Meteorito;
  Gtk::ToggleButton* Tornado;
  Gtk::ToggleButton* MuroDeFuego;
  Gtk::ToggleButton* Rayos;

	void MostrarBotones(Elementos elemento);
	void deselecionarHechizos();
protected:
public:
	void prepararTerraforming();
	void prepararGrieta();

	void lanzarHechizo(int terreno, int objetivo);
	bool estamosCasteando();

	void reActivarHechizo(Gtk::ToggleButton& hechizo);

	void avisarUpgradeDanio();
	void avisarUpgradeRango();
	void avisarUpgradeEspecial();
  MenuTorres (Glib::RefPtr<Gtk::Builder> &ventana2);
  void selecionarTorre(const FichaTorre &torre2);
  void selecionarTerreno(const FichaTerreno &terreno2);
	void agregarElemento(Elementos elemento);
  void decelecionar();
};
#endif
