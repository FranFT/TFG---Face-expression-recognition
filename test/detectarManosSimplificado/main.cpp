#include <iostream>
#include <opencv2/opencv.hpp>
#include "stasm_lib.h"

#define MAX_IMAGENES 100

cv::CascadeClassifier hand_detector;

// Analiza una imagen tratando de identificar un vehículo.
bool detect_hand(cv::Mat& frame){
	// Variables necesarias.
	float puntos_extraidos[2*stasm_NLANDMARKS];
	std::vector<cv::Rect> detecciones;
	cv::Mat gray_frame;
	int salida = false;
	
	// Preparo la imagen.
	cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY);

	
	// Uso el detector sobre la imagen. Me aseguro de detectar rectángulos mayores de la mitad de la
	// imagen.
	hand_detector.detectMultiScale(
		gray_frame,
		detecciones,
		1.5,
		3,
		0|cv::CASCADE_SCALE_IMAGE,
		frame.size()/2,
		frame.size());
		
	// Si se han detectado objetos.
	if(detecciones.size() > 0){
		int mano_encontrada;
		std::cout << "Mano encontrada en "<< detecciones[0] << std::endl;
		cv::rectangle(frame, detecciones[0], cv::Scalar(0,0,255), 4);			
		
		if(!stasm_search_single(
			&mano_encontrada,
			puntos_extraidos,
			(char*)gray_frame.data,
			gray_frame.size().width,
			gray_frame.size().height,
			"path_prueba",
			"../data")){
				std::cout << "Puntos no encontrados" << std::endl;
		}
		else{
			salida = true;
			
			cv::Point2f p1, p2;
			p1 = cv::Point2f(puntos_extraidos[0],puntos_extraidos[1]);
			cv::circle(frame, p1, 1, cv::Scalar(0,255,0), 3);
			
			
			for(int i=2; i<stasm_NLANDMARKS*2; i+=2){
				p2 = cv::Point2f(puntos_extraidos[i],puntos_extraidos[i+1]);
				cv::circle(frame, p2, 1, cv::Scalar(0,255,0), 3);
				cv::line(frame, p1, p2, cv::Scalar(0,255,0));
				p1 = p2;
			}// Fin for.
		}// Fin else.	
	}// Fin if.
	
	return salida;
}//Fin 'detect_hand'.

// Programa principal.
int main(int argc, char** argv){

	// Variables necesarias.
	cv::VideoCapture camera;
	int imagenes_generadas = 0;
	std::string nombre_base = "frame";

	// Abrimos el dispositivo de video auxiliar.
	camera = cv::VideoCapture(1);
	
	// Si no se ha podido abrir, se abre el dispositivo por defecto.	
	if( !camera.isOpened() ){
		std::cerr << "ADVERTENCIA: No se ha podido abrir la video-cámara USB... Abriendo cámara por defecto...\n";
		camera = cv::VideoCapture(0);
		if( !camera.isOpened() ){
			std::cerr << "ERROR: No se ha podido abrir la video-cámara por defecto...\n";
			return -1;
		}
	}
	
	if(!hand_detector.load("../data/hands_toy.xml")){
		std::cerr << "No se ha podido abrir el clasificador.\n";
		return -1;
	}
	
	
	// Mientras nos se presione Esc, capturamos frames.
	while(imagenes_generadas < MAX_IMAGENES){
		cv::Mat frame;
		camera >> frame;
		
		
		
		if( detect_hand(frame) ){
			cv::imwrite( nombre_base + std::to_string(imagenes_generadas)+".png", frame );
			imagenes_generadas++;
		}
		
		

		cv::imshow("video stream", frame);
		if(cv::waitKey(30) >= 0)
			break;
	}// Fin while.
	
	return 0;
}// Fin main.
