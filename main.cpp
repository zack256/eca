#include <iostream>
//#include <filesystem>

#include <opencv2/opencv.hpp>
/**
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
**/

using namespace std;
using namespace cv;

int main () {

    string path = "path/to/file.png";

    Mat img = imread(path);
    if (img.empty()) {
        cout << "File not found :("; return 0;
    }
    imshow("Viewing image", img);
    int k = waitKey(0);
    return 0;
}