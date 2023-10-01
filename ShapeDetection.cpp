#include "ShapeDetection.hpp"

ShapeDetection::ShapeDetection(bool video,bool batch):video(video),batch(batch),shapeCounter(0)
{

}
ShapeDetection::ShapeDetection(Shape& shape):shape(shape)
{

}
ShapeDetection::~ShapeDetection()
{

}

void ShapeDetection::checkInput()
{
    size_t spaceIndex = input.find(' ');
    size_t half = input.find("halve");
    if(spaceIndex == string::npos&&input!="exit")
    {
        cout<<"String needs to contain a whitespace and have this format:[shape][whitespace][colour]"<<endl;
    }
    else 
    {
        if(half != string::npos)
        {
            spaceIndex = input.find(' ',spaceIndex+1);
        }
        string shapetext = input.substr(0,spaceIndex);
        string colourtext = input.substr(spaceIndex+1,input.length()-1);
        if(batch)
        {
            shape.setNewShape(shapetext,colourtext,video);
        }
        else if(shape.checkInput(input,0))
        {
            shape.setNewShape(shapetext,colourtext,video);
        }
        
    }
}

void ShapeDetection::askForShape()
{
    do{
        cout<<"Which shape and colour do you want to search?";
        getline(cin,input);
        checkInput();
    }while(input!="exit");
}


void ShapeDetection::readFromFile(string filename)
{
    fstream file;
    int linecounter = 0;
    file.open(filename, ios::in);
    if (file.is_open()) {
        while (getline(file, input)) {
            if(input.at(0)!='#')
            {
                if(shape.checkInput(input,linecounter))
                {
                    batchStrings.push_back(input);
                }
            }
            linecounter++;
        }
        file.close();
    }
}

void ShapeDetection::changeShape()
{
    input = batchStrings.at(shapeCounter);
    checkInput();
    
    shapeCounter++;
    if(shapeCounter==batchStrings.size())
    {
        shapeCounter = 0;
    }
}

void ShapeDetection::print(string text, int xPos, int yPos)
{
    shape.print(text,batch,xPos,yPos);
}

Shape& ShapeDetection::getShape()
{
    return shape;
}

string& ShapeDetection::getInput()
{
    return input;
}