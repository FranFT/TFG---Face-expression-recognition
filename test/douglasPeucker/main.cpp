#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define ANCHO 650
#define ALTO 400
#define NUM_PUNTOS 50
#define MARGEN_EJE_Y 50

// Función que pinta por pantalla una imagen.
void pintaI(const Mat& _imagen, const char* _nombre_ventana){
	if(!_imagen.empty()){
		namedWindow(_nombre_ventana, WINDOW_AUTOSIZE);

		if(_imagen.type() != CV_8U){
			Mat imagen_copia = Mat(_imagen);
			imagen_copia.convertTo(imagen_copia, CV_8U);
			imshow(_nombre_ventana, imagen_copia);
		}
		else{
			imshow(_nombre_ventana, _imagen);
		}

		waitKey(0);
		destroyWindow(_nombre_ventana);
	}
	else{
		cerr << "ERROR: No se puede mostrar una imagen vacia." << endl;
	}
}// Fin método 'pintaI'.

// Función que dada una coordenada X, obtiene una coordenada Y aplicando una función seno:
double obtenerY(double x){
	return (sin(x) * ALTO/2) + ALTO/2;
}

// Devuelve una matriz de puntos 2D que definen la curva que se desea simplificar.
Mat cargar_curva(){
	// Variables necesarias.
	Mat salida = Mat(NUM_PUNTOS, 1, CV_32SC2);
	double factor = ANCHO / NUM_PUNTOS;
	
	// Inserto los puntos.
	for(int i = 0; i < salida.rows; i++){
		int coordenadaX = i * factor;
		salida.at<Vec2i>(i,0)[0] = coordenadaX;
		salida.at<Vec2i>(i,0)[1] = static_cast<int>(obtenerY(coordenadaX));
	}// Fin for.
	
	//cout << salida;

	return salida;
}// Fin del método 'cargar_curva'.

// Pinta una curva en una imagen dada.
void pintar_curva(Mat& _canvas, const Mat& _curva, Scalar color){	
	// Pinto el primer punto.
	circle( _canvas, _curva.at<Vec2i>(0,0), 1, Scalar(0,0,255), 2 );
	// Pinto el resto y los uno con una linea.
	for(int i = 1; i < _curva.rows; i++){
		line( _canvas, _curva.at<Vec2i>(i-1,0), _curva.at<Vec2i>(i,0), color, 1);
		circle( _canvas, _curva.at<Vec2i>(i,0), 2, Scalar(0, 0, 255), 2 );	
	}// Fin for.

}// Fin del método 'pintar_curva'.

Mat cargar_canvas(){
	// Creo el canvas en negro.
	Mat salida = Mat::zeros(ALTO, ANCHO, CV_8UC3);
	Scalar color_eje = Scalar(200, 200, 200);
	
	// Pinto los ejes.
	// Eje X.
	line(salida, Point2i( 0, ALTO / 2 ), Point2i( ANCHO - 1, ALTO / 2 ), color_eje, 1);
	// Eje Y.
	line(salida, Point2i(MARGEN_EJE_Y, 0), Point2i( MARGEN_EJE_Y, ALTO - 1 ), color_eje, 1);
	
	return salida;
}// Fin del método 'cargar_canvas'.

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
Mat douglasPeucker(Mat _puntos, double _epsilon = 5.0){
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

// Programa principal.
int main(int argc, char** argv){
	/***************************
	**	Variables necesarias	**
	***************************/
	Mat curva, curva_simplificada;
	Mat canvas;
	
	/*********************
	**	Cuerpo del main	**
	**********************/
	// Canvas donde dibujar la curva.
	canvas = cargar_canvas();
	
	// Genero los puntos mediante la función 'seno'.
	curva = cargar_curva();
	
	// Simplifico la curva con el algoritmo de douglasPeucker.
	curva_simplificada = douglasPeucker(curva, 50.0);
	
	// Visualizo la curva simplificada
	pintar_curva(canvas, curva, Scalar(0, 0, 255));
	pintar_curva(canvas, curva_simplificada, Scalar(255, 255, 0));
	pintaI(canvas, "Curva simplificada");	


	return 0;
}// Fin del método 'main'.
