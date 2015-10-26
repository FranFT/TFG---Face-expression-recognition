#include <iostream>
#include <opencv2\opencv.hpp>

using namespace cv;
using namespace std;

//// Entrada / Salida
// Lee la imagen 'filename' en color o escala de grises en función del parámetro 'flagColor'.
Mat leeimagen(char* filename, int flagColor = 0){
	return imread(filename, flagColor);
}

// Muesta una imagen por pantalla en una ventana de nombre 'nombre_ventana'.
void pintaI(const Mat& im, char* nombre_ventana = "imagen"){
	if (!im.empty()){
		Mat im_copia = Mat(im);
		im_copia.convertTo(im_copia, CV_8U);

		namedWindow(nombre_ventana, 1);
		imshow(nombre_ventana, im_copia);
		waitKey();
		destroyWindow(nombre_ventana);
	}
}

int main(){
	Mat prueba = leeimagen("yalefaces/subject01.png");
	pintaI(prueba, "Prueba");
	return 0;
}