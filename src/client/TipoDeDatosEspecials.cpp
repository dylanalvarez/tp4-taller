#include "TiposDeDatosExpeciales.h"


Elementos toElemento(Communication::Element element){
  switch (element) {
    case Communication::Element::earth:
     return tierra;
    case Communication::Element::water:
     return agua;
    case Communication::Element::fire:
     return fuego;
    case Communication::Element::air:
     return aire;
  }
  return aire;
}
