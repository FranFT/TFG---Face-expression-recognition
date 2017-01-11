#include "utilidades.h"

bool leeimagen(char* _filename, Mat& _imagen, unsigned int _flagColor){
	_imagen = imread(_filename, _flagColor);

	if(!_imagen.data)
		return false;
	else
		return true;
}

bool leeimagen(String _filename, Mat& _imagen, unsigned int _flagColor){
	_imagen = imread(_filename, _flagColor);

	if(!_imagen.data)
		return false;
	else
		return true;
}

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
}

void marcar_punto(Mat &img, Point2f pt, Scalar& color, int tam_pixel){
	// Se comprueba que el punto tiene valores correctos.
	if (pt.x >= 0 && pt.y >= 0){
		// Dibuja la cruz en el punto pt.
		line(img, pt - Point2f(0, tam_pixel), pt + Point2f(0, tam_pixel), color);
		line(img, pt - Point2f(tam_pixel, 0), pt + Point2f(tam_pixel, 0), color);
		/*line(img, pt - Point2f(0, tam_pixel), pt + Point2f(0, tam_pixel), color);
		line(img, pt - Point2f(tam_pixel, 0), pt + Point2f(tam_pixel, 0), color);*/
	}
}

void version_OpenCV(){
	cout << "OpenCV version : " << CV_VERSION << endl;
	cout << "Major version : " << CV_MAJOR_VERSION << endl;
 	cout << "Minor version : " << CV_MINOR_VERSION << endl;
	cout << "Subminor version : " << CV_SUBMINOR_VERSION << endl;
}
