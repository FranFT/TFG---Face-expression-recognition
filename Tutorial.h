#ifndef __TUTORIAL_CANNY__
#define __TUTORIAL_CANNY__

#include "utilidades.h"

//// Detecci�n de caracter�sticas
// Detector de bordes de Canny.
// http://docs.opencv.org/doc/tutorials/imgproc/imgtrans/canny_detector/canny_detector.html
//
Mat CannyThreshold(const Mat& img, double low_threshold, int kernel_size = 3, int ratio = 3);


// Ejecuta un peque�o ejemplo de uso del detector de Canny.
void tutorial();

#endif