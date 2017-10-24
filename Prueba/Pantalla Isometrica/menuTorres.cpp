#include "menuTorres.h"


MenuTorres::MenuTorres (Glib::RefPtr<Gtk::Builder> &ventana2): ventana(ventana2){
  	ventana->get_widget("NombreTorre", titulo);
  	ventana->get_widget("Datos1", rango);
    ventana->get_widget("Upgred1", upgradeRango);
    ventana->get_widget("Datos2", danio);
    ventana->get_widget("Upgred2", upgradeDanio);
    ventana->get_widget("Datos3", especial);
    ventana->get_widget("Upgred3", upgradeEspecial);
    upgradeRango->signal_clicked().connect(
      sigc::mem_fun(this, &MenuTorres::avisarUpgradeRango));
    upgradeDanio->signal_clicked().connect(
      sigc::mem_fun(this, &MenuTorres::avisarUpgradeRango));
    upgradeEspecial->signal_clicked().connect(
      sigc::mem_fun(this, &MenuTorres::avisarUpgradeEspecial));
  }

void MenuTorres::cargarTorre (const FichaTorre &torre2){
  titulo->show();
  rango->show();
  upgradeRango->show();
  danio->show();
  upgradeDanio->show();
  especial->hide();
  upgradeEspecial->hide();


  torre =  &torre2;
  std::string sAux ("Daño ");
  sAux = sAux + std::to_string(torre->getDanio());
  danio->set_text(sAux.c_str());
  sAux.assign ("Rango ");
  sAux = sAux + std::to_string(torre->getRango());
  rango->set_text(sAux.c_str());

  switch (torre->getTipo()) {
    case FichaTorreDeTierra:
      titulo->set_text("Torre De Tierra");
      break;
    case FichaTorreDeFuego:
      titulo->set_text("Torre De Fuego");
      especial->show ();
      upgradeEspecial->show ();
      sAux.assign ("Alcance ");
      sAux = sAux + std::to_string(torre->getEspecial());
      especial->set_text(sAux.c_str());
      break;
    case FichaTorreDeAire:
      titulo->set_text("Torre De Aire");
      especial->show ();
      sAux.assign ("Daño aéreo ");
      sAux = sAux + std::to_string(torre->getEspecial());
      especial->set_text(sAux.c_str());
      break;
    case FichaTorreDeAgua:
      titulo->set_text("Torre De Agua");
      especial->show ();
      upgradeEspecial->show ();
      sAux.assign ("Ralentizado ");
      sAux = sAux + std::to_string(torre->getEspecial());
      especial->set_text(sAux.c_str());
      break;
    default:
      break;
  }
}

void MenuTorres::decelecionarTorre (){
  titulo->hide();
  rango->hide();
  upgradeRango->hide();
  danio->hide();
  upgradeDanio->hide();
  especial->hide();
  upgradeEspecial->hide();
  }

//estas son las vericones "betas"
void MenuTorres::avisarUpgradeDanio(){
  printf("Upgrade Daño de %i\n", torre->getId());
  }
void MenuTorres::avisarUpgradeRango(){
  printf("Upgrade Rango de %i\n", torre->getId());
  }
void MenuTorres::avisarUpgradeEspecial(){
  printf("Upgrade Especial de %i\n", torre->getId());
  }
