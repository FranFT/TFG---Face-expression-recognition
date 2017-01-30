#include "subject.h"
Subject::Subject( const Mat& _image, String _image_name, int _image_label ){
  this->image = _image.clone();
  this->image_name = _image_name;
  this->image_label = _image_label;
}
