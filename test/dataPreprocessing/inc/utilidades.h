#ifndef __UTILIDADES__
#define __UTILIDADES__

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/**
*	@fn bool leeimagen(char* _filename, Mat& _imagen, unsigned int _flagColor = 0)
*	@brief Lee una imagen.
*	@param[in] _filename Path necesario para leer la imagen.
*	@param[in] _flagColor Si es 0 la almacena en escala de grises (1 canal).
*						 Si es 1 la almacena en color (3 canales).
*	@param[out] _imagen Objeto que contiene la imagen leida.
*	@returns Si se ha podido leer o no la imagen.
*/
bool leeimagen(char* _filename, Mat& _imagen, unsigned int _flagColor = 0);

/**
*	@fn bool leeimagen(String _filename, Mat& _imagen, unsigned int _flagColor = 0)
*	@brief Lee una imagen.
*	@param[in] _filename Path necesario para leer la imagen.
*	@param[in] _flagColor Si es 0 la almacena en escala de grises (1 canal).
*						 Si es 1 la almacena en color (3 canales).
*	@param[out] _imagen Objeto que contiene la imagen leida.
*	@returns Si se ha podido leer o no la imagen.
*/
bool leeimagen(String _filename, Mat& _imagen, unsigned int _flagColor = 0);

/**
*	@fn pintaI(const Mat& im, char* nombre_ventana = "imagen")
*	@brief Muestra una imagen por pantalla.
*	@param[in] im Objeto Mat que se desea mostrar.
*	@param[in] nombre_ventana Nombre que tendrá la ventana donde se muestra la imagen.
*	@details Internamente la imagen se convertirá a un formato que pueda ser representado por un monitor.
*/
void pintaI(const Mat& _imagen, const char* _nombre_ventana);

/**
*   @fn marcar_punto(Mat &img, Point2f pt, Scalar& color, int tam_pixel)
*/
void marcar_punto(Mat &img, Point2f pt, Scalar& color, int tam_pixel);

/**
*	@fn version_OpenCV()
*	@brief Muestra por pantalla la versión de OpenCV que se tiene instalada.
*/
void version_OpenCV();

#endif
