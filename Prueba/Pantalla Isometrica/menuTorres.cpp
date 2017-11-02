#include "menuTorres.h"


MenuTorres::MenuTorres (Glib::RefPtr<Gtk::Builder> &ventana2): ventana(ventana2){
  	ventana->get_widget("NombreTorre", titulo);

  	ventana->get_widget("Datos1", rango);
    ventana->get_widget("Upgred1", upgradeRango);
    ventana->get_widget("Datos2", danio);
    ventana->get_widget("Upgred2", upgradeDanio);
    ventana->get_widget("Datos3", especial);
    ventana->get_widget("Upgred3", upgradeEspecial);

    ventana->get_widget("Terraforming", Terraforming);
  	ventana->get_widget("Congelacion", Congelacion);
    ventana->get_widget("Grieta", Grieta);
    ventana->get_widget("Ventisca", Ventisca);
    ventana->get_widget("Meteorito", Meteorito);
    ventana->get_widget("Tornado", Tornado);
    ventana->get_widget("MuroDeFuego", MuroDeFuego);
    ventana->get_widget("Rayos", Rayos);

    ventana->get_widget("Menu terreno", menuTerreno);
    ventana->get_widget("Fuego", botonFuego);
    ventana->get_widget("Tierra", botonTierra);
    ventana->get_widget("Agua", botonAgua);
    ventana->get_widget("Aire", botonAire);

    ventana->get_widget("Enviar", botonEnviar);
    ventana->get_widget("mensaje", mensajeEntrada);
    ventana->get_widget("charla del Chat", chat);

    upgradeRango->signal_clicked().connect(
      sigc::mem_fun(this, &MenuTorres::avisarUpgradeRango));
    upgradeDanio->signal_clicked().connect(
      sigc::mem_fun(this, &MenuTorres::avisarUpgradeRango));
    upgradeEspecial->signal_clicked().connect(
      sigc::mem_fun(this, &MenuTorres::avisarUpgradeEspecial));

    botonFuego->signal_clicked().connect(
      sigc::mem_fun(this, &MenuTorres::avisarConstruirTorreFuego));
    botonTierra->signal_clicked().connect(
      sigc::mem_fun(this, &MenuTorres::avisarConstruirTorreTierra));
    botonAgua->signal_clicked().connect(
      sigc::mem_fun(this, &MenuTorres::avisarConstruirTorreAgua));
    botonAire->signal_clicked().connect(
      sigc::mem_fun(this, &MenuTorres::avisarConstruirTorreAire));

    botonEnviar->signal_clicked().connect(
      sigc::mem_fun(this, &MenuTorres::enviarMensajeChat));
    chat->set_sensitive(false);

    Terraforming->signal_toggled().connect(
      sigc::mem_fun(this, &MenuTorres::prepararTerraforming));
    Grieta->signal_toggled().connect(
      sigc::mem_fun(this, &MenuTorres::prepararGrieta));
  }

void MenuTorres::selecionarTorre (const FichaTorre &torre2){
  decelecionar();

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
      titulo->set_text("Torre De Tierra \n Frecuencia:​ ​1/5 s");
      break;
    case FichaTorreDeFuego:
      titulo->set_text("Torre De Fuego \n Frecuencia:​ ​1/3 s");
      sAux.assign  ("Daño ");
      sAux = sAux + std::to_string(torre->getDanio());
      sAux = sAux + "/";
      sAux = sAux + std::to_string((torre->getDanio())/2);
      danio->set_text(sAux.c_str());
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
      especial->show();
      upgradeEspecial->show();
      sAux.assign ("Ralentizado ");
      sAux = sAux + std::to_string(torre->getEspecial());
      especial->set_text(sAux.c_str());
      break;
    default:
      break;
  }
}

void MenuTorres::decelecionar(){
  titulo->set_text(" ");
  rango->hide();
  upgradeRango->hide();
  danio->hide();
  upgradeDanio->hide();
  especial->hide();
  upgradeEspecial->hide();
  menuTerreno->hide();
  }

