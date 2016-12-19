#include <iostream>
#include <opencv2/opencv.hpp>
#include <caffe/caffe.hpp>

using namespace std;
using namespace cv;

int main(){
  cout << "What's up World" << '\n';
  Mat prueba = Mat::zeros(2, 2, CV_32S);

  cout << prueba << endl;
  return 0;
}


// https://github.com/BVLC/caffe/issues/2704
