#include "menuTorres.h"


MenuTorres::MenuTorres (Glib::RefPtr<Gtk::Builder> &ventana2, Emisor& emisor):
                  emisorComandos(emisor), ventana(ventana2){
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
    ventana->get_widget("Ping",botonPing);

    upgradeRango->signal_clicked().connect(
      sigc::mem_fun(this, &MenuTorres::avisarUpgradeRango));
    upgradeDanio->signal_clicked().connect(
      sigc::mem_fun(this, &MenuTorres::avisarUpgradeRango));
    upgradeEspecial->signal_clicked().connect(
      sigc::mem_fun(this, &MenuTorres::avisarUpgradeEspecial));

    botonPing->signal_clicked().connect(
      sigc::mem_fun(this, &MenuTorres::avisarPing));

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
    Congelacion->signal_toggled().connect(
      sigc::mem_fun(this, &MenuTorres::prepararCongelacion));
    Ventisca->signal_toggled().connect(
      sigc::mem_fun(this, &MenuTorres::prepararVentisca));
    Meteorito->signal_toggled().connect(
      sigc::mem_fun(this, &MenuTorres::prepararMeteorito));
    Tornado->signal_toggled().connect(
      sigc::mem_fun(this, &MenuTorres::prepararTornado));
    MuroDeFuego->signal_toggled().connect(
      sigc::mem_fun(this, &MenuTorres::prepararMuroDeFuego));
    Rayos->signal_toggled().connect(
      sigc::mem_fun(this, &MenuTorres::prepararRayos));
  }

void MenuTorres::setNick(std::string nickNuevo){
  elementos.clear();
  decelecionar();
  casteando = false;
  deselecionarHechizos();
  OcultarBotones();
  nick = nickNuevo;
}

void MenuTorres::avisarPing(){
  auto posicion = terreno->getPosicion();
  emisorComandos.pingear(posicion.X, posicion.Y);
}

//seleccionar
void MenuTorres::selecionarTorre (const FichaTorre &torre2){
  deselecionarHechizosTotal();
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
  printf("%i\n", torre->getRango());
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
      sAux = sAux + std::to_string(torre->getDanio()*5);
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
    deselecionarHechizosTotal();
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

//torres
void MenuTorres::avisarConstruirTorreTierra(){
  auto posicion = terreno->getPosicion();
  emisorComandos.cosntruirTorre(posicion.X, posicion.Y, "earth");
  }
void MenuTorres::avisarConstruirTorreAgua(){
  auto posicion = terreno->getPosicion();
  emisorComandos.cosntruirTorre(posicion.X, posicion.Y,"water");
  }
void MenuTorres::avisarConstruirTorreFuego(){
  auto posicion = terreno->getPosicion();
  emisorComandos.cosntruirTorre(posicion.X, posicion.Y,"fire");
  }
void MenuTorres::avisarConstruirTorreAire(){
  auto posicion = terreno->getPosicion();
  emisorComandos.cosntruirTorre(posicion.X, posicion.Y,"air");
  }

//Upgreads
void MenuTorres::avisarUpgradeDanio(){
  emisorComandos.upgraTorre(torre->getId(), "range");
  //printf("Upgrade Daño de %i\n", torre->getId());
  }
void MenuTorres::avisarUpgradeRango(){
  emisorComandos.upgraTorre(torre->getId(), "damage");
  //printf("Upgrade Rango de %i\n", torre->getId());
  }
void MenuTorres::avisarUpgradeEspecial(){
  if (torre->getTipo()==FichaTorreDeFuego)
    emisorComandos.upgraTorre(torre->getId(), "reach");
  else
    emisorComandos.upgraTorre(torre->getId(), "slowdown");
  //printf("Upgrade Especial de %i\n", torre->getId());
  }

//elegirElemento
void MenuTorres::agregarElemento(Elementos elemento){
    elementos.push_back(elemento);
    MostrarBotones(elemento);
  }
void MenuTorres::agregarElemento(Elementos elemento, std::string &nick){
  if (nick == this->nick) {
      elementos.push_back(elemento);
      MostrarBotones(elemento);
    }
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
        botonAgua->show();
      break;
      case aire:
        Tornado->show();
        Rayos->show();
        botonAire->show();
      break;
      case tierra:
        Terraforming->show();
        Grieta->show();
        botonTierra->show();
      break;
    }
  }
