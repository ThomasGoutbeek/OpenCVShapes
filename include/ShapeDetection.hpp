#ifndef SHAPEDETECTION_HPP
#define SHAPEDETECTION_HPP
#include <iostream>
#include <Shape.hpp>
#include <fstream>
#include <vector>

using namespace std;

class ShapeDetection{
    public:
        ShapeDetection(bool video,bool batch);
        ShapeDetection(Shape& shape);
        ~ShapeDetection();
        void checkInput();
        void askForShape();

        void readFromFile(string filename);

        void print(string text, int xPos, int yPos);

        Shape& getShape();
        string& getInput();
        void changeShape();

    private:
        Shape shape;
        bool video;
        string input;
        bool batch;
        vector<string> batchStrings;
        uint16_t shapeCounter;
};

#endif