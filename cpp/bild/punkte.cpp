#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;

int main() {
    int size = 600;
    int n = 51;
    int radius = 500; // groß, damit Viertelkreis sichtbar

    Mat img(size, size, CV_8UC3, Scalar(255, 255, 255));

    // Zentrum unten links (Ecke!)
    int cx = 0;
    int cy = size - 1;

    // Mittelpunkt zeichnen
    circle(img, Point(cx, cy), 6, Scalar(255, 0, 0), -1);
    putText(img, "Center", Point(cx + 10, cy - 10),
            FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 0, 0), 1);

    for (int i = 0; i < n-1; i++) {
        double angle = (M_PI / 2.0) * i / (n - 1);

        int x = cx + int(radius * cos(angle));
        int y = cy - int(radius * sin(angle));

        // Punkt zeichnen
        circle(img, Point(x, y), 5, Scalar(0, 0, 0), -1);

        // Nummer
        int offset = 10;
        
        

        if (i % 2 == 0) {
            // außen / rechts oben
            int xp = cx + int((radius + offset) * cos(angle));
            int yp = cy - int((radius + offset) * sin(angle));
            putText(img,
                    to_string(i+150),
                    Point(xp, yp),
        
                    FONT_HERSHEY_SIMPLEX,
                    0.5,
                    Scalar(0, 0, 255),
                    1);
        }
        else {
            // etwas nach innen / links unten
            int xi = cx + int((radius - 20- offset) * cos(angle));
            int yi = cy - int((radius -20- offset) * sin(angle));

            putText(img,
                    to_string(i+150),
                    Point(xi, yi),
                    FONT_HERSHEY_SIMPLEX,
                    0.5,
                    Scalar(0, 0, 255),
                    1);
        } 
    }

    imwrite("viertelkreis_ecke_4.png", img);
    waitKey(0);

    return 0;
}