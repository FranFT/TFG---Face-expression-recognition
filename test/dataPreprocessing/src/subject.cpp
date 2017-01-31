#include "subject.h"
Subject::Subject( const Mat& _image, int _image_label ){
  this->image = _image.clone();
  this->image_label = _image_label;
}

Mat Subject::getImage(){
  return this->image;
}
void Subject::insertImage( const Mat& _image){
  this->image = _image.clone();
}
