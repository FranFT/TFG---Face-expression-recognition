/*
* Includes
*/
#include <iostream>
#include <opencv2/opencv.hpp>
#include "utilidades.h"
#include "infoBaseDatos.h"

/*
* Namespaces
*/
using namespace std;
using namespace cv;

/**
 * [main description]
 * @return [description]
 */
int main(){
  infoBaseDatos* base_datos;
  base_datos = new yalefaces();

  cout << "Yalefaces tiene " << base_datos->get_num_sujetos() << " sujetos";
  cout << " con " << base_datos->get_num_expresiones() << " expresiones cada";
  cout << " uno. Estos se encuentran en:\n";
  cout << "\t" << base_datos->construir_path( 0, 0 ) << endl;

}// Main ends.
