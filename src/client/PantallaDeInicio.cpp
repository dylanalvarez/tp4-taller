#include "PantallaDeInicio.h"


PantallaDeInicio::PantallaDeInicio (Glib::RefPtr<Gtk::Builder> &ventana, Emisor& emisor):
                  emisorComandos(emisor){
  	ventana->get_widget("Unirse", unirse);
  	ventana->get_widget("Crear", crear);
  	ventana->get_widget("Nick", nick);
  	ventana->get_widget("NombreEquipo", nickEquipo);
  	ventana->get_widget("equipos", equipos);
  	ventana->get_widget("Mapas", mapas);
  	//ventana->get_widget("NombreTorre", titulo);

    unirse->signal_clicked().connect(
      sigc::mem_fun(this, &PantallaDeInicio::unirsePartida));
    crear->signal_clicked().connect(
      sigc::mem_fun(this, &PantallaDeInicio::crearPartida));
  }

void PantallaDeInicio::unirsePartida(){
  emisorComandos.elegirEquipo(nick->get_text().c_str(),
                            equipos->get_id_column());
  }
void PantallaDeInicio::crearPartida(){
  emisorComandos.elegirMapa(nick->get_text().c_str(),
                    nickEquipo->get_text().c_str(), mapas->get_id_column());
  }

void PantallaDeInicio::cargarDatos(
          const std::vector<Communication::NameAndID> &matches,
          const std::vector<Communication::NameAndID> &maps){
  equipos->remove_all();
  for (auto it = matches.begin(); it != matches.end(); ++it){
      equipos->insert(it->id,it->name.c_str());
  }
  mapas->remove_all();
  for (auto it = maps.begin(); it != maps.end(); ++it){
    mapas->insert(it->id,it->name.c_str());
  }
}
