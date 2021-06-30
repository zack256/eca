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

int get_state_of_pos (vector<int> &v, int idx) {
    if ((idx < 0) || (idx >= v.size())) {
        return 0;   // here, off screen returns 0 (white)
    }
    return v[idx];
}

int get_new_state(vector<int> &v, vector<int> &directions, int idx) {
    int direction = 4 * get_state_of_pos(v, idx - 1) + 2 * get_state_of_pos(v, idx) + get_state_of_pos(v, idx + 1);
    return directions[direction];
}

vector<int> update_row(vector<int> &v, vector<int> &directions) {
    vector<int> new_v (v.size());
    for (int i = 0; i < v.size(); i++) {
        new_v[i] = get_new_state(v, directions, i);
    }
    return new_v;
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

vector<int> make_directions_from_rule (int rule) {
    vector<int> directions (8);
    for (int i = 0; i < 8; i++) {
        directions[i] = rule % 2;
        rule /= 2;
    }
    return directions;
}

void eca (Mat &m, vector<int> v, int rule) {
    vector<int> directions = make_directions_from_rule(rule);
    for (int i = 0; i < m.rows; i++) {
        draw_vector_as_row(m, v, i);
        v = update_row(v, directions);
    }
}

int main () {

    int rows = 200, cols = 256;
    Mat m = create_empty_image(rows, cols);

    vector<int> start_state (cols, 0);
    start_state[127] = 1;
    eca(m, start_state, 110);

    imshow("Viewing image", m);
    int k = waitKey(0);

    if (k == 's') {
        imwrite("/path/to/save.png", m);
    }

    return 0;

}