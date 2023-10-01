#include "Shape.hpp"

Shape::Shape():shape(DEFAULT_S),colour(DEFAULT_C),minCorners(0),maxCorners(0),shapeString(""),colourString("")
{

}

ShapeType Shape::getShapeType() const
{
    return shape;
}

Colour Shape::getColour() const
{
    return colour;
}

uint16_t Shape::getMinColorH() const
{
    return minColorH;
}

uint16_t Shape::getMaxColorH() const
{
    return maxColorH;
}

void Shape::setNewShape(const std::string& shape,const std::string& colour,bool video)
{
    shapeString = shape;
    colourString = colour;

    std::array<uint16_t,8> neonShapeValues = {5,20,25,37,160,180,60,100};
    std::array<uint16_t,8> videoValues = {1,15,16,26,150,175,50,75};
    std::array<uint16_t,8> colourValues = {};
    
    if(video)
    {
        colourValues = videoValues;
    }
    else
    {
        colourValues = neonShapeValues;
    }

    if(shape=="driehoek")
    {
        this->shape=TRIANGLE;
        minCorners = 3;
        maxCorners = 3;
    }
    else if(shape=="vierkant")
    {
        this->shape=SQUARE;
        minCorners = 4;
        maxCorners = 4;
    }
    else if(shape=="rechthoek")
    {
        this->shape=RECTANGLE;
        minCorners = 4;
        maxCorners = 4;
    }
    else if(shape=="cirkel")
    {
        this->shape=CIRCLE;
        minCorners = 7;
        maxCorners = 99;
    }
    else if(shape=="halve cirkel")
    {
        this->shape=HALFCIRCLE;
        minCorners = 5;
        maxCorners = 6;
    }
    else
    {
        this->shape = DEFAULT_S;
        std::cout<<"This shape doesn't exist, the available ones are:driehoek,vierkant,rechthoek,cirkel,halve cirkel."<<std::endl;
    }

    if(colour=="oranje")
    {
        this->colour=ORANGE;
        minColorH = colourValues[0];
        maxColorH = colourValues[1];
    }
    else if(colour=="geel")
    {
        this->colour=YELLOW;
        minColorH = colourValues[2];
        maxColorH = colourValues[3];
    }
    else if(colour=="roze")
    {
        this->colour=PINK;
        minColorH = colourValues[4];
        maxColorH = colourValues[5];
    }
    else if(colour=="groen")
    {
        this->colour=GREEN;
        minColorH = colourValues[6];
        maxColorH = colourValues[7];
    }
    else
    {
        this->colour = DEFAULT_C;
        std::cout<<"This colour doesn't exist, the available ones are: oranje, geel, roze, groen."<<std::endl;
    }
}

Mat& Shape::searchForShape(bool batch)
{
    found = false;
    for( size_t i = 0; i< contours.size(); i++ )
    {
        int area = contourArea(contours[i]);

        if(area>1000)
        {
            vector<vector<Point>> conPoly(contours.size());
            vector<Rect> boundRect(contours.size());

            float peri = arcLength(contours[i],true);
            approxPolyDP(contours[i],conPoly[i],0.02*peri,true);
            boundRect[i] = boundingRect(conPoly[i]);

            uint16_t objCor = (int)conPoly[i].size();
            ShapeType s = shape;
            bool isSquare = (boundRect[i].width+boundRect[i].width*0.05>=boundRect[i].height&&boundRect[i].width-boundRect[i].width*0.05<=boundRect[i].height);

            bool isCorrectShape = ((s==SQUARE&&isSquare)||(s==RECTANGLE&&!isSquare)||s==TRIANGLE||s==CIRCLE||s==HALFCIRCLE);

            if(objCor>=minCorners&&objCor<=maxCorners&&isCorrectShape)
            {
                drawContours(frame,conPoly,i,Scalar(255,0,255),2);
                rectangle(frame,boundRect[i].tl(),boundRect[i].br(),Scalar(0,255,0),5);

                int middleX = boundRect[i].x+boundRect[i].width/2;
                int middleY = boundRect[i].y+boundRect[i].height/2;

                string xyText = to_string(middleX) + "," + to_string(middleY);
                string areaText = "Area: " + to_string(area);
                if(batch)
                {
                    print(shapeString + ", "+ colourString+": "+ xyText,batch,middleX-5,middleY);
                }
                else
                {
                    print(xyText,batch,middleX-5,middleY);
                }

                print(areaText,batch,middleX,middleY+15);

                found = true;
            }
        }
    }
    if(!found)
    {
        string notfound = shapeString + " " + colourString + ": Not found";
        print(notfound,batch,0,40);
    }
    return frame;
}

void Shape::print(string text,bool batch, int xPos, int yPos)
{
    if(batch)
    {
        cout << text << endl;
    }
    else
    {
        putText(frame, text, {xPos,yPos},FONT_ITALIC,0.7,Scalar(255,0,0),2);
    }
}

bool Shape::checkInput(string text, int linecounter)
{
    bool correctShape = true;
    bool correctColour = true;

    if(text.find("vierkant")==string::npos&&text.find("halve cirkel")==string::npos&&text.find("cirkel")==string::npos&&text.find("rechthoek")==string::npos&&text.find("driehoek")==string::npos)
    {
        std::cout<<"The shape on line " + to_string(linecounter) + " doesn't exist, the available ones are: driehoek,vierkant,rechthoek,cirkel,halve cirkel."<<std::endl;
        correctShape = false;
    }

    if(text.find("groen")==string::npos&&text.find("roze")==string::npos&&text.find("geel")==string::npos&&text.find("oranje")==string::npos)
    {
        std::cout<<"The colour on line " + to_string(linecounter) + " doesn't exist, the available ones are: oranje, geel, roze, groen."<<std::endl;
        correctColour = false;
    }

    return correctShape&&correctColour;
}

const Mat& Shape::getFrame() const
{
    return frame;
}

void Shape::setFrame(Mat frame)
{
    this->frame = frame;
}
void Shape::setFrame(VideoCapture& cap)
{
    cap >> frame;
}
void Shape::show()
{
    imshow("Contours",frame);
    imshow("Object Detection",frame_threshold);
}

void Shape::filter()
{
    frame_threshold = HSVFilter(frame,frame_HSV,frame_threshold,minColorH,maxColorH);
    contours = filterContours(frame_threshold,contours);
}

Shape::~Shape()
{

}