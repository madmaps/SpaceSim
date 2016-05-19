#ifndef PARTICALS_H
#define PARTICALS_H

class Particals
{
public:
    Particals();
    Particals(double inLocationX, double inLocationY, int inMass);
    Particals(double inLocationX, double inLocationY, double inSpeedX,double inSpeedY,int inMass);
    void combine(Particals& inPartical);
    void addForce(const double& inXForce,const double& inYForce);
    void updateLocation();
    double calculateXForce(const Particals& inPartical)const;
    double calculateYForce(const Particals &inPartical)const;

    double getX()const;
    double getY()const;
    double getDiameter()const;
    double getSpeedX() const;
    double getSpeedY() const;
    int getMass() const;

private:
    void calculateDiameter();
    int mass;
    double diameter;
    double locationX;
    double locationY;
    double speedX;
    double speedY;
    static double gravityForce;
    static double massDiameterRatio;
};

#endif // PARTICALS_H
