#include "ShapeDetection.hpp"

ShapeDetection::ShapeDetection(bool video):video(video)
{

}
ShapeDetection::ShapeDetection(const vector<Shape>& shapes):shapes(shapes)
{

}
ShapeDetection::~ShapeDetection()
{

}

void ShapeDetection::checkInput(const string& s)
{
    size_t spaceIndex = s.find(' ');
    if(spaceIndex == string::npos)
    {
        cout<<"String needs to contain a whitespace and have this format:[shape][whitespace][colour]"<<endl;
    }
    else
    {
        string shapetext = s.substr(0,spaceIndex);
        string colourtext = s.substr(spaceIndex+1,s.length()-1);
        Shape shape(shapetext,colourtext,video);
        if(shape.getShapeType()!=DEFAULT_S&&shape.getColour()!=DEFAULT_C)
        {
            shapes.push_back(shape);
        }
    }
}

void ShapeDetection::askForShape()
{
    string input;
    do{
        cout<<"Which shape and colour do you want to search?";
        getline(cin,input);
        checkInput(input);
    }while(shapes.empty());
}


void ShapeDetection::readFromFile(string filename)
{
    fstream file;
    string data;
    file.open(filename, ios::in);
    if (file.is_open()) {
        string data;
        while (getline(file, data)) {
            if(data.at(0)!='#')
            {
                checkInput(data);
            }
        }
        file.close();
    }
}


vector<Shape>& ShapeDetection::getShapes()
{
    return shapes;
}