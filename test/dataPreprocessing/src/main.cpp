/*
* Includes
*/
#include <stdlib.h>
#include <time.h>
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
 * Global Variables
 */
#define TRAINING_SAMPLE_SIZE 0.7

/**
 * Functions
 */

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

/**
 * [main description]
 * @return [description]
 */
int main(){
  /*
   Variables
   */
  Mat image;
  infoBaseDatos* data_base;
  vector<bool> is_training;

  /*
  Main code
   */
  // Data inicialitation
  srand(time(NULL));
  data_base = new yalefaces();
  is_training = getTrainingSample( data_base );

  for( int i=0; i<is_training.size(); i++)
    cout << is_training.at(i) << ", ";
  cout << endl;

}// Main ends.
