#include "TiposDeDatosExpeciales.h"


Elementos toElemento(Communication::Element element) {
    switch (element) {
        case Communication::Element::earth:
            return Elementos::tierra;
        case Communication::Element::water:
            return Elementos::agua;
        case Communication::Element::fire:
            return Elementos::fuego;
        case Communication::Element::air:
            return Elementos::aire;
    }
    return Elementos::aire;
}
