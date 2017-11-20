#ifndef __FVECTORSPRITES_H__
#define __FVECTORSPRITES_H__
//cosa a mejorar
#include <gtkmm.h>
#include <iostream>
#include <string>

#define SpritePisoFirme 0
#define SpriteTorreDeTierra 1
#define SpriteSueloLava1 2
#define SpriteSueloLava2 3
#define SpriteSueloLava3 4
#define SpriteSueloLava4 5
#define SpriteSueloEnemigo 6
#define SpriteTorreDeFuego 7
#define SpriteFuego1 8
#define SpriteFuego2 9
#define SpriteFuego3 10
#define SpriteTorreDeAgua 11
#define SpriteAgua1 12
#define SpriteAgua2 13
#define SpriteAgua3 14
#define SpriteTorreDeAire 15
#define SpriteAire1 16
#define SpriteAire2 17
#define SpriteAire3 18
#define SpritePortalAzul 19
#define SpritePortalAzul1 20
#define SpritePortalAzul2 21
#define SpritePortalAzul3 22

#define SpriteAbominableInicial 23
#define SpriteAbominableTotal 47

#define SpriteDecierto1 71
#define SpriteDecierto2 72
#define SpriteDecierto3 73
#define SpriteDecierto4 74
#define SpritePradera1 75
#define SpritePradera2 76
#define SpritePradera3 77
#define SpritePradera4 78
#define SpriteSueloGelido1 79
#define SpriteSueloGelido2 80
#define SpriteSueloGelido3 81
#define SpriteSueloGelido4 82

#define SpriteAtaqueAgua 83
#define SpriteAtaqueAguaTotal 15
#define SpriteAtaqueAire 99
#define SpriteAtaqueAireTotal 15
#define SpriteAtaqueFuego 115
#define SpriteAtaqueFuegoTotal 15
#define SpriteAtaqueTierra 131
#define SpriteAtaqueTierraTotal 15

#define SpriteAguila 147
#define SpriteAguilaTotal 31
#define SpriteCabra 179
#define SpriteCabraTotal 31
#define SpriteDemonioVerde 212
#define SpriteDemonioVerdeTotal 39
#define SpriteEspectro 251
#define SpriteEspectroTotal 39
#define SpriteEsqueleto 291
#define SpriteEsqueletoTotal 23

#define SpriteGrieta 315
#define SpriteGrietaTotal 7
#define SpriteMeteoro 323
#define SpriteMeteoroTotal 13
#define SpriteMdeFuego 337
#define SpriteMdeFuegoTotal 12
#define SpriteRallo 350
#define SpriteRalloTotal 16
#define SpriteTornado 367
#define SpriteTornadoTotal 15

#define SpritePortalAzul02 382
#define SpritePortalAzul02Total 9
#define arco02 391
#define SpritePortaRojo02 393
#define SpritePortaRojo02Total 9

#define SpritePortalAzul01 403
#define SpritePortalAzul01Total 9
#define arco01 412
#define SpritePortaRojo01 413
#define SpritePortaRojo01Total 9

class VectorDeSprites{
protected:
  std::vector<Glib::RefPtr<Gdk::Pixbuf>> sprites;
  void cargarSprite(const char* direccion);
public:
  VectorDeSprites();
  Glib::RefPtr<Gdk::Pixbuf>& obtener (int n);

};
#endif
