#include "Menu.h"


Menu::Menu(Glib::RefPtr<Gtk::Builder> &ventana2, Emisor &emisor) :
        emisorComandos(emisor), ventana(ventana2) {
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
    ventana->get_widget("Ping", botonPing);

    upgradeRango->signal_clicked().connect(
            sigc::mem_fun(this, &Menu::avisarUpgradeRango));
    upgradeDanio->signal_clicked().connect(
            sigc::mem_fun(this, &Menu::avisarUpgradeDanio));
    upgradeEspecial->signal_clicked().connect(
            sigc::mem_fun(this, &Menu::avisarUpgradeEspecial));

    botonPing->signal_clicked().connect(
            sigc::mem_fun(this, &Menu::avisarPing));

    botonFuego->signal_clicked().connect(
            sigc::mem_fun(this, &Menu::avisarConstruirTorreFuego));
    botonTierra->signal_clicked().connect(
            sigc::mem_fun(this, &Menu::avisarConstruirTorreTierra));
    botonAgua->signal_clicked().connect(
            sigc::mem_fun(this, &Menu::avisarConstruirTorreAgua));
    botonAire->signal_clicked().connect(
            sigc::mem_fun(this, &Menu::avisarConstruirTorreAire));

    botonEnviar->signal_clicked().connect(
            sigc::mem_fun(this, &Menu::enviarMensajeChat));
    chat->set_sensitive(false);

    Terraforming->signal_toggled().connect(
            sigc::mem_fun(this, &Menu::prepararTerraforming));
    Grieta->signal_toggled().connect(
            sigc::mem_fun(this, &Menu::prepararGrieta));
    Congelacion->signal_toggled().connect(
            sigc::mem_fun(this, &Menu::prepararCongelacion));
    Ventisca->signal_toggled().connect(
            sigc::mem_fun(this, &Menu::prepararVentisca));
    Meteorito->signal_toggled().connect(
            sigc::mem_fun(this, &Menu::prepararMeteorito));
    Tornado->signal_toggled().connect(
            sigc::mem_fun(this, &Menu::prepararTornado));
    MuroDeFuego->signal_toggled().connect(
            sigc::mem_fun(this, &Menu::prepararMuroDeFuego));
    Rayos->signal_toggled().connect(
            sigc::mem_fun(this, &Menu::prepararRayos));
}

void Menu::setNick(std::string nickNuevo) {
    elementos.clear();
    deseleccionar();
    casteando = false;
    deselecionarHechizos();
    OcultarBotones();
    chat->get_buffer()->set_text("");
    nick = nickNuevo;
}

void Menu::avisarPing() {
    auto posicion = terreno->getPosicion();
    emisorComandos.pingear(posicion.X, posicion.Y);
}

//selecionar
void Menu::selecionarTorre(const FichaTorre &torre2) {
    deselecionarHechizosTotal();
    deseleccionar();

    rango->show();
    upgradeRango->show();
    danio->show();
    upgradeDanio->show();
    especial->hide();
    upgradeEspecial->hide();


    torre = &torre2;
    std::string sAux("Daño ");
    sAux = sAux + std::to_string(torre->getDanio());
    danio->set_text(sAux.c_str());
    sAux.assign("Rango ");
    printf("%i\n", torre->getRango());
    sAux = sAux + std::to_string(torre->getRango());
    rango->set_text(sAux.c_str());

    switch (torre->getTipo()) {
        case FichaTorreDeTierra:
            titulo->set_text("Torre De Tierra \n Frecuencia:​ ​1/5 s");
            break;
        case FichaTorreDeFuego:
            titulo->set_text("Torre De Fuego \n Frecuencia:​ ​1/3 s");
            sAux.assign("Daño ");
            sAux = sAux + std::to_string(torre->getDanio());
            sAux = sAux + "/";
            sAux = sAux + std::to_string((torre->getDanio()) / 2);
            danio->set_text(sAux.c_str());
            especial->show();
            upgradeEspecial->show();
            sAux.assign("Alcance ");
            sAux = sAux + std::to_string(torre->getEspecial());
            especial->set_text(sAux.c_str());
            break;
        case FichaTorreDeAire:
            titulo->set_text("Torre De Aire");
            especial->show();
            sAux.assign("Daño aéreo ");
            sAux = sAux + std::to_string(torre->getDanio() * 5);
            especial->set_text(sAux.c_str());
            break;
        case FichaTorreDeAgua:
            titulo->set_text("Torre De Agua");
            especial->show();
            upgradeEspecial->show();
            sAux.assign("Ralentizado ");
            sAux = sAux + std::to_string(torre->getEspecial());
            especial->set_text(sAux.c_str());
            break;
        default:
            break;
    }
}

