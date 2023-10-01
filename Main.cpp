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
    VideoCapture cap(2);
    createTrackbars();
    bool video = false;
    bool batch = false;

    string v = "video";
    thread th;

    if(argv[1]==v)
    {
        video = true;
    }

    if(argc==3)
    {
        batch = true;
    }

    ShapeDetection s(video,batch);

    if(batch)
    {
        s.readFromFile(argv[2]);
    }
    else
    {
        th = thread(&ShapeDetection::askForShape,&s);
    }

    Shape& shape = s.getShape();
    
    while (s.getInput()!="exit") {

        if(video)
        {
            shape.setFrame(cap);
        }
        else
        {
            shape.setFrame(imread("Neon_shapes.png"));
        }

        if(shape.getFrame().empty())
        {
            break;
        }
        if(batch)
        {
            s.changeShape();
        }
        ostringstream out;
        auto timeStart = chrono::high_resolution_clock::now();

        shape.filter();
        shape.searchForShape(batch);

        auto timeDone = chrono::high_resolution_clock::now();

        out << std::chrono::duration_cast<std::chrono::nanoseconds>(timeDone-timeStart).count();

        string time = "Nanoseconds to find: " + out.str();

        s.print(time,0,20);
        shape.show();

        char key = (char) waitKey(30);
        this_thread::sleep_for(chrono::milliseconds(1000));

        if (key == 'q')
        {
            break;
        }
    }
    th.join();
    return 0;
}

