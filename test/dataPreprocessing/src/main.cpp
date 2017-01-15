/*
* Includes
*/
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <sstream>
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

/***************
 * Functions
 **************/
/**
 * Assing a name to a given subject-expression pair.
 * @param  _sub  Subject index in data base.
 * @param  _expr Subject's expression index in data base.
 * @return       Subject name
 */
String getSubjectName( const int _sub, String _expr){
  ostringstream conversor;
  conversor << "subject" << _sub << "." << _expr;
  return conversor.str();
}// getSubjectName

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
 * Write the mirror image.
 * @param _image Image to be flipped.
 * @param _pathname  Image path to be saved (without format).
 */
void horizontalFlip(const Mat& _image, const String _pathname){
  Mat flipped_image;
  flip( _image, flipped_image, 1 );
  imwrite( _pathname + "1.png", flipped_image );
}// horizontalFlip


int main(){
  /*
   Variables
   */
  Mat image;
  String subject_name, training_path, test_path;
  infoBaseDatos* data_base;
  vector<bool> is_training;

  /*
  Main code
   */
  // Data inicialitation
  srand(time(NULL));
  training_path = "data/training/";
  test_path = "data/test/";
  data_base = new yalefaces();
  is_training = getTrainingSample( data_base );

  // Applying random transformations to each training image.
  for( unsigned int i = 0; i < data_base->get_num_sujetos(); i++){
    for( unsigned int j = 0; j < data_base->get_num_expresiones(); j++){
      if( leeimagen( data_base->construir_path( i, j ), image ) ){
        // Assign subject name
        subject_name = getSubjectName( i , data_base->get_expresion( j ) );
        if( is_training.at( i ) ){
          // Writing original image to test folder.
          imwrite( training_path + subject_name + ".png", image );
          /**
           * Do some random transformations
           */
          // If expression is 'leftlight' or 'rightlight' its not needed to do horizontalFlip.
          if( j != 3 && j != 6)
            horizontalFlip( image, training_path + subject_name );

        }
        else{
          // Writing image to test folder.
          imwrite( test_path + subject_name + ".png", image );
        }// if-else: is_training
      }// if
      else{
        cerr << "Error while trying to read: "
        << data_base->construir_path( i, j ) << endl;
        return 1;
      }// if-else: leeimagen.
    }// for
  }// for

  return 0;

}// Main ends.
