#include "subject.h"
Subject::Subject( const Mat& _image, int _image_label ){
  this->image = _image.clone();
  this->image_label = _image_label;
}
