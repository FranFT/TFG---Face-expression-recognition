/*
* Includes
*/
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "utilidades.h"
#include "infoBaseDatos.h"
#include "subject.h"

/*
* Namespaces
*/
using namespace std;
using namespace cv;

/**
 * Global Variables
 */
#define TRAINING_SAMPLE_SIZE 0.7

/***************
 * Functions
 **************/

 /**
  * This method calculates which sample element is in the training sample.
  */
 vector<bool> getTrainingSample( const infoBaseDatos* _data_base ){
   // Variables
   vector<int> indexes;
   vector<bool> output_vector;

   // Method code
   for( unsigned int i = 0; i < _data_base->get_num_sujetos(); i++ )
     indexes.push_back( i );
   random_shuffle( indexes.begin(), indexes.end() );

   output_vector = vector<bool>( indexes.size(), false );
   for( unsigned int i = 0; i < ceil( indexes.size() * TRAINING_SAMPLE_SIZE ); i++ )
     output_vector.at( indexes.at( i ) ) = true;

   return output_vector;
 }// getTrainingSample ends.

int main(){
  /*
   Variables
   */
  Mat temp_image;
  vector< bool > is_training;
  vector<vector< Subject > > subjects;
  infoBaseDatos* data_base;

  /*
  Main code
   */
  // Data inicialitation
  //srand(time(NULL));
  srand(12345);
  data_base = new yalefaces();
  is_training = getTrainingSample( data_base );


  // Allocating memmory
  subjects = vector<vector< Subject > >( data_base->get_num_sujetos() );


  // Reading images
  for( unsigned int i = 0; i < data_base->get_num_sujetos(); i++)
    for( unsigned int j = 0; j < data_base->get_num_expresiones(); j++)
      if( leeimagen( data_base->construir_path( i, j ), temp_image ) )
        subjects.at( i ).push_back( Subject( temp_image, j ));
      else{
        cerr << "Error intentado leer la imagen: '"
        << data_base->construir_path( i, j ) << endl;
        return 1;
      }

   return 0;
}
