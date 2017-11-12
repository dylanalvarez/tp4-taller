#include "VectorDeSprites.h"


void VectorDeSprites::cargarSprite(const char* direccion){
  try{ //ver esto.
    sprites.push_back(Gdk::Pixbuf::create_from_file(direccion));
  }
  catch(const Gio::ResourceError& ex){
    std::cerr << "ResourceError: " << ex.what() << std::endl;
  }
  catch(const Gdk::PixbufError& ex){
    std::cerr << "PixbufError: " << ex.what() << std::endl;
  }
}
VectorDeSprites::VectorDeSprites(){
  cargarSprite("Sprites/PisoFirme.png");
  cargarSprite("Sprites/TorreDeTierra.png");
  cargarSprite("Sprites/SueloLava1.png");
  cargarSprite("Sprites/SueloLava2.png");
  cargarSprite("Sprites/SueloLava3.png");
  cargarSprite("Sprites/SueloLava4.png");
  cargarSprite("Sprites/SueloEnemigo.png");
  cargarSprite("Sprites/TorreDeFuego.png");
  cargarSprite("Sprites/TorreFuego1.png");
  cargarSprite("Sprites/TorreFuego2.png");
  cargarSprite("Sprites/TorreFuego3.png");
  cargarSprite("Sprites/TorreDeAgua.png");
  cargarSprite("Sprites/TorreAgua1.png");
  cargarSprite("Sprites/TorreAgua2.png");
  cargarSprite("Sprites/TorreAgua3.png");
  cargarSprite("Sprites/TorreDeAire.png");
  cargarSprite("Sprites/TorreAire1.png");
  cargarSprite("Sprites/TorreAire2.png");
  cargarSprite("Sprites/TorreAire3.png");
  cargarSprite("Sprites/PortalAzul.png");
  cargarSprite("Sprites/PortalAzul1.png");
  cargarSprite("Sprites/PortalAzul2.png");
  cargarSprite("Sprites/PortalAzul3.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante1.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante2.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante3.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante4.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante5.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante6.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante7.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante8.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante9.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante10.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante11.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante12.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante13.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante14.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante15.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante16.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante17.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante18.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante19.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante20.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante21.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante22.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante23.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante24.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante25.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante26.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante27.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante28.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante29.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante30.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante31.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante32.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante33.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante34.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante35.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante36.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante37.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante38.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante39.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante40.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante41.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante42.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante43.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante44.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante45.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante46.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante47.png");
  cargarSprite("Sprites/AbmonibleCaminarAdelante48.png");
  cargarSprite("Sprites/Decierto1.png");
  cargarSprite("Sprites/Decierto2.png");
  cargarSprite("Sprites/Decierto3.png");
  cargarSprite("Sprites/Decierto4.png");
  cargarSprite("Sprites/Pradera1.png");
  cargarSprite("Sprites/Pradera2.png");
  cargarSprite("Sprites/Pradera3.png");
  cargarSprite("Sprites/Pradera4.png");
  cargarSprite("Sprites/SueloGelido1.png");
  cargarSprite("Sprites/SueloGelido2.png");
  cargarSprite("Sprites/SueloGelido3.png");
  cargarSprite("Sprites/SueloGelido4.png");

}
Glib::RefPtr<Gdk::Pixbuf>& VectorDeSprites::obtener (int n){
  return (sprites[n]);
}
