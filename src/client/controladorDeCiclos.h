#ifndef __CONTRALADORcicloS_H__
#define __CONTRALADORcicloS_H__

#include <gtkmm.h>
#include <iostream>
#include "TiposDeDatosExpeciales.h"
#include "receptor.h"
#include "emisor.h"
#include <thread>

class controladorDeCiclos {
private:
    Receptor &receptor;
    Emisor &emisor;
    std::thread emisorThread;
    std::thread receptorThread;
    bool seguir = true;
public:
    controladorDeCiclos(Receptor &receptor2, Emisor &emisor2); //falso
    void iniciar();

    void terminar();

    Communication::GameState estadoActual();
};

#endif
