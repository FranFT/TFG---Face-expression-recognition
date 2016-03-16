#ifndef __CLASS_EXPRESION__
#define __CLASS_EXPRESION__

#include <time.h>
#include <fstream>
#include <opencv2\objdetect\objdetect.hpp>
#include "utilidades.h"

#define NUM_SUJETOS 15
#define NUM_EXPRESIONES 11
#define SEMILLA_ALEATORIA 12345

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
	double size_training;
	bool color;
	bool salida;
	tipo_expresion tipo;
	Rect2i region_cara_defecto;

	vector<Mat> imagenes;
	vector<int> muestra_training;
	vector<Rect2i> region_cara;

	String formato;
	String ruta;
	String ruta_clasificador_xml;
	String clasificador_defecto;

	String tipo_expresion2String(tipo_expresion _tipo);
	void generar_fichero_entrenamiento();
	void optimizar_region_cara(String xml_classifier);

public:
	expresion();
	expresion(tipo_expresion _tipo, double _size_training = 0.8, String _ruta = "yalefaces/subject", String _formato = ".png");
	~expresion(){};

	expresion& operator=(const expresion& obj);

	void set_salida_por_pantalla(bool _salida);
	void set_ruta_clasificador_xml(String _ruta);
	void set_clasificador_defecto(String _nombre);
	String get_clasificador_defecto();

	void print_muestras();
	void print_tipo_expresion();

	bool cargar_expresion(tipo_expresion _tipo, bool _optimizar_region, bool _color = false);
	bool generar_muestras(double _size_training);
};

#endif