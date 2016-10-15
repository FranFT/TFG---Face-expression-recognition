#include <iostream>
#include <opencv2/opencv.hpp>
#include "stasm4.1.0/stasm/stasm_lib.h"

cv::CascadeClassifier car_detector;
float puntos_extraidos[2*stasm_NLANDMARKS];

// Analiza una imagen tratando de identificar un vehículo.
void detect_car(cv::Mat& frame){
	// Variables necesarias.
	std::vector<cv::Rect> detecciones;
	cv::Mat gray_frame;
	
	// Preparo la imagen.
	cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY);
	cv::equalizeHist(gray_frame, gray_frame);
	
	// Uso el detector sobre la imagen.
	car_detector.detectMultiScale(
		gray_frame,
		detecciones,
		1.5,
		3,
		0|cv::CASCADE_SCALE_IMAGE,
		cv::Size(30,30));
		
		// Si se han detectado objetos.
		if(detecciones.size() > 0){
			// Busco el rectángulo de mayor tamaño. Para evitar errores provocados por la simplez del
			// detector, el rectángulo debe ser más ancho que el 50% del frame capturado.
			bool encontrado = false;
			int maxSize = 0;
			for(size_t i=0; i < detecciones.size(); i++)
				if(detecciones[i].width >= frame.size().width*0.5){
					encontrado = true;
					if(detecciones[i].width > detecciones[maxSize].width)
						maxSize = i;
				}
			
			if(encontrado){
				std::cout << "Coche encontrado...";
				cv::rectangle(frame, detecciones[maxSize], cv::Scalar(0,0,255), 4);
				int face_found;
				cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY);
				if(!stasm_search_single(
					&face_found,
					puntos_extraidos,
					(char*)gray_frame.data,
					gray_frame.size().width,
					gray_frame.size().height,
					"path_prueba",
					"../data")){
						std::cout << "Puntos no encontrados" << std::endl;
					}
			}
			

			//std::cout << detecciones[0] << std::endl;
			//cv::rectangle(frame, detecciones[0], cv::Scalar(0,0,255), 4);
		}
}

/*void detect_car(cv::Mat& frame){
	int face_found;

	if(stasm_search_single(
		&face_found,
		puntos_extraidos,
		(char*)frame.data,
		frame.cols,
		frame.rows,
		"/pos",
		"../data")){
			std::cout << "Puntos encontrados" << std::endl;
		}

}*/

// Programa principal.
int main(int argc, char** argv){

	// Abrimos el dispositivo de video por defecto.
	cv::VideoCapture camera(0);
	if(!camera.isOpened()){
		std::cerr << "No se ha podido abrir la video-cámara.\n";
		return -1;
	}
	
	if(!car_detector.load("../data/cascade.xml")){
		std::cerr << "No se ha podido abrir el clasificador.\n";
		return -1;
	}
	
	// Mientras nos se presione Esc, capturamos frames.
	while(true){
		cv::Mat frame;
		camera >> frame;
		
		detect_car(frame);

		cv::imshow("video stream", frame);
		if(cv::waitKey(30) >= 0)
			break;
	}
	
	return 0;
}
