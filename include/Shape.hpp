#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <iostream>
#include "Filters.hpp"
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
        ~Shape();
        ShapeType getShapeType() const;
        Colour getColour() const;
        uint16_t getMinColorH() const;
        uint16_t getMaxColorH() const;

        void setNewShape(const string& shape,const string& colour,bool video);
        bool checkInput(string text, int linecounter);

        const Mat& getFrame() const;
        void setFrame(Mat frame);
        void setFrame(VideoCapture& cap);
        
        void filter();
        Mat& searchForShape(bool batch);

        void print(string text,bool batch,int xPos=0,int yPos=0);
        void show();

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
        Mat frame, frame_threshold, frame_HSV;
        vector<vector<Point>> contours;
};

#endif