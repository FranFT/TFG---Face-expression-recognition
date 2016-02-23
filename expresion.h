#ifndef __CLASS_EXPRESION__
#define __CLASS_EXPRESION__

#include "utilidades.h"

#define NUM_SUJETOS 15

enum tipo_expresion{
	centerlight,
	glasses,
	happy,
	leftlight,
	noglasses,
	normal,
	rightlight,
	sad,
	sleepy,
	surprised,
	wink
};

class expresion{
private:
	vector<Mat> imagenes;
	vector<int> muestra_training;
	vector<int> muestra_test;
	tipo_expresion tipo;
	float size_training;
	int color;
	String ruta;
	String formato;
	String tipo_expresion2String(tipo_expresion _tipo);
public:
	expresion();
	expresion(tipo_expresion _tipo, float _size_training = 0.8);
	expresion(tipo_expresion _tipo, float _size_training = 0.8, String _ruta = "yalefaces/subject", String _formato = ".png");
	expresion(const expresion& obj);
	~expresion(){};
	bool cargar_expresion(tipo_expresion _tipo, bool _color = false, bool _salida = false);
};

#endif