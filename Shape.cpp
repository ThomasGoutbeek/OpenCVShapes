#include "Shape.hpp"

Shape::Shape():shape(DEFAULT_S),colour(DEFAULT_C),minCorners(0),maxCorners(0),shapeString(""),colourString("")
{

}

Shape::Shape(const std::string& shape,const std::string& colour,bool video)
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
    else if(shape=="halvecirkel")
    {
        this->shape=HALFCIRCLE;
        minCorners = 5;
        maxCorners = 6;
    }
    else
    {
        this->shape = DEFAULT_S;
        std::cout<<"This shape doesn't exist, the available ones are:driehoek,vierkant,rechthoek,cirkel,halvecirkel."<<std::endl;
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


Mat& Shape::searchForShape(Mat& frame,const vector<vector<Point>>& contours, bool batch)
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
                if(batch)
                {
                    cout << shapeString + " " + colourString + ": " + xyText<<endl;
                }
                else
                {
                    putText(frame,xyText,{middleX-5,middleY},FONT_ITALIC,0.5,Scalar(255,0,0),2);
                }
                found = true;
            }
        }
    }
    if(!found)
    {
        cout << shapeString + " " + colourString + ": Not found"<<endl;
    }
    return frame;
}

Shape::~Shape()
{

}