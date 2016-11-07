#include <iostream>
#include <fstream>
#include <string>
#include <opencv2/opencv.hpp>
#include "douglasPeucker.h"

using namespace std;
using namespace cv;

// Inserta el punto de coordenadas X,Y de _linea en la posición de la matriz: _puntos(_fila, _col).
void insertar_punto( const string& _linea, Mat& _puntos, const int _fila, const int _col ){
	/***************************
	**	Variables necesarias	**
	***************************/
	int i = 0;
	string coordX, coordY;
	
	/***************************
	**	Cuerpo de la función	**
	***************************/
	// Extraigo el primer número.
	for(i = 0; _linea[i] != ' '; i++)
		coordX += _linea[i];
		
	// Salto los espacios en blanco.
	while( _linea[i] == ' ' )
		i++;
	
	// Extraigo el segundo número.		
	for(; i < _linea.length(); i++)
		coordY += _linea[i];
		
	// Inserto los números en la matriz.
	_puntos.at<Vec2f>( _fila, _col )[0] = stof( coordX );
	_puntos.at<Vec2f>( _fila, _col )[1] = stof( coordY );
}// Fin del método 'insertar_punto'.

// Devuelve los puntos contenidos en un shapefile de la librería STASM como una matriz donde la
// fila i-esima y columna j-esima indican el punto i-esimo de la entrada j-esima.
// El vector devuelto estaŕa vacío en caso de que ocurra algún error durante el proceso.
Mat leerShapeFile( const char* _filename ){
	/***************************
	**	Variables necesarias	**
	***************************/
	int i = 0;
	int num_muestras = 0;
	Mat puntos;
	ifstream shapefile;
	string linea, num_pts;
	
	/***************************
	**	Cuerpo de la función	**
	***************************/
	// Abro el fichero.
	shapefile.open( _filename );
	
	if( !shapefile.is_open() )
		return puntos;
	
	// Busco la primera entrada y la contabilizo.
	while( linea[0] != '{' )
		getline( shapefile, linea );
	num_muestras++;
	
	// Obtengo el número de puntos que tiene cada entrada.		
	for( i = 2; linea[i] != ' '; i++ )
		num_pts += linea[i];
	
	// Cuento el número total de entradas.
	while( getline( shapefile, linea ) )
		if( linea[0] == '{' )
			num_muestras++;
			
	// Reservo memoria para los puntos de cada entrada.
	puntos = Mat( stoi( num_pts ), num_muestras, CV_32FC2 );
	
	// Vuelvo al comienzo del fichero.
	shapefile.clear();
	shapefile.seekg( 0, ios::beg );
		
	// Recorro el fichero y relleno la matriz de puntos.
	num_muestras = 0; // Indicará la columna donde insertar los puntos.
	while( getline( shapefile, linea ) ){
		// Cuando encontramos un bloque de puntos se inserta en la columna correspondiente.
		if( linea[0] == '{' ){
			for( i = 0; i < puntos.rows; i++ ){
				getline( shapefile, linea );
				insertar_punto( linea, puntos, i, num_muestras );
			}
			// Incremento para insertar en la siguiente columna.
			num_muestras++;
		}
	}		
	// Cierro el fichero.
	shapefile.close();

	return puntos;
}// Fin del método 'leerShapeFile'.

/**
* Función que selecciona los puntos utilizables tras la simplificación. Para ello, aplica el
* algoritmo de Douglas Peucker a todas las entradas y selecciona aquella que mantiene MÁS puntos
* tras la simplificación.
*	Se devuelven los índices de los puntos utilizables según esta simplificación. En caso de error en 
* el proceso se devuelve el vector vacío.
**/
vector<int> obtener_indices(const Mat& _puntos, const double _epsilon){
	/***************************
	**	Variables necesarias	**
	***************************/
	int indice = 0; // Indice de la entrada con el mayor número de puntos tras la simplificación.
	int numPuntos = 0;	// Variable usada para calcular el máximo.
	int maxPuntos = 0;	// Variable usada para calcular el máximo.
	vector<int> indices;
	Mat puntos_simplificados;
	
	/***************************
	**	Cuerpo de la función	**
	***************************/
	// Obtengo la entrada que mantiene más puntos tras la simplificación.
	for( int i = 0; i < _puntos.cols; i++ ){
		numPuntos = douglasPeucker( _puntos.col( i ), _epsilon ).rows;
		if( numPuntos > maxPuntos ){
			maxPuntos = numPuntos;
			indice = i;
		}
	}
	
	// Almaceno la simplificación de puntos con mayor número de puntos.
	puntos_simplificados = douglasPeucker( _puntos.col( indice ), _epsilon );
	
	// Busco y almaceno los índices de puntos que estan antes y después de la simplificación.
	for( int i = 0, j = 0; i < _puntos.rows; i++ ){
		if( _puntos.at<Vec2f>( i, indice ) == puntos_simplificados.at<Vec2f>( j, 0 ) ){
			indices.push_back( i );
			j++;
		}
	}
	
	// Si el número de índices encontrados no coincide con el número de puntos tras la simplificación
	// se devuelve el vector vacío como signo de error.
	if( indices.size() != puntos_simplificados.rows )
		indices.clear();
		
	return indices;	
}// Fin del método 'obtener_indices'.

