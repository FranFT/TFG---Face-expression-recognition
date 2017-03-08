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
  CV_INTER_CUBIC,  BORDER_REFLECT);

  return rotated_image;
}// randomRotate

/**
 * It normalizes a image to reach 0 mean 1 variance. It is achieved by subtracting
 * the image pixels mean and then dividing by image standard deviation.
 * @param  _image image to be normalized.
 * @return        Normalized image.
 */
Mat normalizeImage( const Mat& _image ){
  // Variables
  Mat _mean, _stddev, _temp;

  // Code //
  // Working on a temp variable. Changing its precision for better accuracy
  _temp = _image.clone();
  _temp.convertTo( _temp, CV_64F );

  // Calculating mean and standard deviation.
  meanStdDev( _temp, _mean, _stddev );

  // Returning the normalized image.
  return (_temp - _mean) / _stddev;
}// normalizeImage

/**
 * Adds Gaussian Noise to a given image.
 * @param  _image Image which will receive noise.
 * @return        50% prob to return the given image with brigher or darker noise.
 */
Mat randomNoise( const Mat& _image ){
  // Variables.
  Mat gaussianNoise;

  // Code //
  gaussianNoise = _image.clone();
  // Getting the mask.
  randn(gaussianNoise ,50,20);

  if( rand() % 2 == 0)
    return _image - gaussianNoise; // Darker noise.
  else
    return _image + gaussianNoise; // Brighter noise.
}

/**
 * Apply a random combination of the transformations already implemented to the
 * same image.
 * @param  _image     Image to be transformed.
 * @param  output_mat Transformed output image.
 * @param  nt         Number of different transformations that can be applied.
 * @return            True if some transformation was applied. False otherwise.
 */
bool combinedTrans( const Mat& _image, Mat& output_mat, int nt = 4 ){
  // Variables //
  int trans_to_be_applied;
  bool trasn_was_applied;

  // Code //
  output_mat = _image.clone();
  trasn_was_applied = false;

  // Applying 'num_trans' transformations with a 50% prob.
  for( unsigned int i = 0; i < nt; i++ ){
    trans_to_be_applied = rand() % nt;
    if( rand() % 2 == 0 ){
      trasn_was_applied = true;
      switch ( trans_to_be_applied ) {
        case 0:
          output_mat = horizontalFlip( output_mat );
        break;

        case 1:
          output_mat = randomZoom( output_mat );
        break;

        case 2:
          output_mat = randomRotate( output_mat );
        break;

        case 3:
          output_mat = randomNoise( output_mat );
        break;

        default:
          cerr << "No hay definida una transfomación para el valor: " << trans_to_be_applied << endl;
        break;
      }
    }
  }

  return trasn_was_applied;
}

/**
 * Generates the labels file to be able to classify using the model later.
 * @param  _data_base Data base used.
 * @param  expr       Expression used to generate the labels.
 * @return            If succeeded writing the file.
 */
bool generateLabelsFile( const infoBaseDatos* _data_base, int expr = -1 ){
  /*
  Variables
   */
  ofstream labels_file;
  String labels_file_name = "labels.txt";

  /*
  Code
   */
  labels_file.open( labels_file_name.c_str(), ios::trunc );
  if( labels_file.is_open() ){
    if( expr == -1 ){
      for( unsigned int i = 0; i < _data_base->get_num_expresiones(); i++ )
        labels_file << i << " " << _data_base->get_expresion( i ) << endl;
    }
    else{
      labels_file << 0 << " Not " << _data_base->get_expresion( expr ) << endl;
      labels_file << 1 << " " << _data_base->get_expresion( expr ) << endl;
    }
    labels_file.close();
    return true;
  }
  else{
    return false;
  }
}

