#ifndef __MENUTORRE_H__
#define __MENUTORRE_H__

#include <gtkmm.h>
#include <iostream>
#include "Fichas.h"
#include "TiposDeDatosExpeciales.h"
#include "emisor.h"
#include <string>

class Menu {
private:
    std::string nick;
    Emisor &emisorComandos;
    std::vector<Elementos> elementos;
    bool casteando = false;
    Hechizo hechizoActual;
    Glib::RefPtr<Gtk::Builder> ventana;
    const FichaTorre *torre;
    const FichaTerreno *terreno;
    Gtk::Label *titulo;
    bool seleccionadaTorre;
    bool seleccionadaTerreno;
    int danioValor;
    int rangoValor;
    int especialValor;

    //torre
    Gtk::Label *textoConstruirTorre;

    Gtk::Label *rango;
    Gtk::Button *upgradeRango;
    Gtk::Label *danio; //por no usar Ñ
    Gtk::Button *upgradeDanio;
    Gtk::Label *especial;
    Gtk::Button *upgradeEspecial;

    //terreno
    Gtk::Box *menuTerreno;
    Gtk::Button *botonFuego;
    Gtk::Button *botonTierra;
    Gtk::Button *botonAgua;
    Gtk::Button *botonAire;

    Gtk::Button *botonPing;

    //poderes
    Gtk::ToggleButton *Terraforming;
    Gtk::ToggleButton *Congelacion;
    Gtk::ToggleButton *Grieta;
    Gtk::ToggleButton *Ventisca;
    Gtk::ToggleButton *Meteorito;
    Gtk::ToggleButton *Tornado;
    Gtk::ToggleButton *MuroDeFuego;
    Gtk::ToggleButton *Rayos;

    //chat
    Gtk::Button *botonEnviar;
    Gtk::Entry *mensajeEntrada;
    Gtk::TextView *chat;

    void MostrarBotones(Elementos elemento);

    void OcultarBotones();

    void deselecionarHechizos();

    void deselecionarHechizosTotal();

    void desectivarHechizo(Gtk::ToggleButton *hechizo);

    void reActivarHechizo(Gtk::ToggleButton *hechizo);

    void
    prepararHechizo(Gtk::ToggleButton *botonHechizo, std::string nombreHechizo,
                    Hechizo hechizoActual2);

protected:
public:
    void setNick(std::string nickNuevo);

    void avisarConstruirTorreTierra();

    void avisarConstruirTorreFuego();

    void avisarConstruirTorreAgua();

    void avisarConstruirTorreAire();

    void avisarPing();

    void prepararTerraforming();

    void prepararGrieta();

    void prepararCongelacion();

    void prepararVentisca();

    void prepararMeteorito();

    void prepararTornado();

    void prepararMuroDeFuego();

    void prepararRayos();


    void
    lanzarHechizo(int x, int y, int objetivo);
    bool estamosCasteando();

    void actualizarPoderes(const Communication::GameState &gameState);

    void desectivarHechizo(Communication::PositionalPower::Type hechizo);

    void reActivarHechizo(Communication::PositionalPower::Type hechizo);

    void desectivarHechizo(Communication::TargetPower::Type hechizo);

    void reActivarHechizo(Communication::TargetPower::Type hechizo);

    void avisarUpgradeDanio();

    void avisarUpgradeRango();

    void avisarUpgradeEspecial();

    void enviarMensajeChat();

    void recivirMensajeChat(std::string entrada);

    Menu(Glib::RefPtr<Gtk::Builder> &ventana2, Emisor &emisor);

    void selecionarTorre(const FichaTorre &torre2);

    void selecionarTerreno(const FichaTerreno &terreno2);

    void agregarElemento(Elementos elemento);

    void agregarElemento(Elementos elemento, std::string &nick);

    void deseleccionar();

    void actualizarTorre();
};

#endif
