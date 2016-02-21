#include "Tutorial.h"

//// Detección de características
// Detector de bordes de Canny.
// http://docs.opencv.org/doc/tutorials/imgproc/imgtrans/canny_detector/canny_detector.html
//
Mat CannyThreshold(const Mat& img, double low_threshold, int kernel_size, int ratio)
{
	// Variables necesarias.
	Mat detected_edges;

	// Alisamos la imagen reduciendo el ruido y la guardamos en 'detected_edges'.
	blur(img, detected_edges, Size(kernel_size, kernel_size));

	// Aplicamos el detector de bordes de Canny
	// (http://docs.opencv.org/modules/imgproc/doc/feature_detection.html?highlight=canny#canny).
	Canny(detected_edges, detected_edges, low_threshold, low_threshold*ratio, kernel_size);

	return detected_edges;
}

void tutorial(){
	vector<Mat> imagenes_solucion;

	// Leo imagen.
	Mat prueba = leeimagen("yalefaces/subject01.png");

	// La añado al vector de imágenes solución.
	imagenes_solucion.push_back(prueba);

	// Aplico el detector de fronteras de Canny.
	prueba = CannyThreshold(prueba, 40);

	// Añado la imagen al vector de imágenes solución.
	imagenes_solucion.push_back(prueba);

	// Pinto las imágenes del vector.
	pintaMI(imagenes_solucion, "Canny Edge Detector");
}