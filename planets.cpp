#include "QPainter"
#include "planets.h"
#include <random>

Planets::Planets(QWidget *parent) :
    QLabel(parent)
{
    setMouseTracking(true);
    std::random_device rd;
    std::mt19937 mt(rd());
    //std::mt19937 mt(1);

    std::uniform_int_distribution<int> dist(0,410);
    std::uniform_int_distribution<int> radius(0,359);
    std::uniform_int_distribution<int> randMass(1,20);
    Particals* tempPartical=NULL;
    currentPlanet=0;

    zoomFactor = 16;
    XShift = 0;
    YShift = 0;
    mouseDownX = 0;
    mouseDownY = 0;
    mouseDown = 0;
    planetSize = 8;
    bool good = 0;
    int randomRad,randomDist;

    for(int i = 0;i<2000;i++)
    {
        do
        {
            randomRad = radius(mt);
            randomDist = dist(mt);
            tempPartical=new Particals(cos(randomRad)*randomDist+400,sin(randomRad)*randomDist+400,cos(randomRad+1.570795)*pow((400-randomDist)/40,2),sin(randomRad+1.570795)*pow((400-randomDist)/40,2),randMass(mt));
            //tempPartical=new Particals(cos(randomRad)*randomDist+400,sin(randomRad)*randomDist+400,5,0,randMass(mt));
            //tempPartical = new Particals(dist(mt),dist(mt),5,0,randMass(mt));
            //tempPartical = new Particals(dist(mt)+200,(dist(mt)/8)+200,0,0,randMass(mt));

            good = 1;
            for(int j=0;j<planets.size();j++)
            {
                if(tempPartical->getX() == planets.at(j)->getX() && tempPartical->getY() == planets.at(j)->getY())
                {
                    good = 0;
                }
            }
            if(!good)
            {
                delete tempPartical;
                tempPartical = 0;
            }
        }while(!good);
        planets.push_back(tempPartical);
    }
    //tempPartical = new Particals(280.5,628.7601,0,0,1);
    //planets.push_back(tempPartical);


    /*tempPartical = new Particals(100,300,100);
    planets.push_back(tempPartical);
    tempPartical = new Particals(100,400,100);
    planets.push_back(tempPartical);
    tempPartical = new Particals(500,350,10000);
    planets.push_back(tempPartical);*/
}

void Planets::updateData()
{
    for(unsigned int i=0;i<planets.size();i++)
    {
        planets.at(i)->addForce(calculateXForce(i),calculateYForce(i));
    }
    for(unsigned int i=0;i<planets.size();i++)
    {
        planets.at(i)->updateLocation();
    }
    double distance=0;
    for(unsigned int i=0;i<planets.size();i++)
    {
        for(unsigned int j=i+1;j<planets.size();j++)
        {
            distance = sqrt(pow(planets.at(i)->getX()-planets.at(j)->getX(),2)+pow(planets.at(i)->getY()-planets.at(j)->getY(),2));
            if(distance<fabs(planets.at(i)->getDiameter()/2+planets.at(j)->getDiameter()/2))
            {

                if(planets.at(i)->getDiameter()<planets.at(j)->getDiameter())
                {
                    Particals* temp = planets.at(i);
                    planets.at(i) = planets.at(j);
                    planets.at(j) = temp;
                }
                planets.at(i)->combine(*planets.at(j));
                delete planets.at(j);
                for(unsigned int m=j;m<planets.size()-1;m++)
                {
                    planets.at(m)=planets.at(m+1);
                }
                planets.pop_back();
                if(currentPlanet>j)
                {
                    currentPlanet--;
                }
                j--;
            }
        }
    }
    update();
    doneUpdating();
}

