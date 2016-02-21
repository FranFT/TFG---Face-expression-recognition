#include "utilidades.h"

Mat leeimagen(char* filename, int flagColor){
	return imread(filename, flagColor);
}

void pintaI(const Mat& im, char* nombre_ventana){
	if (!im.empty()){
		Mat im_copia = Mat(im);
		im_copia.convertTo(im_copia, CV_8U);

		namedWindow(nombre_ventana, 1);
		imshow(nombre_ventana, im_copia);
		waitKey();
		destroyWindow(nombre_ventana);
	}
}

void pintaMI(const vector<Mat> &imagenes_solucion, char* nombre){
	// Variables necesarias.
	int tam_ventana_rows = 0;
	int tam_ventana_cols = 0;
	int x_inicio = 0;
	bool color = false;
	Mat solucion, roi, aux;
	vector<Mat>::const_iterator it;

	// Calculo el valor de la imagen que contrendrá el conjunto de imágenes solución.
	for (it = imagenes_solucion.begin(); it != imagenes_solucion.end(); it++){
		tam_ventana_cols = tam_ventana_cols + (*it).cols;
		if (tam_ventana_rows < (*it).rows)
			tam_ventana_rows = (*it).rows;

		// Indico si hay imágenes en color.
		if ((*it).channels() == 3)
			color = true;
	}

	if (color)
		solucion = Mat(tam_ventana_rows, tam_ventana_cols, CV_8UC3);
	else
		solucion = Mat(tam_ventana_rows, tam_ventana_cols, CV_8UC1);

	for (it = imagenes_solucion.begin(); it != imagenes_solucion.end(); it++){

		// Defino dónde se situará la imagen en la matriz solución.
		roi = Mat(solucion, Rect(x_inicio, 0, (*it).cols, (*it).rows));

		// Si la matriz solución está definida para imágenes en color y encontramos
		// una imagen en escala de grises, la convertimos.
		if (color == true && (*it).channels() == 1){
			aux = (*it).clone();
			aux.convertTo(aux, CV_8U);
			cvtColor(aux, aux, COLOR_GRAY2RGB);
			aux.copyTo(roi);
		}
		else
		{
			aux = (*it).clone();
			aux.convertTo(aux, CV_8U);
			aux.copyTo(roi);
		}

		// Actualizo la posición de inicio de la región de interés.
		x_inicio = x_inicio + aux.cols;
	}

	pintaI(solucion, nombre);
}

void pintaMI(const vector<vector<Mat> > &imagenes_solucion, char* nombre){
	int tam_ventana_rows = 0;
	int tam_ventana_cols = 0;
	bool color = false;
	int x_inicio = 0;
	int aux_x = 0;
	int aux_y = 0;

	vector<vector<Mat> >::const_iterator it_filas;
	vector<Mat>::const_iterator it_columnas;
	vector<int>::const_iterator it;
	vector<int> y_inicio;
	Mat solucion, roi, aux;


	y_inicio.push_back(0);

	for (it_filas = imagenes_solucion.begin(); it_filas != imagenes_solucion.end(); ++it_filas){

		aux_x = 0;
		aux_y = 0;

		for (it_columnas = (*it_filas).begin(); it_columnas != (*it_filas).end(); ++it_columnas){
			aux_x = aux_x + (*it_columnas).cols;

			if (aux_y < (*it_columnas).rows)
				aux_y = (*it_columnas).rows;

			if ((*it_columnas).channels() == 3)
				color = true;
		}

		if (aux_x > tam_ventana_cols)
			tam_ventana_cols = aux_x;

		tam_ventana_rows += aux_y;
		y_inicio.push_back(aux_y);
	}


	if (color)
		solucion = Mat(tam_ventana_rows, tam_ventana_cols, CV_8UC3);
	else
		solucion = Mat(tam_ventana_rows, tam_ventana_cols, CV_8UC1);

	for (it_filas = imagenes_solucion.begin(), it = y_inicio.begin(); it_filas != imagenes_solucion.end(); ++it_filas, ++it){

		x_inicio = 0;

		for (it_columnas = (*it_filas).begin(); it_columnas != (*it_filas).end(); ++it_columnas){

			roi = Mat(solucion, Rect(x_inicio, (*it), (*it_columnas).cols, (*it_columnas).rows));

			if (color == true && (*it_columnas).channels() == 1){
				aux = (*it_columnas).clone();
				aux.convertTo(aux, CV_8U);
				cvtColor(aux, aux, COLOR_GRAY2RGB);
				aux.copyTo(roi);
			}
			else{
				aux = (*it_columnas).clone();
				aux.convertTo(aux, CV_8U);
				aux.copyTo(roi);
			}

			x_inicio = x_inicio + (*it_columnas).cols;
		}
	}

	pintaI(solucion, nombre);
}