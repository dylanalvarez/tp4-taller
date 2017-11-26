#ifndef __RECEPTOR_H__
#define __RECEPTOR_H__

#include <gtkmm.h>
#include <iostream>
#include "TiposDeDatosExpeciales.h"
#include "OrdenadorDeFichas.h"
#include "Menu.h"
#include <vector>
#include "../common/GameClientReceiver.h"
#include "../common/GameClientSocket.h"

class Receptor {
public:
    Receptor(GameClientReceiver &reciver, GameClientSocket &socket);

    void iniciar();

    void terminar();

    GameClientReceiver &getReceiver();

private:
    GameClientReceiver &reciver;
    GameClientSocket &socket;
    bool seguir = true;
};

#endif