// Función que obtiene los nombres de imágenes necesarios para crear el shapefile.
vector<string> obtenerNombresImagenes(const char* _filename){
	/***************************
	**	Variables necesarias	**
	***************************/
	ifstream shapefile;
	streampos posicion_actual, posicion_anterior;
	string linea, nombre_imagen;
	vector<string> salida;
	bool exito = true;
	bool repetida = false;
	
	/***************************
	**	Cuerpo de la función	**
	***************************/
	// Abro el fichero.
	shapefile.open( _filename );
	
	if( !shapefile.is_open() )
		return salida;
	
	// Almaceno la posición de la linea actual.
	posicion_actual = shapefile.beg;
	
	// Hasta el final del fichero o en caso de error.
	while(getline( shapefile, linea ) && exito){
		// Si no obtengo el caracter '{' al comienzo de la linea actualizo la posición de la linea anterior.
		if( linea[0] != '{' ){
			posicion_anterior = posicion_actual;
			posicion_actual = shapefile.tellg();
		}
		// Si me encuentro una linea con '{' y no es repetida.
		else if( !repetida ){
			// Leo la linea anterior.
			shapefile.seekg( posicion_anterior );
			getline( shapefile, linea );
			
			// Almaceno todo aquello tras el espacio en blanco.
			size_t encontrado = linea.find_first_of(' ');
			if( encontrado != string::npos ){
				for(encontrado = encontrado + 1; encontrado != linea.length(); encontrado++)
					nombre_imagen += linea[encontrado];
			
				salida.push_back( nombre_imagen );
				nombre_imagen.clear();
				
				// Vuelvo a la linea y la marco como repetida, para que en la siguiente iteración se ignore.
				shapefile.seekg( posicion_actual );
				repetida = true;
			}
			else{
				exito = false;
			}
		}
		// Si la linea es repetida desactivo ese flag.
		else if( repetida ){
			repetida = false;
		}
	}
	
	// Si algo ha fallado durante el proceso se devuelve el vector vacío.
	if( !exito )
		salida.clear();
	
	return salida;
}// Fin del método 'obtenerNombresImagenes'.


// Función que escribe el shape file de puntos simplificados.
bool generarShapefile(
	const Mat& _puntos,
	const vector<int>& _indices,
	const vector<string> _nombres_imagenes ){
	/***************************
	**	Variables necesarias	**
	***************************/
	const char* nombre_fichero = "handsSimplificado.shape";
	ofstream fichero_salida;

	
	/***************************
	**	Cuerpo de la función	**
	***************************/
	// Abro el fichero descartando el contenido actual.
	fichero_salida.open( nombre_fichero, ios::trunc );
	
	if( !fichero_salida.is_open() )
		return false;
	
	// Comienzo a escribir en el fichero.
	// Escribo la cabecera.
	fichero_salida << "shape " << nombre_fichero << endl << endl <<
	"# Change the following to the location of your hand images\n" <<
	"Directories /home/fran/Dropbox/TFG---Face-expression-recognition/res/Hands/images\n" << endl;
	
	// Después de la cabecera comienzo a escribir los puntos.
	for( int i = 0; i < _puntos.cols; i++ ){
		fichero_salida << "00000000 " << _nombres_imagenes.at(i) << endl <<
		"{ " << _indices.size() << " 2" << endl;

		for( int j = 0; j < _indices.size(); j++ ){
			fichero_salida <<
			static_cast<float>(_puntos.at<Vec2f>( _indices.at(j), i )[0]) << " " <<
			static_cast<float>(_puntos.at<Vec2f>( _indices.at(j), i )[1]) << endl;
		}
		fichero_salida << "}" << endl;
		
	}
		
	fichero_salida.close();
	
	return true;
}// Fin del método 'generarShapefile'.

// Programa principal.
int main( int argc, char** argv ){
	/***************************
	**	Variables necesarias	**
	***************************/
	const char* nombre_fichero = "../lib/STASM_handsSimplificado/tasm/shapes/hands.shape";
	const double epsilon = 100.0; // Parámetro del algoritmo de Douglas Peucker.
	Mat shapefile_points; // Matriz donde se leen los puntos del fichero.
	vector<int> puntos_utilizables; // Indices de los puntos utilizables tras la simplificación.
	vector<string> nombre_imagenes; // Nombres de las imagenes utilizadas en el fichero.
	
	/***************************
	**	Cuerpo de la función	**
	***************************/
	// Leo los puntos del fichero.
	shapefile_points = leerShapeFile( nombre_fichero );
	if( shapefile_points.empty() ){
		cerr << "No se han podido extrar puntos del fichero: '" << nombre_fichero << "'." << endl;
		return 1;
	}
	
	// Obtengo los índices de los puntos utilizables.
	puntos_utilizables = obtener_indices( shapefile_points, epsilon );
	if( puntos_utilizables.empty() ){
		cerr << "Error en el método 'obtener_indices()'" << endl;
		return 1;	
	}
		
	// Obtengo el nombre de los índices de las imágenes del shapefile.
	nombre_imagenes = obtenerNombresImagenes( nombre_fichero );
	if( nombre_imagenes.empty() ){
		cerr << "Error en el método 'obtenerNombresImagenes()'" << endl;
		return 1;	
	}
	
	// Genero el shapefile.
	if( !generarShapefile( shapefile_points, puntos_utilizables, nombre_imagenes ) ){
		cerr << "No se pudo generar el shapefile." << endl;
		return 1; 
	}
		
	return 0;
}// Fin del método 'main'.




