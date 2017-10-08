//Se incluyen todos los tipos de la librería (no óptimo)
#include <gtkmm.h>
#include <iostream>
#include "PantallaDeJuego.h"

//esta clase es solo para dirigir el movimiento en este caso.
class contenedorAuxilar{
  private:
    FichaSprite* sprite;
    int x;
    int y;
  public:
    contenedorAuxilar(FichaSprite* sprite2, int x2, int y2):
                      sprite(sprite2), x(x2), y(y2){ };
    void pulsaion(){
      y = y+1;
      sprite->cambiarPosicion(x,y);
      };
  };

int main(int argc, char *argv[])
{
  //Crea la aplicación de gtkmm
  auto app = Gtk::Application::create(argc, argv);
  Gtk::Window ventana;
  ventana.set_default_size(200, 200);

  //creo dos sprites. (si los nombres son simples)
  FichaSprite* sprite1 = new FichaSprite(10, 0, "Verde.png");
  contenedorAuxilar contenedorAuxilar1 (sprite1, 10, 0);
  FichaSprite* sprite2 = new FichaSprite(30, 0, "Rojo.png");
  contenedorAuxilar contenedorAuxilar2 (sprite2, 30, 0);

  //creo pantalla
  PantallaDeJuego area;
  area.agregar(sprite1,1);
  area.agregar(sprite2,2);


  //creo boton
  Gtk::Button pulso("Pulsasion");
  pulso.signal_clicked().connect( sigc::mem_fun(
        contenedorAuxilar1, &contenedorAuxilar::pulsaion) );
  pulso.signal_clicked().connect( sigc::mem_fun(
        contenedorAuxilar2, &contenedorAuxilar::pulsaion) );
  pulso.signal_clicked().connect( sigc::mem_fun(
        area, &PantallaDeJuego::pulsaion) );

  Gtk::Box m_box1;
  m_box1.pack_start(pulso);
  m_box1.pack_start(area);
  ventana.add(m_box1);
  ventana.show_all();

  app->run(ventana);
  delete sprite1;
  delete sprite2;
  return 0;
}
