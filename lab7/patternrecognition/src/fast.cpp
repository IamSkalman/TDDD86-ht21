#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include "Point.h"


// constants
static const int SCENE_WIDTH = 512;
static const int SCENE_HEIGHT = 512;



inline void render_points(QGraphicsScene* scene, const vector<Point>& points) {
    for(const auto& point : points) {
        point.draw(scene);
    }
}


inline void render_line(QGraphicsScene* scene, const Point& p1, const Point& p2) {
    p1.lineTo(scene, p2);
}


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // open file
    string filename = "input100.txt";
    ifstream input;
    input.open(filename);

    // the vector of points
    vector<Point> points;

    // read points from file
    int N;
    int x;
    int y;

    input >> N;

    for (int i = 0; i < N; ++i) {
        input >> x >> y;
        points.push_back(Point(x, y));
    }
    input.close();

    // setup graphical window
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    view->setScene(scene);
    // draw points to screen all at once
    render_points(scene, points);
    view->scale(1, -1); //screen y-axis is inverted
    view->resize(view->sizeHint());
    view->setWindowTitle("Fast Pattern Recognition");
    view->show();

    // sort points by natural order
    // makes finding endpoints of line segments easy
    sort(points.begin(), points.end());
    auto begin = chrono::high_resolution_clock::now();


    int nPoints = points.size();
    for(int p = 0; p < nPoints - 1; p++){

        map<double, vector<Point>> slopeMap;

        for(int q = p+1; q < nPoints; q++){
            slopeMap[points[p].slopeTo(points[q])].push_back(points[q]);
        }

        for(const auto& line: slopeMap){
            if(line.second.size() > 2){
                render_line(scene, points[p], *(line.second.end() - 1)); //line.second.end() pekar på en nullptr (efter sista elementet)
                a.processEvents();
            }

        }

    }



    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    return a.exec(); // start Qt event loop
}







