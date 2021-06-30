#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat create_empty_image (int rows, int cols) {
    Scalar white = Scalar(255, 255, 255);
    Mat m (rows, cols, CV_8UC3, white);
    return m;
}

void draw_vector_as_row(Mat &m, vector<int> &v, int row) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i]) {
            Vec3b & color = m.at<Vec3b>(row, i);
            color[0] = 0;
            color[1] = 0;
            color[2] = 0;
        }
    }
}

int main () {

    int rows = 500, cols = 256;
    Mat m = create_empty_image(rows, cols);

    vector<int> v (cols, 0);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j && (i % j)) {
                v[j] = 0;
            } else {
                v[j] = 1;
            }
        }
        draw_vector_as_row(m, v, i);
    }

    imshow("Viewing image", m);
    int k = waitKey(0);
    return 0;

}