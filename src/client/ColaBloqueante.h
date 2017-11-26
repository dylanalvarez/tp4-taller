#ifndef __LDDL_FON__
#define __LDDL_FON__

#include <string>
#include <list>
#include <condition_variable>
#include <mutex>
#include "TiposDeDatosExpeciales.h"

class ColaBloqueante {
private:
    std::mutex m;
    std::condition_variable cv;
    std::list<Mensaje> lista;
    bool ready, finalizado;
public:
    ColaBloqueante();

    int agregarLinea(Mensaje entrada);

    int tomarNuevoTermino(Mensaje *salida);

    int finDeLista();
};


#endif
