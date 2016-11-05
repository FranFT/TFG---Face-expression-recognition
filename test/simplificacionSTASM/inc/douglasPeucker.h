#ifndef __DOUGLASPEUCKER_H__
#define __DOUGLASPEUCKER_H__

#include <opencv2/opencv.hpp>

// Función que calcula la distancia de un punto _pt a la linea formada por 'l1' y 'l2'.
double distanciaPerpendicular(cv::Point2i _pt, cv::Point2i l1, cv::Point2i l2);

// Función que implementa el algoritmo de Douglas Peucker.
// https://en.wikipedia.org/wiki/Ramer%E2%80%93Douglas%E2%80%93Peucker_algorithm
cv::Mat douglasPeucker(cv::Mat _puntos, double _epsilon);

#endif //__DOUGLASPEUCKER_H__
