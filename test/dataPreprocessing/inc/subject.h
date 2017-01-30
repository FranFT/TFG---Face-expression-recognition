#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

class Subject{
private:
  Mat image;
  String image_name;
  int image_label;
public:
  Subject();
  Subject( const Mat& _image, String _image_name, int _image_label );
};
