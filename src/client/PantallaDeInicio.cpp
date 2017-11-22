#include "PantallaDeInicio.h"


PantallaDeInicio::PantallaDeInicio(Glib::RefPtr<Gtk::Builder> &ventana,
   Emisor& emisor, MenuTorres& menu2): emisorComandos(emisor), menu(menu2){
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
    if(nick->get_text().empty())
        return;
    
  emisorComandos.elegirEquipo(nick->get_text().c_str(),
                            ids[equipos->get_active_text().c_str()]);
  menu.setNick(nick->get_text().c_str());
  }
void PantallaDeInicio::crearPartida(){
    if(nick->get_text().empty())
        return;
    if(nickEquipo->get_text().empty())
        return;
  emisorComandos.elegirMapa(nick->get_text().c_str(),
                    nickEquipo->get_text().c_str(),
                    ids[mapas->get_active_text ().c_str()]);
  menu.setNick(nick->get_text().c_str());
  }

void PantallaDeInicio::cargarDatos(
          const std::vector<Communication::NameAndID> &matches,
          const std::vector<Communication::NameAndID> &maps){
  ids.clear();
  equipos->remove_all();
  for (auto it = matches.begin(); it != matches.end(); ++it){
      equipos->insert(it->id,it->name.c_str());
      ids.emplace(std::make_pair(it->name.c_str(),it->id));
  }
  mapas->remove_all();
  for (auto it = maps.begin(); it != maps.end(); ++it){
    mapas->insert(it->id+1,it->name.c_str());
    ids.emplace(std::make_pair(it->name.c_str(),it->id));
  }
}
