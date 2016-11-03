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
	return (sin(x) * ALTO/2) + ALTO/2;;
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
void pintar_curva(Mat& _canvas, const Mat& _curva){	
	// Pinto el primer punto.
	circle( _canvas, _curva.at<Vec2i>(0,0), 1, Scalar(0,0,255), 2 );
	// Pinto el resto y los uno con una linea.
	for(int i = 1; i < NUM_PUNTOS; i++){
		line( _canvas, _curva.at<Vec2i>(i-1,0), _curva.at<Vec2i>(i,0), Scalar(255, 255, 255), 1 );
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

// Programa principal.
int main(int argc, char** argv){
	/***************************
	**	Variables necesarias	**
	***************************/
	Mat curva;
	Mat canvas;
	
	/*********************
	**	Cuerpo del main	**
	**********************/
	canvas = cargar_canvas();
	curva = cargar_curva();
	pintar_curva(canvas, curva);
	pintaI(canvas, "canvas");


	return 0;
}// Fin del método 'main'.
