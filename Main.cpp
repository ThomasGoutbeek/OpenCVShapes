#include <iostream>
#include <stdint.h>
#include <vector>

#include <Shape.hpp>
#include <ShapeDetection.hpp>
#include <Filters.hpp>
#include <chrono>
#include <thread>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    VideoCapture cap(0);
    createTrackbars();
    bool video = false;
    string v = "video";

    if(argv[1]==v)
    {
        video = true;
    }

    ShapeDetection s(video);
    bool batch = false;
    if(argc==3)
    {
        s.readFromFile(argv[2]);
        batch = true;
    }
    else
    {
        s.askForShape();
    }
    Mat frame,frame_HSV,frame_threshold;

    vector<vector<Point>> contours;
    vector<Shape>& shapes = s.getShapes();

    while (true) {

        if(video)
        {
            cap >> frame;
            resize(frame, frame, Size(frame.size().width/2, frame.size().height/2), INTER_LINEAR);
        }
        else
        {
            frame = imread("Neon_shapes.png");
        }

        if(frame.empty())
        {
            break;
        }

        for(Shape& shape:shapes)
        {
            auto timeStart = chrono::high_resolution_clock::now();

            frame_threshold = HSVFilter(frame,frame_HSV,frame_threshold,shape);
            contours = filterContours(frame_threshold);
            frame = shape.searchForShape(frame,contours,batch);

            auto timeDone = chrono::high_resolution_clock::now();
            cout<<"Nanoseconds to find: ";
            cout<< std::chrono::duration_cast<std::chrono::nanoseconds>(timeDone-timeStart).count()<<endl;

            imshow("Object Detection", frame_threshold);
            imshow("Contours",frame);
        }

        char key = (char) waitKey(30);
        this_thread::sleep_for(chrono::milliseconds(100));
        system("clear");

        if (key == 'q')
        {
            break;
        }
    }
    return 0;
}

