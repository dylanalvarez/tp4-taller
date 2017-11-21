#ifndef __GESTIONADORDESONIDOS_H__
#define __GESTIONADORDESONIDOS_H__

#include <iostream>
#include "../common/Sound.h"

class GestionadorDeSonidos{
private:
 std::string proximoSonido;
 bool haySonido;
 bool seguir;
protected:
 void reprorduicrSonid();
public:
 void iniciar();
 void terminar();
 void siguienteSonido(std::string nuevoSonido);
};
#endif