void MenuTorres::OcultarBotones(){
    Meteorito->hide();
    MuroDeFuego->hide();
    botonFuego->hide();
    Congelacion->hide();
    Ventisca->hide();
    botonAgua->hide();
    Tornado->hide();
    Rayos->hide();
    botonAire->hide();
    Terraforming->hide();
    Grieta->hide();
    botonTierra->hide();
  }

//los preparar no son Eficientes. Pero estan pensados para ser visuales.
void MenuTorres::prepararHechizo(Gtk::ToggleButton* botonHechizo, std::string nombreHechizo,
                      Hechizo hechizoActual2){
  if (!(botonHechizo->get_active())){
    casteando = false;
    titulo->hide();
    return; //si estamos desactivando. Da igual.
  }
  hechizoActual = hechizoActual2;
  deselecionarHechizos();
  decelecionar();
  casteando = true;
  titulo->set_text(nombreHechizo.c_str());
  titulo->show();
}
void MenuTorres::prepararTerraforming(){
  prepararHechizo(Terraforming,"Terraforming", Hechizo::Terraforming);
}
void MenuTorres::prepararGrieta(){
  prepararHechizo(Grieta,"Grieta", Hechizo::Grieta);
}
void MenuTorres::prepararCongelacion(){
  prepararHechizo(Congelacion,"Congelacion", Hechizo::Congelacion);
}
void MenuTorres::prepararVentisca(){
  prepararHechizo(Ventisca,"Ventisca", Hechizo::Ventisca);
}
void MenuTorres::prepararMeteorito(){
  prepararHechizo(Meteorito,"Meteorito", Hechizo::Meteorito);
}
void MenuTorres::prepararTornado(){
  prepararHechizo(Tornado,"Tornado", Hechizo::Tornado);
}
void MenuTorres::prepararMuroDeFuego(){
  prepararHechizo(MuroDeFuego,"MuroDeFuego", Hechizo::MuroDeFuego);
}
void MenuTorres::prepararRayos(){
  prepararHechizo(Rayos,"Rayos", Hechizo::Rayos);
}
void MenuTorres::deselecionarHechizos(){
  if (hechizoActual != Hechizo::Congelacion)
    Congelacion->set_active(false);
  if (hechizoActual != Hechizo::Ventisca)
    Ventisca->set_active(false);
  if (hechizoActual != Hechizo::Meteorito)
    Meteorito->set_active(false);
  if (hechizoActual != Hechizo::Tornado)
    Tornado->set_active(false);
  if (hechizoActual != Hechizo::MuroDeFuego)
    MuroDeFuego->set_active(false);
  if (hechizoActual != Hechizo::Rayos)
    Rayos->set_active(false);
  if (hechizoActual != Hechizo::Grieta)
    Grieta->set_active(false);
  if (hechizoActual != Hechizo::Terraforming)
    Terraforming->set_active(false);
}
void MenuTorres::deselecionarHechizosTotal(){
    Congelacion->set_active(false);
    Ventisca->set_active(false);
    Meteorito->set_active(false);
    Tornado->set_active(false);
    MuroDeFuego->set_active(false);
    Rayos->set_active(false);
    Grieta->set_active(false);
    Terraforming->set_active(false);
}
bool MenuTorres::estamosCasteando(){
  return casteando;
}
void MenuTorres::lanzarHechizo(int x, int y, int objetivo){
  switch (hechizoActual) {
    case Hechizo::Terraforming:
      if(terreno == NoColicion)
        return; //agregar algo mas de logica.. preguntar esto.
      printf("Terraforming en %i, %i\n", x,y);
      emisorComandos.lansarEchizo(x,y,"terraforming");
     break;
    case Hechizo::Grieta:
      if(terreno == NoColicion)
        return; //agregar algo mas de logica.. preguntar esto.
      printf("Grieta en %i, %i\n", x,y);
      emisorComandos.lansarEchizo(x,y,"fissure");
     break;
    case Hechizo::Congelacion:
      if(objetivo == NoColicion)
        return; //agregar algo mas de logica.. preguntar esto.
      printf("Congelacion en enemigo %i\n", objetivo);
      emisorComandos.lansarEchizo(objetivo,"freezing");
     break;
    case Hechizo::Ventisca:
      if(terreno == NoColicion)
        return; //agregar algo mas de logica.. preguntar esto.
      printf("Ventisca en %i, %i\n", x,y);
      emisorComandos.lansarEchizo(x,y,"blizzard");
     break;
    case Hechizo::Meteorito:
      if(terreno == NoColicion)
        return; //agregar algo mas de logica.. preguntar esto.
      printf("Meteorito en %i, %i\n", x,y);
      emisorComandos.lansarEchizo(x,y,"meteorite");
     break;
    case Hechizo::Tornado:
      if(terreno == NoColicion)
        return; //agregar algo mas de logica.. preguntar esto.
      printf("Tornado en %i, %i\n", x,y);
      emisorComandos.lansarEchizo(x,y,"tornado");
     break;
    case Hechizo::MuroDeFuego:
      if(terreno == NoColicion)
        return; //agregar algo mas de logica.. preguntar esto.
      printf("MuroDeFuego en %i, %i\n", x,y);
      emisorComandos.lansarEchizo(x,y,"fireWall");
     break;
    case Hechizo::Rayos:
      if(terreno == NoColicion)
        return; //agregar algo mas de logica.. preguntar esto.
      printf("Rayos en enemigo %i\n", objetivo);
      emisorComandos.lansarEchizo(objetivo,"ray");
    break;
  }
  deselecionarHechizosTotal();
  casteando = false;
}