void Planets::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen thePen;
    QBrush theBrush;
    theBrush.setStyle(Qt::SolidPattern);
    thePen.setStyle(Qt::SolidLine);
    QColor theColor;
    theColor.setRgb(0,0,0);
    thePen.setColor(theColor);
    theBrush.setColor(theColor);
    QPoint thePoint;
    painter.setBrush(theBrush);
    painter.setBrush(theBrush);

    painter.drawRect(0,0,this->width(),this->height());
    theColor.setRgb(255,255,0);
    thePen.setColor(theColor);
    theBrush.setColor(theColor);
    painter.setBrush(theBrush);
    painter.setBrush(theBrush);
    int green;
    double locX,locY;
    double distance = 0;


    for(unsigned int i=0;i<planets.size();i++)
    {

        //thePoint.setX(planets.at(i)->getX());
        //thePoint.setY(planets.at(i)->getY());
        if(currentPlanet==i)
        {
            theColor.setRgb(0,0,255);
        }
        else
        {
            green = planets.at(i)->getDiameter()*255/50;
            if(green>255)
            {
                green=255;
            }
            theColor.setRgb(255,green,0);
        }
        theBrush.setColor(theColor);
        thePen.setColor(theColor);
        painter.setPen(thePen);
        painter.setBrush(theBrush);

        //locX = ((planets.at(i)->getX()+(XShift*zoomFactor) - this->width()/2)/zoomFactor) + (this->width()/2);
        //locY = ((planets.at(i)->getY()+(YShift*zoomFactor) - this->height()/2)/zoomFactor) + (this->height()/2);
        locX = ((planets.at(i)->getX() + XShift - this->width()/2)/zoomFactor) + (this->width()/2);
        locY = ((planets.at(i)->getY() + YShift - this->height()/2)/zoomFactor) + (this->height()/2);

        thePoint.setY(locY);
        thePoint.setX(locX);
        painter.drawEllipse(thePoint,planetSize*(planets.at(i)->getDiameter()/2)/zoomFactor,planetSize*(planets.at(i)->getDiameter()/2)/zoomFactor);
        distance = sqrt(pow(thePoint.x()-mouseLocX,2)+pow(thePoint.y()-mouseLocY,2));
        if(distance<planetSize*(planets.at(i)->getDiameter()/2)/zoomFactor)
        {

            painter.drawText(this->width()-300,this->height()-100,QString("Planet: %1").arg(i));
            painter.drawText(this->width()-300,this->height()-80,QString("Location (X,Y): (%1,%2)").arg(planets.at(i)->getX()).arg(planets.at(i)->getY()));
            painter.drawText(this->width()-300,this->height()-60,QString("Speed (X,Y): (%1,%2)").arg(planets.at(i)->getSpeedX()).arg(planets.at(i)->getSpeedY()));
            painter.drawText(this->width()-300,this->height()-40,QString("Mass: %1").arg(planets.at(i)->getMass()));

        }


    }

    if(currentPlanet<planets.size())
    {
        painter.drawText(20,this->height()-100,QString("Planet: %1").arg(currentPlanet));
        painter.drawText(20,this->height()-80,QString("Location (X,Y): (%1,%2)").arg(planets.at(currentPlanet)->getX()).arg(planets.at(currentPlanet)->getY()));
        painter.drawText(20,this->height()-60,QString("Speed (X,Y): (%1,%2)").arg(planets.at(currentPlanet)->getSpeedX()).arg(planets.at(currentPlanet)->getSpeedY()));
        painter.drawText(20,this->height()-40,QString("Mass: %1").arg(planets.at(currentPlanet)->getMass()));
    }
    theColor.setRgb(255,255,255);
    thePen.setColor(theColor);
    painter.setPen(thePen);
    painter.drawText(0,20,QString("%1").arg(planets.size()));
    painter.drawText(0,40,QString("%1").arg(zoomFactor));
    painter.drawText(0,60,QString("X:%1  Y:%2").arg(XShift).arg(YShift));
    painter.drawText(0,80,QString("PlanetSize: %1").arg(planetSize));

}

void Planets::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->delta() / 8;
    int numSteps = numDegrees / 15;

    if (event->orientation() == Qt::Vertical)
    {
        if(numSteps<0)
        {
            zoomFactor = zoomFactor*2;
        }
        else
        {
            zoomFactor = zoomFactor/2;
        }
    }
    event->accept();
}

void Planets::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        mouseDown=1;
        mouseDownX=event->x()-(XShift/zoomFactor);
        mouseDownY=event->y()-(YShift/zoomFactor);
    }
    if(event->button()==Qt::RightButton)
    {
        planetSize*=2;
        if(planetSize>1000)
        {
            planetSize=1;
        }
    }
    if(event->button()==Qt::MiddleButton)
    {
        currentPlanet++;
        if(currentPlanet>planets.size()-1)
        {
            currentPlanet=0;
        }
    }
}

void Planets::mouseMoveEvent(QMouseEvent *event)
{
    if(mouseDown)
    {
        XShift = (event->x()-mouseDownX)*zoomFactor;
        YShift = (event->y()-mouseDownY)*zoomFactor;
    }
    mouseLocX = event->x();
    mouseLocY = event->y();

}

void Planets::mouseReleaseEvent(QMouseEvent *event)
{
    mouseDown=0;
}



double Planets::calculateXForce(const unsigned int& current) const
{
    double returnForce=0;
    for(unsigned int i=0;i<planets.size();i++)
    {
        if(i!=current)
        {
            returnForce+=planets.at(current)->calculateXForce(*planets.at(i));
        }
    }
    return returnForce;
}

double Planets::calculateYForce(const unsigned int& current) const
{
    double returnForce = 0;
    for(unsigned int i=0;i<planets.size();i++)
    {
        if(i!=current)
        {
            returnForce += planets.at(current)->calculateYForce(*planets.at(i));
        }
    }
    return returnForce;
}



