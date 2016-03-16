#ifndef __CLASS_EXPRESION__
#define __CLASS_EXPRESION__

#include <time.h>
#include <fstream>
#include <opencv2\objdetect\objdetect.hpp>
#include "utilidades.h"

// Variables globales con las caracter�sticas de la base de datos Yalefaces.
#define NUM_SUJETOS 15
#define NUM_EXPRESIONES 11
#define SEMILLA_ALEATORIA 12345

// Tipo enumerado que facilita el acceso a los distintos tipos de expresi�n a trav�s del c�digo.
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

// Clase que gestiona la lectura de las im�genes y creaci�n de los ficheros de muestras positivas y negativas
// que ser�n necesarios por las aplicaciones "opencv_createsamples.exe" y "opencv_traincascade.exe" para generar
// los ficheros requeridos para entrenar cada clasificador.
class expresion{
private:
	// Tama�o de la muestra de training dado como un porcentaje (0.0 - 1.0)
	double size_training;

	// Flag que indica si la im�genes ser�n leidas en color o en escala de grises.
	bool color;

	// Flag que activa las salidas por pantalla de resultados en las funciones donde se requieren.
	bool salida;

	// Expresi�n que contienen las im�genes leidas en una instancia de la clase 'expresi�n'.
	tipo_expresion tipo;

	// Regi�n de la imagen donde se encuentra la cara dentro de cada imagen. Por defecto es el tama�o completo de la imagen.
	Rect2i region_cara_defecto;

	// Vector que contiene las im�genes leidas para una expresi�n dada.
	vector<Mat> imagenes;

	// Vector binario que indica si la imagen i-�sima del vector "im�genes" pertenece o no a la muestra de entrenamiento.
	vector<int> muestra_training;

	// Vector cuya entrada i-�sima define la regi�n donde se encuentra la cara del sujeto en la imagen i-�sima.
	vector<Rect2i> region_cara;

	//// Conjunto de strings necesarios para crear los ficheros de muestras positivas y negativas con las que se entrenar� el clasificador
	//// del tipo expresi�n en particular.
	// Formato del fichero de salida.
	String formato;

	// Path del directorio que contiene las im�genes.
	String ruta;

	// Path del directorio que contiene el clasificador de caras de OpenCV. (Usado para rellenar el vector "region_cara").
	String ruta_clasificador_xml;

	// Nombre del clasificador que se usar� para detectar caras.
	String clasificador_defecto;

	// Funci�n auxiliar que convierte un elemento del tipo 'tipo_expresion' en un String.
	String tipo_expresion2String(tipo_expresion _tipo);

	// Funci�n que genera los ficheros de muestras positivas (samples\positive_samples\expresionX.info)
	// y negativas (samples\background_samples\bg_expresionX.txt).
	void generar_fichero_entrenamiento();

	// Funci�n que detecta, con el clasificador de caras indicado como argumento, las regiones de cada im�gen donde se
	// ha encontrado una cara.
	void optimizar_region_cara(String xml_classifier);

	// Funci�n que genera de manera aleatoria las muestras de training y test.
	bool generar_muestras(double _size_training);

public:
	// Constructor por defecto.
	expresion();

	// Constructor con par�metros.
	expresion(tipo_expresion _tipo, double _size_training = 0.8, String _ruta = "yalefaces/subject", String _formato = ".png");

	// Destructor.
	~expresion(){};

	// Habilita la salida por pantalla de resultados intermedios.
	void set_salida_por_pantalla(bool _salida);

	// Sirve para cambiar la ruta del directorio que contiene el clasificador de OpenCV si es necesario.
	void set_ruta_clasificador_xml(String _ruta);

	// Sirve para cambiar el nombre del clasificador de OpenCV si es necesario.
	void set_clasificador_defecto(String _nombre);

	// Sirve para obtener el clasificador por defecto.
	String get_clasificador_defecto();

	// Muestra por pantalla la disposici�n de las muestras de training y test.
	void print_muestras();

	// Funci�n que lee las im�genes de los sujetos que tienen una expresi�n facial concreta.
	// Asigna cada imagen leida a la muestra de training y test de manera aleatoria.
	// Genera los ficheros de muestras positivas y negativas de las im�genes que pertenecen a la muestra de training.
	// Puede indicarse como argumento que emplee el clasificador de OpenCV para detectar d�nde se encuentra la cara
	// en cada una de las im�genes adem�s de indicar si la base de datos es en color o en escala de grises.
	bool cargar_expresion(tipo_expresion _tipo, bool _optimizar_region, bool _color = false);
};

#endif