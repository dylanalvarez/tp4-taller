#ifndef __CONTRALADORSICLOS_H__
#define __CONTRALADORSICLOS_H__

#include <gtkmm.h>
#include <iostream>


class ControladorDeSiclos{
private:
public:
  void iniciar();
  typedef sigc::signal<void> type_pulso;
  type_pulso getPulso();
  void terminar();
protected:
  bool seguir = true;
  type_pulso pulso;
};
#endif