int main(int argc, char **argv){
  /*
   Variables
   */
  int choosen_expr = 0;
  infoBaseDatos* data_base;
  data_base = new yalefaces();

  Mat temp_image;
  vector< bool > is_training;
  vector<vector< Subject > > subjects;
  ofstream training_output_file, test_output_file;
  String training_path, test_path, training_output_file_name, test_output_file_name;
  ostringstream image_name, file_name;
  int combinedImagesToBeGenerated;

  /*
  Checking input parameters.
   */
  if( argc == 1 ){ // No parameters.
    choosen_expr = -1;
    file_name << "testListFile_all.txt";
  }
  else if( argc == 2 ){ // Expression was given.
    bool found = false;
    // Checking if the expression is correct.
    for( int i = 0; i < data_base->get_num_expresiones(); i++ )
      if( argv[1] == data_base->get_expresion( i ) ){
        found = true;
        choosen_expr = i;
      }

    if( !found ){
      cerr << "Error: Debes introducir una expresión válida." << endl;
      return 1;
    }
    else{
      file_name << "testListFile_" << argv[1] << ".txt";
    }
  }
  else{ // More than one parameter
    cerr << "Error: El número de parámetros debe ser 1 o ninguno." << endl;
    return 1;
  }


  /*
  Main code
   */
  // Data inicialitation
  srand(time(NULL));
  training_path = "data/training/";
  test_path = "data/test/";
  is_training = getTrainingSample( data_base );
  training_output_file_name = "trainingListFile.txt";
  test_output_file_name = file_name.str();
  combinedImagesToBeGenerated = 5;

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
        subjects.at( i ).push_back( Subject( randomRotate( subjects[i][j].getImage()), j ) );
        subjects.at( i ).push_back( Subject( randomNoise( subjects[i][j].getImage()), j ) );

        //
        // Combined transformations.
        //
        Mat combinedTransImage;
        for( unsigned int k = 0; k < rand() % combinedImagesToBeGenerated; k++ )
            if( combinedTrans( subjects[i][j].getImage(), combinedTransImage ) )
              subjects.at( i ).push_back( Subject( combinedTransImage, j ) );
      }// for
    }// if
  }// for

  // Getting 0 mean 1 variance.
  /*for( unsigned int i = 0; i < data_base->get_num_sujetos(); i++ )
    if( is_training.at( i ) )
      for( unsigned int j = 0; j < subjects[i].size(); j++ )
        subjects[i][j].insertImage( normalizeImage( subjects[i][j].getImage() ) );*/

  // Writing images and listfile.
  training_output_file.open( training_output_file_name.c_str(), ios::trunc );
  test_output_file.open( test_output_file_name.c_str(), ios::trunc );
  if( training_output_file.is_open() && test_output_file.is_open() ){
    for( unsigned int i = 0; i < data_base->get_num_sujetos(); i++ ){
      for( unsigned int j = 0; j < subjects[i].size(); j++ ){
        image_name << "subject" << i << "-" << j << "-" << data_base->get_expresion(subjects[i][j].getLabel()) << ".png";
        if( is_training[i] ){
          imwrite( training_path + image_name.str(), subjects[i][j].getImage());
          training_output_file << "training/" << image_name.str() << " ";
          if( choosen_expr == -1 )
            training_output_file << subjects[i][j].getLabel() << endl;
          else
            ( subjects[i][j].getLabel() == choosen_expr ) ? training_output_file << 1 << endl : training_output_file << 0 << endl;
        }
        else{
          imwrite( test_path + image_name.str(), subjects[i][j].getImage());
          test_output_file << "test/" << image_name.str() << " ";
          if( choosen_expr == -1 )
            test_output_file << subjects[i][j].getLabel() << endl;
          else
            ( subjects[i][j].getLabel() == choosen_expr ) ? test_output_file << 1 << endl : test_output_file << 0 << endl;
        }
        image_name.str("");
      }
    }
    training_output_file.close();
    test_output_file.close();

    // Generates label file.
    if( !generateLabelsFile(data_base, choosen_expr)){
      cerr << "ERROR: No se pudo generar el archivo LabelsFile" << endl;
      return 1;
    }
  }
  else{
    cerr << "ERROR: No se pudo escribir el archivo ListFile" << endl;
    return 1;
  }
   return 0;
}