void Menu::deseleccionar() {
    titulo->set_text(" ");
    rango->hide();
    upgradeRango->hide();
    danio->hide();
    upgradeDanio->hide();
    especial->hide();
    upgradeEspecial->hide();
    menuTerreno->hide();
    terreno = NULL;
    torre = NULL;
}

void Menu::selecionarTerreno(const FichaTerreno &terreno2) {
    deselecionarHechizosTotal();
    terreno = &terreno2;
    deseleccionar();
    titulo->set_text(" ");
    switch (terreno->getTipo()) {
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
void Menu::avisarConstruirTorreTierra() {
    auto posicion = terreno->getPosicion();
    emisorComandos.cosntruirTorre(posicion.X, posicion.Y, "earth");
}

void Menu::avisarConstruirTorreAgua() {
    auto posicion = terreno->getPosicion();
    emisorComandos.cosntruirTorre(posicion.X, posicion.Y, "water");
}

void Menu::avisarConstruirTorreFuego() {
    auto posicion = terreno->getPosicion();
    emisorComandos.cosntruirTorre(posicion.X, posicion.Y, "fire");
}

void Menu::avisarConstruirTorreAire() {
    auto posicion = terreno->getPosicion();
    emisorComandos.cosntruirTorre(posicion.X, posicion.Y, "air");
}

//Upgreads
void Menu::avisarUpgradeDanio() {
    emisorComandos.upgraTorre(torre->getId(), "damage");
}

void Menu::avisarUpgradeRango() {
    emisorComandos.upgraTorre(torre->getId(), "range");
}

void Menu::avisarUpgradeEspecial() {
    if (torre->getTipo() == FichaTorreDeFuego)
        emisorComandos.upgraTorre(torre->getId(), "reach");
    else
        emisorComandos.upgraTorre(torre->getId(), "slowdown");
}

//elegirElemento
void Menu::agregarElemento(Elementos elemento) {
    elementos.push_back(elemento);
    MostrarBotones(elemento);
}

void Menu::agregarElemento(Elementos elemento, std::string &nick) {
    if (nick == this->nick) {
        elementos.push_back(elemento);
        MostrarBotones(elemento);
    }
}

void Menu::MostrarBotones(Elementos elemento) {
    switch (elemento) {
        case Elementos::fuego:
            Meteorito->show();
            MuroDeFuego->show();
            botonFuego->show();
            break;
        case Elementos::agua:
            Congelacion->show();
            Ventisca->show();
            botonAgua->show();
            break;
        case Elementos::aire:
            Tornado->show();
            Rayos->show();
            botonAire->show();
            break;
        case Elementos::tierra:
            Terraforming->show();
            Grieta->show();
            botonTierra->show();
            break;
    }
}

void Menu::OcultarBotones() {
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
void Menu::prepararHechizo(Gtk::ToggleButton *botonHechizo,
                           std::string nombreHechizo,
                           Hechizo hechizoActual2) {
    if (!(botonHechizo->get_active())) {
        casteando = false;
        titulo->hide();
        return; //si estamos desactivando. Da igual.
    }
    hechizoActual = hechizoActual2;
    deselecionarHechizos();
    deseleccionar();
    casteando = true;
    titulo->set_text(nombreHechizo.c_str());
    titulo->show();
}

void Menu::prepararTerraforming() {
    prepararHechizo(Terraforming, "Terraforming", Hechizo::Terraforming);
}

void Menu::prepararGrieta() {
    prepararHechizo(Grieta, "Grieta", Hechizo::Grieta);
}

void Menu::prepararCongelacion() {
    prepararHechizo(Congelacion, "Congelacion", Hechizo::Congelacion);
}

void Menu::prepararVentisca() {
    prepararHechizo(Ventisca, "Ventisca", Hechizo::Ventisca);
}

void Menu::prepararMeteorito() {
    prepararHechizo(Meteorito, "Meteorito", Hechizo::Meteorito);
}

void Menu::prepararTornado() {
    prepararHechizo(Tornado, "Tornado", Hechizo::Tornado);
}

void Menu::prepararMuroDeFuego() {
    prepararHechizo(MuroDeFuego, "MuroDeFuego", Hechizo::MuroDeFuego);
}

void Menu::prepararRayos() {
    prepararHechizo(Rayos, "Rayos", Hechizo::Rayos);
}

void Menu::deselecionarHechizos() {
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

void Menu::deselecionarHechizosTotal() {
    Congelacion->set_active(false);
    Ventisca->set_active(false);
    Meteorito->set_active(false);
    Tornado->set_active(false);
    MuroDeFuego->set_active(false);
    Rayos->set_active(false);
    Grieta->set_active(false);
    Terraforming->set_active(false);
}

bool Menu::estamosCasteando() {
    return casteando;
}

void Menu::lanzarHechizo(int x, int y, int objetivo) {
    switch (hechizoActual) {
        case Hechizo::Terraforming:
            emisorComandos.lanzarEchizo(x, y, "terraforming");
            break;
        case Hechizo::Grieta:
            emisorComandos.lanzarEchizo(x, y, "fissure");
            break;
        case Hechizo::Congelacion:
            emisorComandos.lanzarEchizo(objetivo, "freezing");
            break;
        case Hechizo::Ventisca:
            emisorComandos.lanzarEchizo(x, y, "blizzard");
            break;
        case Hechizo::Meteorito:
            emisorComandos.lanzarEchizo(objetivo, "meteorite");
            break;
        case Hechizo::Tornado:
            emisorComandos.lanzarEchizo(x, y, "tornado");
            break;
        case Hechizo::MuroDeFuego:
            emisorComandos.lanzarEchizo(x, y, "fireWall");
            break;
        case Hechizo::Rayos:
            emisorComandos.lanzarEchizo(objetivo, "ray");
            break;
    }
    deselecionarHechizosTotal();
    casteando = false;
}

void Menu::reActivarHechizo(Gtk::ToggleButton *hechizo) {
    hechizo->set_sensitive(true);
    hechizo->set_active(false);
}

void Menu::desectivarHechizo(Gtk::ToggleButton *hechizo) {
    hechizo->set_active(true);
    hechizo->set_sensitive(false);
}

void Menu::reActivarHechizo(Communication::PositionalPower::Type hechizo) {
    switch (hechizo) {
        case Communication::PositionalPower::Type::fissure:
            reActivarHechizo(Grieta);
            break;
        case Communication::PositionalPower::Type::terraforming:
            reActivarHechizo(Terraforming);
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

void Menu::desectivarHechizo(Communication::PositionalPower::Type hechizo) {
    switch (hechizo) {
        case Communication::PositionalPower::Type::fissure:
            desectivarHechizo(Grieta);
            break;
        case Communication::PositionalPower::Type::terraforming:
            desectivarHechizo(Terraforming);
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

void Menu::desectivarHechizo(Communication::TargetPower::Type hechizo) {
    switch (hechizo) {
        case Communication::TargetPower::Type::freezing:
            desectivarHechizo(Ventisca);
            break;
        case Communication::TargetPower::Type::ray:
            desectivarHechizo(Rayos);
            break;
        case Communication::TargetPower::Type::meteorite:
            desectivarHechizo(Meteorito);
            break;
    }
}

void Menu::actualizarPoderes(const Communication::GameState &gameState) {
    if (terreno != NULL)
      selecionarTerreno(*terreno);
    if (torre != NULL)
      selecionarTorre(*torre);

    /*for (auto it = gameState.positionalPowers.begin() ; it != gameState.positionalPowers.end(); ++it)
      desectivarHechizo(it->type);
    for (auto it = gameState.targetPowers.begin() ; it != gameState.targetPowers.end(); ++it)
      desectivarHechizo(it->type);*/
}


//Chat
void Menu::enviarMensajeChat() {
    emisorComandos.enviarMensajeDeChat(mensajeEntrada->get_text().c_str());
    mensajeEntrada->set_text(" ");
}

void Menu::recivirMensajeChat(std::string entrada) {
  auto aux = chat->get_buffer();
  auto iter = aux->end();
  aux->insert(iter, (entrada + "\n").c_str());

}
