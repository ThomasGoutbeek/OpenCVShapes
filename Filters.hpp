#ifndef FILTERS_HPP
#define FILTERS_HPP

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/core/core_c.h"
#include <stdint.h>
#include <Shape.hpp>

using namespace std;
using namespace cv;

vector<vector<Point>>& filterContours(Mat& frame_threshold);
Mat& HSVFilter(Mat& frame,Mat& frame_HSV,Mat& frame_threshold,const Shape& shape);

void on_low_H_thresh_trackbar(int, void*);
void on_high_H_thresh_trackbar(int, void*);
void on_low_S_thresh_trackbar(int, void*);
void on_high_S_thresh_trackbar(int, void*);
void on_low_V_thresh_trackbar(int, void*);
void on_high_V_thresh_trackbar(int, void*);

void createTrackbars();

#endif