#ifndef PLANETS_H
#define PLANETS_H

#include <QLabel>
#include <QWheelEvent>
#include <vector>
#include "particals.h"

class Planets : public QLabel
{
    Q_OBJECT
public:
    explicit Planets(QWidget *parent = 0);

signals:
    void doneUpdating();
public slots:
    void updateData();
protected:
    void paintEvent(QPaintEvent* event);
    void wheelEvent(QWheelEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    double calculateXForce(const unsigned int &current) const;
    double calculateYForce(const unsigned int& current) const;

    std::vector<Particals*> planets;
    double zoomFactor;
    int XShift;
    int YShift;
    int mouseDownX;
    int mouseDownY;
    bool mouseDown;
    int mouseLocX;
    int mouseLocY;
    int planetSize;
    int currentPlanet;
};

#endif // PLANETS_H
