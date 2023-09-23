#ifndef SHAPEDETECTION_HPP
#define SHAPEDETECTION_HPP
#include <iostream>
#include <Shape.hpp>
#include <fstream>
#include <vector>

using namespace std;

class ShapeDetection{
    public:
        ShapeDetection(bool video);
        ShapeDetection(const vector<Shape>& shapes);
        ~ShapeDetection();
        void checkInput(const string& s);
        void askForShape();

        void readFromFile(string filename);
        vector<Shape>& getShapes();
    private:
        vector<Shape> shapes;
        bool video;
};

#endif