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
 */
Mat horizontalFlip(const Mat& _image){
  Mat flipped_image;
  flip( _image, flipped_image, 1 );
  return flipped_image;
}// horizontalFlip
/**
 * Rotaciones, traslaciones
 */

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
  resize(_image(zoomed_area), zoomed_image, _image.size());

  return zoomed_image;
}

int main(){
  /*
   Variables
   */
  Mat image;
  vector<vector<pair< Mat, String> > > images;
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

  // Allocating memmory
  images = vector<vector<pair< Mat, String> > >( data_base->get_num_sujetos() );
  for( unsigned int i = 0; i < data_base->get_num_sujetos(); i++ )
    images.at( i ) = vector<pair< Mat, String > >( data_base->get_num_expresiones() );

  // Reading images
  for( unsigned int i = 0; i < data_base->get_num_sujetos(); i++){
    for( unsigned int j = 0; j < data_base->get_num_expresiones(); j++){
      if( leeimagen( data_base->construir_path( i, j ), image ) ){
        images[i][j] = make_pair( image, getSubjectName( i, data_base->get_expresion( j ) ) );
      }
      else{
        cerr << "Error while trying to read: "
        << data_base->construir_path( i, j ) << endl;
        return 1;
      }// if-else: leeimagen.
    }// for
  }// for


  // Applying random transformations to each training image.
  for( unsigned int i = 0; i < data_base->get_num_sujetos(); i++){
    if( is_training.at( i ) ){
      for( unsigned int j = 0; j < data_base->get_num_expresiones(); j++){
        //
        // Do some transformations
        //
        images[i].push_back( make_pair( horizontalFlip( images[i][j].first ), getSubjectName( i, data_base->get_expresion( j ) ) ) );
        images[i].push_back( make_pair( randomZoom( images[i][j].first ), getSubjectName( i, data_base->get_expresion( j ) ) ) );
      }// for
    }// if
  }// for

  return 0;

}// Main ends.
