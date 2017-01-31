#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

class Subject{
private:
  Mat image;
  int image_label;
public:
  Subject();
  Subject( const Mat& _image, int _image_label );
  Mat getImage();
  int getLabel();
  void insertImage( const Mat& _image);
};
