#include "infoBaseDatos.h"

yalefaces::yalefaces():infoBaseDatos(15, 11, "yalefaces"){
	insertar_expresion("centerlight");
	insertar_expresion("glasses");
	insertar_expresion("happy");
	insertar_expresion("leftlight");
	insertar_expresion("noglasses");
	insertar_expresion("normal");
	insertar_expresion("rightlight");
	insertar_expresion("sad");
	insertar_expresion("sleepy");
	insertar_expresion("surprised");
	insertar_expresion("wink");
}

String yalefaces::construir_path(int _sujeto, int _expresion) const{

	assert(_sujeto+1 > 0 && _sujeto+1 <= this->num_sujetos );
	assert(_expresion >= 0 && _expresion < this->expresiones.size());

  ostringstream conversor;

  if(_sujeto+1 < 10)
      conversor << "../res/yalefaces/subject0" << _sujeto+1 << "." << this->expresiones.at(_expresion) << ".png";
  else
      conversor << "../res/yalefaces/subject" << _sujeto+1 << "." << this->expresiones.at(_expresion) << ".png";

  return conversor.str();
}
