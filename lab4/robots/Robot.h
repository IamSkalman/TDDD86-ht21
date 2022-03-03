/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "Unit.h"
#include <QGraphicsScene>

class Robot : public Unit {
    bool crashed = false;

public:

    /*
     * Constructor for Robot
     */
    Robot();

    /*
     * Constructor for Robot, based on a Point
     */
    Robot(const Point& p);

    /*
     * Return whether the robot can move.
     */
    virtual bool canMove() const;

    /*
     * Overrides Unit* clone()
     * Return the Pointer of a clone of this Robot
     */
    virtual Robot* clone() const override;

    /*
     * Crashes and remembers it
     */
    virtual void doCrash();

    /*
     * Return whether the robot crashed
     */
    virtual bool justCrashed() const;


    /*
    * Draws this robot onto the given QGraphicsScene.
    */
    virtual void draw(QGraphicsScene* scene) const override;


};

#endif // ROBOT_H
