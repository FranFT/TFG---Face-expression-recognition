/*!	@file	utilidades.h
	@brief	Fichero que contiene un conjunto de funciones básicas auxiliares.
*/
#ifndef __UTILIDADES__
#define __UTILIDADES__

#include <iostream>
#include <opencv2\opencv.hpp>

using namespace cv;
using namespace std;

/**
*	@fn Mat leeimagen(char* filename, int flagColor = 0)
*	@brief Lee una imagen.
*	@param[in] filename Path necesario para leer la imagen.
*	@param[in] flagColor Si es 0 la almacena en escala de grises (1 canal). 
*						 Si es 1 la almacena en color (3 canales).
*	@returns La imagen se almacena en un objeto de tipo Mat y se devuelve.
*/
Mat leeimagen(char* filename, int flagColor = 0);

/**
*	@fn Mat leeimagen(String filename, int flagColor = 0)
*	@brief Lee una imagen.
*	@param[in] filename Path necesario para leer la imagen.
*	@param[in] flagColor Si es 0 la almacena en escala de grises (1 canal).
*						 Si es 1 la almacena en color (3 canales).
*	@returns La imagen se almacena en un objeto de tipo Mat y se devuelve.
*/
Mat leeimagen(String filename, int flagColor = 0);

/**
*	@fn pintaI(const Mat& im, char* nombre_ventana = "imagen")
*	@brief Muestra una imagen por pantalla.
*	@param[in] im Objeto Mat que se desea mostrar.
*	@param[in] nombre_ventana Nombre que tendrá la ventana donde se muestra la imagen.
*	@details Internamente la imagen se convertirá a un formato que pueda ser representado por un monitor.
*/
void pintaI(const Mat& im, char* nombre_ventana = "imagen");

/**
*	@fn void pintaMI(const vector<Mat> &imagenes_solucion, char* nombre = "solucion")
*	@brief Muestra un conjunto de imágenes por pantalla.
*	@param[in] imagenes_solucion Conjunto de objetos Mat (imágenes) a ser mostradas.
*	@param[in] nombre Nombre que tendrá la ventana donde se muestran las imágenes.
*	@details Se mostrará el conjunto de imágenes concatenadas en una sola ventana.
*/
void pintaMI(const vector<Mat> &imagenes_solucion, char* nombre = "solucion");

/**
*	@fn void pintaMI(const vector<vector<Mat> > &imagenes_solucion, char* nombre = "solucion")
*	@brief Muestra una matriz de imágenes por pantalla.
*	@param[in] imagenes_solucion Matriz de objetos Mat (imágenes) a ser mostradas.
*	@param[in] nombre Nombre que tendrá la ventana donde se muestran las imágenes.
*	@details Se mostrará en una misma ventana, el conjunto de imágenes concatenadas, distribuyéndolas por filas en la pantalla si pertenencen al mismo contenedor.
*/
void pintaMI(const vector<vector<Mat> > &imagenes_solucion, char* nombre = "solucion");

#endif