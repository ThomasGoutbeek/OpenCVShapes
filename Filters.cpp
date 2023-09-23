#include "Filters.hpp"

vector<vector<Point>> contours;
const uint16_t thresh = 100;

const int max_value_H = 360/2;
const int max_value = 255;

const String window_capture_name = "Video Capture";
const String window_detection_name = "Object Detection";
int low_H = 0, low_S = 0, low_V = 0;
int high_H = max_value_H, high_S = max_value, high_V = max_value;

vector<vector<Point>>& filterContours(Mat& frame_threshold)
{
    Mat canny_output;
    Canny( frame_threshold, canny_output, thresh, thresh*2 );
    vector<Vec4i> hierarchy;
    findContours( canny_output, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE );
    return contours;
}

Mat& HSVFilter(Mat& frame,Mat& frame_HSV,Mat& frame_threshold,const Shape& shape)
{
    cvtColor(frame, frame_HSV, COLOR_BGR2HSV);
    inRange(frame_HSV, Scalar(shape.getMinColorH(), low_S, low_V), Scalar(shape.getMaxColorH(), high_S, high_V), frame_threshold);
    return frame_threshold;
}

void on_low_H_thresh_trackbar(int, void*)
{
 low_H = min(high_H-1, low_H);
 setTrackbarPos("Low H", window_detection_name, low_H);
}
void on_high_H_thresh_trackbar(int, void*)
{
 high_H = max(high_H, low_H+1);
 setTrackbarPos("High H", window_detection_name, high_H);
}
void on_low_S_thresh_trackbar(int, void*)
{
 low_S = min(high_S-1, low_S);
 setTrackbarPos("Low S", window_detection_name, low_S);
}
void on_high_S_thresh_trackbar(int, void*)
{
 high_S = max(high_S, low_S+1);
 setTrackbarPos("High S", window_detection_name, high_S);
}
void on_low_V_thresh_trackbar(int, void*)
{
 low_V = min(high_V-1, low_V);
 setTrackbarPos("Low V", window_detection_name, low_V);
}
void on_high_V_thresh_trackbar(int, void*)
{
 high_V = max(high_V, low_V+1);
 setTrackbarPos("High V", window_detection_name, high_V);
}

void createTrackbars()
{
    namedWindow(window_capture_name);
    namedWindow(window_detection_name);
    createTrackbar("Low H", window_detection_name, &low_H, max_value_H, on_low_H_thresh_trackbar);
    createTrackbar("High H", window_detection_name, &high_H, max_value_H, on_high_H_thresh_trackbar);
    createTrackbar("Low S", window_detection_name, &low_S, max_value, on_low_S_thresh_trackbar);
    createTrackbar("High S", window_detection_name, &high_S, max_value, on_high_S_thresh_trackbar);
    createTrackbar("Low V", window_detection_name, &low_V, max_value, on_low_V_thresh_trackbar);
    createTrackbar("High V", window_detection_name, &high_V, max_value, on_high_V_thresh_trackbar);
}
