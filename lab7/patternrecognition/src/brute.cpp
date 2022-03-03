/*
 * TDDD86 Pattern Recognition
 * This program computes and plots all line segments involving 4 points
 * in a file using Qt.
 */

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include "Point.h"



inline void render_points(QGraphicsScene* scene, const vector<Point>& points) {
    for(const auto& point : points) {
        point.draw(scene);
    }
}


inline void render_line(QGraphicsScene* scene, const Point& p1, const Point& p2) {
    p1.lineTo(scene, p2);
}

