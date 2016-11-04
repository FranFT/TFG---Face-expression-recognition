#include "douglasPeucker.h"
using namespace cv;

// Función que calcula la distancia de un punto _pt a la linea formada por 'l1' y 'l2'.
double distanciaPerpendicular(Point2i _pt, Point2i l1, Point2i l2){
	// Calculo el doble del área del triángulo formado por (_pt, l1, l2)
	double area = abs( ( ( l2.y - l1.y ) * _pt.x ) - ( ( l2.x - l1.x ) * _pt.y ) +
		(l2.x * l1.y) - (l2.y * l1.x) );
	
	// Divido el área de dicho triangulo entre la distancia entre 'l1' y 'l2'.
	return area / sqrt( ( ( l2.y - l1.y ) * ( l2.y - l1.y ) ) +
		( l2.x - l1.x ) * ( l2.x - l1.x ) );
}

// Función que implementa el algoritmo de Douglas Peucker.
// https://en.wikipedia.org/wiki/Ramer%E2%80%93Douglas%E2%80%93Peucker_algorithm
Mat douglasPeucker(Mat _puntos, double _epsilon){
	// Variables necesarias.
	double distancia_maxima = 0.0;
	double distancia_actual = 0.0;
	int indice = 0;
	Mat resultado;

	// Busco el punto a mayor distancia del segmento formado por los puntos extremos.
	for(int i = 1; i < _puntos.rows - 1; i++){
		distancia_actual = distanciaPerpendicular( _puntos.at<Vec2i>( i, 0 ), // Punto i-esimo.
			_puntos.at<Vec2i>( 0, 0 ), _puntos.at<Vec2i>( _puntos.rows - 1, 0 )); // Segmento.
		
		// Actualizo la distancia máxima.
		if( distancia_actual > distancia_maxima ){
			indice = i;
			distancia_maxima = distancia_actual;
		}
	}
	
	// Si la distancia máxima es mayor que el umbral se simplifica de forma recursiva.
	if( distancia_maxima > _epsilon ){
		Mat subMatriz1, subMatriz2;
		// Preparo la informacion para las llamadas recursivas. Para ello divido la lista de puntos por
		// el punto mas alejado. (El límite superior del rango de filas es exclusivo, por lo que se le
		// añade 1).
		subMatriz1.push_back( _puntos.rowRange( 0, indice + 1 ) );
		subMatriz2.push_back( _puntos.rowRange( indice, _puntos.rows ) );
	
		// Llamadas recursivas.
		Mat resultado1 = douglasPeucker(subMatriz1, _epsilon);	
		Mat resultado2 = douglasPeucker(subMatriz2, _epsilon);
		
		// Construyo el conjunto de puntos resultado.
		resultado.push_back( resultado1.rowRange( 0, resultado1.rows - 1 ) );
		resultado.push_back(resultado2);
	}
	// Si la distancia del punto es menor que el umbral (_epsilon)
	else{
		resultado.push_back( _puntos.row(0) );
		resultado.push_back( _puntos.row( _puntos.rows - 1 ) );
	}
	
	// Devuelvo la lista de puntos resultante.
	return resultado;
}// Fin del método 'douglasPeucker'.
