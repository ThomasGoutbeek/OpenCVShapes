#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <iostream>
#include "opencv2/imgproc.hpp" 
using namespace cv;
using namespace std;

enum ShapeType{
    DEFAULT_S,SQUARE,RECTANGLE,CIRCLE,TRIANGLE,HALFCIRCLE
};
enum Colour{
    DEFAULT_C,ORANGE,YELLOW,PINK,GREEN
};
class Shape{
    public:
        Shape();
        Shape(const string& shape,const string& colour,bool video);
        ~Shape();
        ShapeType getShapeType() const;
        Colour getColour() const;
        uint16_t getMinColorH() const;
        uint16_t getMaxColorH() const;
        
        Mat& searchForShape(Mat& frame,const vector<vector<Point>>& contours, bool batch);
    private:
        ShapeType shape;
        Colour colour;
        uint16_t minCorners;
        uint16_t maxCorners;
        string shapeString;
        string colourString;
        uint16_t minColorH;
        uint16_t maxColorH;
        bool found;
};

#endif