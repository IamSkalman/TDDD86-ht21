/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include "Junk.h"
#include "constants.h"

Junk::Junk() : Robot(){}

Junk::Junk(const Point& p) : Robot(p){}

Junk* Junk::clone() const{
    return new Junk(*this);
}

void Junk::draw(QGraphicsScene *scene) const {
    Point corner = asPoint();
    scene->addEllipse(QRectF(corner.x * UNIT_WIDTH, corner.y * UNIT_HEIGHT,
                             JUNK_RADIUS, JUNK_RADIUS), QPen(), QBrush(JUNK_COLOR));
}

void Junk::doCrash(){

}

bool Junk::canMove() const{
    return false;
}

bool Junk::justCrashed() const{
    return false;
}

void Junk::moveTowards(const Unit &){

}



