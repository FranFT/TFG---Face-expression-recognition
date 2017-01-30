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

 /**
  * Write the mirror image.
  * @param _image Image to be flipped.
  */
 Mat horizontalFlip(const Mat& _image){
   Mat flipped_image;
   flip( _image, flipped_image, 1 );
   return flipped_image;
 }// horizontalFlip

 /**
  * Makes a random zoom-in within a range.
  * @param  _image    Image to be zoomed.
  * @param  min_range Minimun percentage of the picture to be zoomed in.
  * @param  max_range Maximun percentage of the picture to be zoomed in.
  * @return           Zoomed in image.
  */
Mat randomZoom(const Mat& _image, int min_range = 10, int max_range = 30){
  // Variables //
  int x, y;
  float zoom_range;
  Mat zoomed_image;
  Rect zoomed_area;

  // Code //
  // Defining a random zoom within a [min,max] range.
  zoom_range = ( rand() % (max_range - min_range + 1) ) + min_range;
  zoom_range /= 100;

  // Defining the initial rect point.
  x = _image.cols * zoom_range;
  y = _image.rows * zoom_range;
  zoomed_area = Rect( x, y, _image.cols - x, _image.rows - y );

  // Zooming in while resizing the result image.
  resize( _image( zoomed_area ), zoomed_image, _image.size() );

  return zoomed_image;
}// randomZoom.

/**
 * Makes a random rotation within a range.
 * @param  _image    Image to be rotated.
 * @param  min_range Minimun angle of the picture to be rotated.
 * @param  max_range Maximun angle of the picture to be rotated.
 * @return           rotated in image.
 */
Mat randomRotate(const Mat& _image, int min_range = 5, int max_range = 40){
  // Variables //
  int aux;
  Point2f center_point;
  float rotation_angle;
  Mat rot_matrix;
  Mat rotated_image;

  // Code //
  // Calculating image center point.
  center_point = Point2f( _image.cols/2.0F, _image.rows/2.0F);
  // Getting the random rotation angle.
  aux = rand();
  rotation_angle = ( aux % (max_range - min_range + 1) ) + min_range;

  if( aux % 2 == 0 )
    rotation_angle *= -1;
  // Getting the rotation matrix and applying it.
  rot_matrix = getRotationMatrix2D( center_point, rotation_angle, 1.0 );
  warpAffine( _image, rotated_image, rot_matrix, _image.size(),
  CV_INTER_CUBIC,  BORDER_TRANSPARENT);

  return rotated_image;
}// randomRotate



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

  // Applying random transformations to each training image.
  for( unsigned int i = 0; i < data_base->get_num_sujetos(); i++){
    if( is_training.at( i ) ){
      for( unsigned int j = 0; j < data_base->get_num_expresiones(); j++){
        //
        // Do some transformations ( Data augmetation process )
        //
        subjects.at( i ).push_back( Subject( horizontalFlip( subjects[i][j].getImage()), j ) );
        subjects.at( i ).push_back( Subject( randomZoom( subjects[i][j].getImage()), j ) );
        //subjects.at( i ).push_back( Subject( randomRotate( subjects[i][j].getImage()), j ) );
      }// for
    }// if
  }// for

   return 0;
}
