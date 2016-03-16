#ifndef __CLASS_EXPRESION__
#define __CLASS_EXPRESION__

#include <time.h>
#include <fstream>
#include <opencv2\objdetect\objdetect.hpp>
#include "utilidades.h"

// Variables globales con las características de la base de datos Yalefaces.
#define NUM_SUJETOS 15
#define NUM_EXPRESIONES 11
#define SEMILLA_ALEATORIA 12345

// Tipo enumerado que facilita el acceso a los distintos tipos de expresión a través del código.
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

// Clase que gestiona la lectura de las imágenes y creación de los ficheros de muestras positivas y negativas
// que serán necesarios por las aplicaciones "opencv_createsamples.exe" y "opencv_traincascade.exe" para generar
// los ficheros requeridos para entrenar cada clasificador.
class expresion{
private:
	// Tamaño de la muestra de training dado como un porcentaje (0.0 - 1.0)
	double size_training;

	// Flag que indica si la imágenes serán leidas en color o en escala de grises.
	bool color;

	// Flag que activa las salidas por pantalla de resultados en las funciones donde se requieren.
	bool salida;

	// Expresión que contienen las imágenes leidas en una instancia de la clase 'expresión'.
	tipo_expresion tipo;

	// Región de la imagen donde se encuentra la cara dentro de cada imagen. Por defecto es el tamaño completo de la imagen.
	Rect2i region_cara_defecto;

	// Vector que contiene las imágenes leidas para una expresión dada.
	vector<Mat> imagenes;

	// Vector binario que indica si la imagen i-ésima del vector "imágenes" pertenece o no a la muestra de entrenamiento.
	vector<int> muestra_training;

	// Vector cuya entrada i-ésima define la región donde se encuentra la cara del sujeto en la imagen i-ésima.
	vector<Rect2i> region_cara;

	//// Conjunto de strings necesarios para crear los ficheros de muestras positivas y negativas con las que se entrenará el clasificador
	//// del tipo expresión en particular.
	// Formato del fichero de salida.
	String formato;

	// Path del directorio que contiene las imágenes.
	String ruta;

	// Path del directorio que contiene el clasificador de caras de OpenCV. (Usado para rellenar el vector "region_cara").
	String ruta_clasificador_xml;

	// Nombre del clasificador que se usará para detectar caras.
	String clasificador_defecto;

	// Función auxiliar que convierte un elemento del tipo 'tipo_expresion' en un String.
	String tipo_expresion2String(tipo_expresion _tipo);

	// Función que genera los ficheros de muestras positivas (samples\positive_samples\expresionX.info)
	// y negativas (samples\background_samples\bg_expresionX.txt).
	void generar_fichero_entrenamiento();

	// Función que detecta, con el clasificador de caras indicado como argumento, las regiones de cada imágen donde se
	// ha encontrado una cara.
	void optimizar_region_cara(String xml_classifier);

	// Función que genera de manera aleatoria las muestras de training y test.
	bool generar_muestras(double _size_training);

public:
	// Constructor por defecto.
	expresion();

	// Constructor con parámetros.
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

	// Muestra por pantalla la disposición de las muestras de training y test.
	void print_muestras();

	// Función que lee las imágenes de los sujetos que tienen una expresión facial concreta.
	// Asigna cada imagen leida a la muestra de training y test de manera aleatoria.
	// Genera los ficheros de muestras positivas y negativas de las imágenes que pertenecen a la muestra de training.
	// Puede indicarse como argumento que emplee el clasificador de OpenCV para detectar dónde se encuentra la cara
	// en cada una de las imágenes además de indicar si la base de datos es en color o en escala de grises.
	bool cargar_expresion(tipo_expresion _tipo, bool _optimizar_region, bool _color = false);
};

#endif