void MenuTorres::selecionarTerreno(const FichaTerreno &terreno2){
    terreno =  &terreno2;
    decelecionar();
    titulo->set_text(" ");
    switch (terreno->getTipo()){
      case FichaPisoFirme:
          titulo->set_text("Piso Firme");
          menuTerreno->show();
      break;
      case FichaPisoEnemigos:
          titulo->set_text("Piso Enemigo");
      break;
      default:
          titulo->set_text("Fondo");
      break;
      }
}

void MenuTorres::avisarConstruirTorreTierra(){
  printf("Construir Torre de Tierra en:  ");
  terreno->imprimierCordenadas();
  }
void MenuTorres::avisarConstruirTorreAgua(){
  printf("Construir Torre de Agua en:  ");
  terreno->imprimierCordenadas();
  }
void MenuTorres::avisarConstruirTorreFuego(){
  printf("Construir Torre de Fuego en:  ");
  terreno->imprimierCordenadas();
  }
void MenuTorres::avisarConstruirTorreAire(){
  printf("Construir Torre de Aire en:  ");
  terreno->imprimierCordenadas();
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

void MenuTorres::agregarElemento(Elementos elemento){
    elementos.push_back(elemento);
    MostrarBotones(elemento);
  }

void MenuTorres::MostrarBotones(Elementos elemento){
    switch (elemento) {
      case fuego:
        Meteorito->show();
        MuroDeFuego->show();
        botonFuego->show();
      break;
      case agua:
        Congelacion->show();
        Ventisca->show();
      break;
      case aire:
        Tornado->show();
        Rayos->show();
      break;
      case tierra:
        Terraforming->show();
        Grieta->show();
        botonTierra->show();
      break;
    }
  }

//los preparar no son Eficientes. Pero estan pensados para ser visuales.
void MenuTorres::prepararTerraforming(){
  if (!(Terraforming->get_active())){
    casteando = false;
    titulo->hide();
    return; //si estamos desactivando. Da igual.
  }
  hechizoActual = Hechizo::Terraforming;
  deselecionarHechizos();
  decelecionar();
  casteando = true;
  titulo->set_text("Terraforming");
  titulo->show();
}
void MenuTorres::prepararGrieta(){
  if (!(Grieta->get_active())){
    casteando = false;
    titulo->hide();
    return; //si estamos desactivando. Da igual.
  }
  hechizoActual = Hechizo::Grieta;
  decelecionar();
  deselecionarHechizos();
  casteando = true;
  titulo->set_text("Grieta");
  titulo->show();

}

void MenuTorres::deselecionarHechizos(){
  //es horriblo..
  if (hechizoActual != Hechizo::Grieta)
    Grieta->set_active(false);
  if (hechizoActual != Hechizo::Terraforming)
    Terraforming->set_active(false);
}
bool MenuTorres::estamosCasteando(){
  return casteando;
}
void MenuTorres::lanzarHechizo(int terreno, int objetivo){
  switch (hechizoActual) {
    case Hechizo::Terraforming:
      if(terreno == NoColicion)
        return; //agregar algo mas de logica.. preguntar esto.
      printf("Terraforming en %i\n", terreno);
      Terraforming->set_sensitive(false);
    break;
    case Hechizo::Grieta:
      if(terreno == NoColicion)
        return; //agregar algo mas de logica.. preguntar esto.
      printf("Grieta en %i\n", terreno);
      Grieta->set_sensitive(false);
    break;
    default:
      //falta que aca salte un error.
    break;
  }
  casteando = false;
}

void MenuTorres::reActivarHechizo(Gtk::ToggleButton& hechizo){
  hechizo.set_sensitive(true);
  hechizo.set_active(false);
}

void MenuTorres::enviarMensajeChat(){
  recivirMensajeChat(mensajeEntrada->get_text().c_str());
  mensajeEntrada->set_text(" ");
}

void MenuTorres::recivirMensajeChat(std::string entrada){
  auto aux = chat->get_buffer ();
  auto c = mensajeEntrada->get_text(); //esto es lo que hay que cambiar.
  aux->insert_at_cursor("\n");
  aux->insert_at_cursor(entrada.c_str());
  chat->set_buffer(aux);
}
