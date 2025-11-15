#include "domino.h"
#include <iostream>
#include <functional>

#define _USE_MATH_DEFINES
#include <cmath>


Domino::Domino()
{
    topValue = 2;
    bottomValue = 5;
    posX = 300;
    posY = 200;
    rotation = 0;
}

static void draw_dot(const CairoContext& cr, double x, double y, double radius)
{
    cr->arc(x, y, radius, 0, 2*PI);
    cr->fill();
}

void Domino::draw(const CairoContext& cr)
{
    cr->save();
    cr->translate(posX, posY);
    cr->rotate(rotation * PI / 180.0);

    double width = DOMINO_SIDE;
    double height = 2 * DOMINO_SIDE;

    cr->set_source_rgb(1,1,1);
    cr->rectangle(-width/2, -height/2, width, height);
    cr->fill_preserve();
    cr->set_source_rgb(0,0,0);
    cr->stroke();

    cr->move_to(-width/2, 0);
    cr->line_to(width/2, 0);
    cr->stroke();

    const double DOT_RADIUS = 6;
    const double dotOffsetX = width * 0.25;
    const double dotOffsetY = DOMINO_SIDE * 0.25;

    std::function<void(int, double)> drawPips;
    drawPips = [&](int numPips, double centerY)
    {
        switch(numPips)
        {
            case 0: 
                break;

            case 1:
                cr->arc(0, centerY, DOT_RADIUS, 0, 2*PI);
                cr->fill();
                break;

            case 2:
                cr->arc(-dotOffsetX, centerY, DOT_RADIUS, 0, 2*PI); cr->fill();
                cr->arc(dotOffsetX, centerY, DOT_RADIUS, 0, 2*PI); cr->fill();
                break;

            case 3:
                cr->arc(-dotOffsetX, centerY - dotOffsetY, DOT_RADIUS, 0, 2*PI); cr->fill();
                cr->arc(0, centerY, DOT_RADIUS, 0, 2*PI); cr->fill();
                cr->arc(dotOffsetX, centerY + dotOffsetY, DOT_RADIUS, 0, 2*PI); cr->fill();
                break;

            case 4:
                cr->arc(-dotOffsetX, centerY - dotOffsetY, DOT_RADIUS, 0, 2*PI); cr->fill();
                cr->arc(dotOffsetX, centerY - dotOffsetY, DOT_RADIUS, 0, 2*PI); cr->fill();
                cr->arc(-dotOffsetX, centerY + dotOffsetY, DOT_RADIUS, 0, 2*PI); cr->fill();
                cr->arc(dotOffsetX, centerY + dotOffsetY, DOT_RADIUS, 0, 2*PI); cr->fill();
                break;

            case 5:
                drawPips(4, centerY);
                cr->arc(0, centerY, DOT_RADIUS, 0, 2*PI); cr->fill();
                break;

            case 6:
                cr->arc(-dotOffsetX, centerY - dotOffsetY, DOT_RADIUS, 0, 2*PI); cr->fill();
                cr->arc(dotOffsetX, centerY - dotOffsetY, DOT_RADIUS, 0, 2*PI); cr->fill();
                cr->arc(-dotOffsetX, centerY, DOT_RADIUS, 0, 2*PI); cr->fill();
                cr->arc(dotOffsetX, centerY, DOT_RADIUS, 0, 2*PI); cr->fill();
                cr->arc(-dotOffsetX, centerY + dotOffsetY, DOT_RADIUS, 0, 2*PI); cr->fill();
                cr->arc(dotOffsetX, centerY + dotOffsetY, DOT_RADIUS, 0, 2*PI); cr->fill();
                break;
        }
    };

    cr->set_source_rgb(0,0,0);
    drawPips(topValue, -DOMINO_SIDE * 0.5);
    drawPips(bottomValue, DOMINO_SIDE * 0.5);

    cr->restore();
}
bool Domino::domino_is_clicked(double clickX, double clickY)
{
    double dx = clickX - posX;
    double dy = clickY - posY;
    
    double angle = -rotation * PI / 180.0;
    double rotatedX = dx * cos(angle) - dy * sin(angle);
    double rotatedY = dx * sin(angle) + dy * cos(angle);
    
    return (fabs(rotatedX) <= DOMINO_SIDE/2 &&
            fabs(rotatedY) <= (2*DOMINO_SIDE)/2);
}

bool Domino::rivet_is_clicked(double clickX, double clickY)
{
    double dx = clickX - posX;
    double dy = clickY - posY;
    double distance = sqrt(dx*dx + dy*dy);
    return distance <= RIVET_RADIUS;
}

