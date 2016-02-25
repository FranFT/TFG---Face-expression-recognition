#ifndef __CLASS_EXPRESION__
#define __CLASS_EXPRESION__

#include <time.h>
#include <fstream>
#include <opencv2\objdetect\objdetect.hpp>
#include "utilidades.h"

#define NUM_SUJETOS 15
#define NUM_EXPRESIONES 11

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
	float size_training;
	bool color;
	bool salida;
	tipo_expresion tipo;
	Rect2i region_cara;

	vector<Mat> imagenes;
	vector<int> muestra_training;
	vector<int> muestra_test;

	String formato;
	String ruta;
	String ruta_clasificador_xml;
	String clasificador_defecto;

	String tipo_expresion2String(tipo_expresion _tipo);
	void generar_fichero_background_samples();
	void optimizar_region_cara(String xml_classifier);

public:
	expresion();
	expresion(tipo_expresion _tipo, float _size_training = 0.8, String _ruta = "yalefaces/subject", String _formato = ".png");
	expresion(const expresion& obj);
	~expresion(){};

	void set_salida_por_pantalla(bool _salida);
	void set_ruta_clasificador_xml(String _ruta);
	void set_clasificador_defecto(String _nombre);

	void print_muestras();
	void print_tipo_expresion();

	bool cargar_expresion(tipo_expresion _tipo, bool _color = false);
	bool generar_muestras(float _size_training);
};

#endif