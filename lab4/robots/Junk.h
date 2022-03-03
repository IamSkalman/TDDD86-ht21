/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef JUNK_H
#define JUNK_H

#include "Unit.h"
#include <QGraphicsScene>
#include "Robot.h"

class Junk : public Robot {
public:
    /*
     * Constructor of Junk, calls
     * on Robot()
     */
    Junk();

    /*
     * Constructor of Junk, calls
     * on Robot(p)
     */
    Junk(const Point& p);

    /*
    * Draws this junk onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const override;

    /*
     * Overrides Robots doCrash()
     */
    void doCrash() override;

    /*
     * Overrides Robots canMove(),
     * always return false.
     */
    bool canMove() const override;

    /*
     * Overrides Robots justCrashed(),
     * always return false.
     */
    bool justCrashed() const override;

    /*
     * Overrides Robots moveTowards(),
     */
    void moveTowards(const Unit &) override;

    /*
     * Overrides Robot* clone(),
     * return the pointer of a clone of this Junk
     */
    virtual Junk* clone() const override;


};

#endif // JUNK_H
