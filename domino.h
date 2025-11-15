#ifndef DOMINO_H
#define DOMINO_H

#include <cairomm/cairomm.h>
#include <cmath>

typedef ::Cairo::RefPtr<::Cairo::Context> CairoContext;

const int DOMINO_SIDE = 60;
const int RIVET_RADIUS = 10;
const double PI = 3.14159265358979323846;

class Domino {
public:
    int topValue, bottomValue;
    double posX, posY;
    int rotation;

    Domino();

    void draw(const CairoContext& cr);

    bool domino_is_clicked(double clickX, double clickY);
    bool rivet_is_clicked(double clickX, double clickY);
};

#endif
