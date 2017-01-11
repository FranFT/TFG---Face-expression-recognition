#ifndef __EXPRESION_H__
#define __EXPRESION_H__

#include "sujeto.h"
#include "infoBaseDatos.h"

class Expresion{
private:
	const infoBaseDatos *base_datos;
	const double *puntos_referencia;	
	unsigned int tipo_expresion;
	Sujeto *sujetos;


public:
	Expresion();
	Expresion(unsigned int _tipo, infoBaseDatos *_base_datos, double *_puntos);
	~Expresion();
};

#endif //__EXPRESION_H__