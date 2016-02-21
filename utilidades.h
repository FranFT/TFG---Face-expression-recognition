#include <iostream>
#include <opencv2\opencv.hpp>
using namespace cv;
using namespace std;
//// Entrada / Salida
// Lee la imagen 'filename' en color o escala de grises en funci�n del par�metro 'flagColor'.
Mat leeimagen(char* filename, int flagColor = 0);

// Muesta una imagen por pantalla en una ventana de nombre 'nombre_ventana'.
void pintaI(const Mat& im, char* nombre_ventana = "imagen");

// Muestra un vector de im�genes en una sola imagen llamada 'solucion' por defecto.
void pintaMI(const vector<Mat> &imagenes_solucion, char* nombre = "solucion");

void pintaMI(const vector<vector<Mat> > &imagenes_solucion, char* nombre = "solucion");