void MenuTorres::reActivarHechizo(Gtk::ToggleButton* hechizo){
  hechizo->set_sensitive(true);
  hechizo->set_active(false);
}
void MenuTorres::desectivarHechizo(Gtk::ToggleButton* hechizo){
  hechizo->set_active(true);
  hechizo->set_sensitive(false);
}
void MenuTorres::reActivarHechizo(Communication::PositionalPower::Type hechizo){
  switch (hechizo) {
    case Communication::PositionalPower::Type::fissure:
      reActivarHechizo(Grieta);
    break;
    case Communication::PositionalPower::Type::terraforming:
      reActivarHechizo(Terraforming);
    break;
    case Communication::PositionalPower::Type::meteorite:
      reActivarHechizo(Meteorito);
    break;
    case Communication::PositionalPower::Type::fireWall:
      reActivarHechizo(MuroDeFuego);
    break;
    case Communication::PositionalPower::Type::blizzard:
      reActivarHechizo(Ventisca);
    break;
    case Communication::PositionalPower::Type::tornado:
      reActivarHechizo(Tornado);
    break;
  }
}
void MenuTorres::desectivarHechizo(Communication::PositionalPower::Type hechizo){
  switch (hechizo) {
    case Communication::PositionalPower::Type::fissure:
      desectivarHechizo(Grieta);
    break;
    case Communication::PositionalPower::Type::terraforming:
      desectivarHechizo(Terraforming);
    break;
    case Communication::PositionalPower::Type::meteorite:
      desectivarHechizo(Meteorito);
    break;
    case Communication::PositionalPower::Type::fireWall:
      desectivarHechizo(MuroDeFuego);
    break;
    case Communication::PositionalPower::Type::blizzard:
      desectivarHechizo(Ventisca);
    break;
    case Communication::PositionalPower::Type::tornado:
      desectivarHechizo(Tornado);
    break;
  }
}
void MenuTorres::desectivarHechizo(Communication::TargetPower::Type hechizo){
  switch (hechizo) {
    case Communication::TargetPower::Type::freezing:
      desectivarHechizo(Ventisca);
    break;
    case Communication::TargetPower::Type::ray:
      desectivarHechizo(Rayos);
    break;
  }
}
void MenuTorres::actualizarPoderes(const Communication::GameState &gameState){
  /*for (auto it = gameState.positionalPowers.begin() ; it != gameState.positionalPowers.end(); ++it)
    desectivarHechizo(it->type);
  for (auto it = gameState.targetPowers.begin() ; it != gameState.targetPowers.end(); ++it)
    desectivarHechizo(it->type);*/
}



//Chat
void MenuTorres::enviarMensajeChat(){
  emisorComandos.enviarMensajeDeChat(mensajeEntrada->get_text().c_str());
  mensajeEntrada->set_text(" ");
}
void MenuTorres::recivirMensajeChat(std::string entrada){
  auto aux = chat->get_buffer ();
  auto c = mensajeEntrada->get_text(); //esto es lo que hay que cambiar.
  aux->insert_at_cursor("\n");
  aux->insert_at_cursor(entrada.c_str());
  chat->set_buffer(aux);
}
