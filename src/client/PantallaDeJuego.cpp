#include "PantallaDeJuego.h"
//estos dos van en Pixeles.
#define VelocidadDesplasamiento 10
#define SpriteWidth 79
#define SpriteHeigth 159
//esto es para terminar de ajustar la escala.
#define ConstantenMagicaEscala 5 //cantidad de sprites de largo
#define AreaDeDesplasamiento 100
// o son cosntante o se calculan al crear la pantalla de juego
#define desplasamientoSuperiorX 2000
#define desplasamientoInferiorX 2000
#define desplasamientoSuperiorY 2000
#define desplasamientoInferiorY 2000


void PantallaDeJuego::reniciarDesplasamiento(){
  datosActuales.desplasamientoX = 520;
  datosActuales.desplasamientoY = 220;
}

void PantallaDeJuego::desplazamientoIncrementalEnX() {
    if ((datosActuales.desplasamientoX + VelocidadDesplasamiento) <
        desplasamientoSuperiorX)
        datosActuales.desplasamientoX += VelocidadDesplasamiento;
}

void PantallaDeJuego::desplazamientoDecrementalEnX() {
    if ((datosActuales.desplasamientoX - VelocidadDesplasamiento) >
        -desplasamientoInferiorX)
        datosActuales.desplasamientoX -= VelocidadDesplasamiento;
}

void PantallaDeJuego::desplazamientoIncrementalEnY() {
    if ((datosActuales.desplasamientoY + VelocidadDesplasamiento) <
        desplasamientoSuperiorY)
        datosActuales.desplasamientoY += VelocidadDesplasamiento;
}

void PantallaDeJuego::desplazamientoDecrementalEnY() {
    if ((datosActuales.desplasamientoY - VelocidadDesplasamiento) >
        -desplasamientoInferiorY)
        datosActuales.desplasamientoY -= VelocidadDesplasamiento;
}

bool PantallaDeJuego::on_leave_notify_event(GdkEventCrossing *event) {
    incirementeEnX = false;
    decrementoEnX = false;
    incirementeEnY = false;
    decrementoEnY = false;
    return Gtk::DrawingArea::on_leave_notify_event(event);
}

bool PantallaDeJuego::on_key_press_event(GdkEventKey *event) {
    if (event->keyval == GDK_KEY_w)
        desplazamientoIncrementalEnX();
    if (event->keyval == GDK_KEY_s)
        desplazamientoDecrementalEnY();
    if (event->keyval == GDK_KEY_a)
        desplazamientoIncrementalEnY();
    if (event->keyval == GDK_KEY_d)
        desplazamientoDecrementalEnX();
    return Gtk::DrawingArea::on_key_press_event(event);
}

bool PantallaDeJuego::on_motion_notify_event(GdkEventMotion *event) {
    incirementeEnX = false;
    decrementoEnX = false;
    incirementeEnY = false;
    decrementoEnY = false;

    if (event->x < AreaDeDesplasamiento)
        incirementeEnX = true;
    if (event->x > datosActuales.width - AreaDeDesplasamiento)
        decrementoEnX = true;
    if (event->y < AreaDeDesplasamiento)
        incirementeEnY = true;
    if (event->y > datosActuales.height - AreaDeDesplasamiento)
        decrementoEnY = true;
    return Gtk::DrawingArea::on_motion_notify_event(event);
}

bool PantallaDeJuego::ejecutarCicloDeAnimacion() {
    fichas.ejecutarCicloDeAnimacion(); //trabajar en esto para reducir la cantidad de pulsos.
    queue_draw(); //Esto redibuja
    return true;
}

bool PantallaDeJuego::ejecutarcicloDesplasamientos() {
    if (incirementeEnX)
        desplazamientoIncrementalEnX();
    if (decrementoEnX)
        desplazamientoDecrementalEnX();
    if (incirementeEnY)
        desplazamientoIncrementalEnY();
    if (decrementoEnY)
        desplazamientoDecrementalEnY();
    return true;
}

bool PantallaDeJuego::on_button_press_event(GdkEventButton *event) {
    //si es necesario mejorar presision
    int x = event->x;
    int y = event->y;
    x = x - datosActuales.desplasamientoX;
    y = y - datosActuales.desplasamientoY;
    int x2 = (x + y * (2.025641025)) / (1.795454544);
    int y2 = (x - y * (2.025641025)) / (-1.795454544);
    int aux0;
    if (menu.estamosCasteando()) {
        if ((aux0 = fichas.ObetenerTerrenoEnEstaPosicion(x2, y2)) == NoColicion)
            return Gtk::DrawingArea::on_button_press_event(event);
        auto posicion = fichas.getTerreno(aux0).getPosicion();
        menu.lanzarHechizo(posicion.X, posicion.Y,
                           fichas.ObetenerEnemigoEnEstaPosicion(x2, y2));
        return Gtk::DrawingArea::on_button_press_event(event);
    }

    int id = fichas.ObetenerTorreEnEstaPosicion(x2, y2);
    if (id != NoColicion) {
        menu.selecionarTorre(fichas.getTorre(id));
        return Gtk::DrawingArea::on_button_press_event(event);
    }
    id = fichas.ObetenerTerrenoEnEstaPosicion(x2, y2);
    if (id != NoColicion) {
        menu.selecionarTerreno(fichas.getTerreno(id));
        return Gtk::DrawingArea::on_button_press_event(event);
    }
    menu.deseleccionar();
    return Gtk::DrawingArea::on_button_press_event(event);
}

bool PantallaDeJuego::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
    Gtk::Allocation allocation = get_allocation();
    datosActuales.width = allocation.get_width();
    datosActuales.height = allocation.get_height();
// por alguna razon dejo de funcionar.
//  double width2 = (double)width/SpriteWidth/ConstantenMagicaEscala;
//  double height2 = (double)height/SpriteHeigth/ConstantenMagicaEscala;
//  cr->scale(width2,height2);
//  cr->save();

    fichas.imprir(cr, datosActuales);
    return true; //esto es parte del formato de timer..
}

PantallaDeJuego::PantallaDeJuego(OrdenadorDeFichas &fichas2,
                                 Glib::RefPtr<Gtk::Builder> &ventana,
                                 Emisor &emisor) :
        fichas(fichas2), menu(ventana, emisor) {
    set_can_focus(true); //activa la relacion con el teclado
    add_events(Gdk::BUTTON_PRESS_MASK);
    add_events(Gdk::LEAVE_NOTIFY_MASK);
    add_events(Gdk::POINTER_MOTION_MASK); //activa las otras relaciones
    datosActuales.desplasamientoX = 120;
    datosActuales.desplasamientoY = 120;
}

PantallaDeJuego::~PantallaDeJuego() {
}

void PantallaDeJuego::agregarElemento(Elementos elemento) {
    menu.agregarElemento(elemento);
    elementos.push_back(elemento);
}

Menu &PantallaDeJuego::getMenu() {
    return menu;
}
