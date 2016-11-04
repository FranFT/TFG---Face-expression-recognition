#include <iostream>
#include <fstream>
#include <string>
#include <opencv2/opencv.hpp>
#include "douglasPeucker.h"

using namespace std;
using namespace cv;

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

// Programa principal.
int main( int argc, char** argv ){
	/***************************
	**	Variables necesarias	**
	***************************/
	const char* nombre_fichero = "../lib/STASM_handsSimplificado/tasm/shapes/hands.shape";
	Mat shapefile_points;
	
	
	/***************************
	**	Cuerpo de la función	**
	***************************/
	// Leo los puntos del fichero.
	shapefile_points = leerShapeFile( nombre_fichero );
	
	// Si no se han obtenido puntos se notifica el error.
	if(shapefile_points.empty()){
		cerr << "No se han podido extrar puntos del fichero: '" << nombre_fichero << "'." << endl;
		return 1;
	}	
	
	return 0;
}// Fin del método 'main'.
