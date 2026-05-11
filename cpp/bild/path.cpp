#include "helper_2.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <termios.h>
#include <unistd.h>

using namespace std;

char getch() {
    termios oldt, newt;
    char ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

int main() {
    int size = 1000;
    int nPins = 200;
    double radius = 450.0;

    string ordner = "alle_bilder/";
    string name = "pferd_9path";

    vector<int> path;
    ifstream file(ordner + name + ".txt");

    if (!file.is_open()) {
        cout << "Datei nicht gefunden: " << ordner + name + ".txt" << endl;
        return 1;
    }

    int value;
    while (file >> value) {
        path.push_back(value);
    }

    file.close();
    int m = path.size();

    if (path.size() < 2) {
        cout << "Path-Datei ist leer oder zu kurz." << endl;
        return 1;
    }

    vector<Point> pins = points(nPins, radius, size);

    int i = 420;

    while (true) {
        char taste = getch();

        if (taste == 27) {
            getch();
            char pfeil = getch();

            if (pfeil == 'C') {
                i++;
            }

            if (pfeil == 'D') {
                i--;
            }
        }

        if (taste == ' ') {
            i++;
        }
    

        if (taste == 'a') {
            i--;
        }
        if (taste == 'd') {
            i++;
        }

        if (taste == 'q') {
            break;
        }

        if (i < 1) {
            i = 1;
        }
        if (i >= (int)path.size()) {
            i = path.size() - 1;
        }

        Mat bild(size, size, CV_8UC1, Scalar(255));

        // Nur Dummy-Bild, weil draw_delta ein target braucht
        Mat target(size, size, CV_8UC1, Scalar(255));

        double error = 0.0;

        for (int j = 1; j <= i; j++) {
            int a = path[j - 1];
            int b = path[j];

            if (a < 0 || a >= nPins || b < 0 || b >= nPins) {
                cout << "Falscher Pin: " << a << " " << b << endl;
                continue;
            }

            error = draw_delta(
                target,
                bild,
                pins[a].x,
                pins[a].y,
                pins[b].x,
                pins[b].y,
                error
            );
        }

        imwrite("striche.png", bild);

        cout << "i = " << i << " / " << path.size() - 1 << "    " <<200 - path[i] << endl;
    }

    return 0;
}