#include <iostream>
#include <opencv2/opencv.hpp>
#include "stasm_lib.h"

// Array que contendrá los puntos extraidos.
float puntos_extraidos[2*stasm_NLANDMARKS];

// Pinta el vector de puntos en la imagen dada.
void pinta(cv::Mat& _frame){
	// Variables necesarias.
	cv::Point2f p1,p2;
	
	// Pinto el primer punto.
	p1 = cv::Point2f(puntos_extraidos[0],puntos_extraidos[1]);
	cv::circle(_frame, p1, 1, cv::Scalar(0,255,0), 3);
	
	// Pinto el resto y los uno mediante una linea al anterior.
	for(int i=2; i<stasm_NLANDMARKS*2; i+=2){
		p2 = cv::Point2f(puntos_extraidos[i], puntos_extraidos[i+1]);
		cv::circle(_frame, p2, 1, cv::Scalar(0,255,0), 3);
		cv::line(_frame, p1, p2, cv::Scalar(0,255,0));
		p1 = p2;
	}
}

// Programa principal.
int main(int argc, char** argv){

	// Abrimos el dispositivo de video por defecto.
	cv::VideoCapture camera(0);
	if(!camera.isOpened()){
		std::cerr << "No se ha podido abrir la video-cámara.\n";
		return -1;
	}
	
	int cara_encontrada = 0;
	
	// Mientras nos se presione Esc, capturamos frames.
	while(true){
		cv::Mat frame, grey_frame;
		camera >> frame;
		
		cv::cvtColor(frame, grey_frame, cv::COLOR_BGR2GRAY);
		stasm_search_single(
			&cara_encontrada,
			puntos_extraidos,
			(char*)grey_frame.data,
			grey_frame.size().width,
			grey_frame.size().height,
			"path",
			"../data");
			
		if(cara_encontrada)
				pinta(frame);

		cv::imshow("video stream", frame);
		if(cv::waitKey(30) >= 0)
			break;
	}
	
	return 0;
}
