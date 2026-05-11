#pragma once
#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const double PI = 3.14159265358979323846;

vector<Point> points(int n, double r, int size) {
    vector<Point> result;
    result.reserve(n);

    int cx = size / 2;
    int cy = size / 2;

    for(int i = 0; i < n; i++) {
        int x = cx + int(r * cos(2.0 * PI * i / n));
        int y = cy + int(r * sin(2.0 * PI * i / n));
        result.push_back(Point(x, y));
    }

    return result;
}

void resizeToSquare(const string& inputPath,
                    const string& outputPath,
                    int targetSize)
{
    Mat img = imread(inputPath, IMREAD_GRAYSCALE);

    if(img.empty()) {
        cout << "Fehler beim Laden: " << inputPath << endl;
        return;
    }

    float scale = max(
        targetSize / (float)img.cols,
        targetSize / (float)img.rows
    );

    Mat resized;
    resize(img, resized, Size(), scale, scale, INTER_AREA);

    int x = (resized.cols - targetSize) / 2;
    int y = (resized.rows - targetSize) / 2;

    Mat cropped = resized(Rect(x, y, targetSize, targetSize));
    imwrite(outputPath, cropped);
}

void resizeToSquare(const string& inputPath, int targetSize) {
    resizeToSquare(inputPath, inputPath, targetSize);
}

void draw(Mat& input, int x1, int y1, int x2, int y2) {
    const double sigma = 0.6;
    const double strength =0.6;
    const int radius = int(3.0 * sigma);

    LineIterator it(input, Point(x1, y1), Point(x2, y2), 8);

    for(int k = 0; k < it.count; k++, ++it) {
        Point p = it.pos();

        for(int dy = -radius; dy <= radius; dy++) {
            int y = p.y + dy;
            if(y < 0 || y >= input.rows) continue;

            uchar* row = input.ptr<uchar>(y);

            for(int dx = -radius; dx <= radius; dx++) {
                int x = p.x + dx;
                if(x < 0 || x >= input.cols) continue;

                double d2 = dx * dx + dy * dy;
                double weight = exp(-d2 / (2.0 * sigma * sigma));

                row[x] = (uchar)(row[x] * (1.0 - strength * weight));
            }
        }
    }
}
double delta(const Mat& bild, const Mat& testen) {
    double sum = 0.0;
    int N = bild.rows * bild.cols;

    for(int y = 0; y < bild.rows; y++) {
        const uchar* p1 = bild.ptr<uchar>(y);
        const uchar* p2 = testen.ptr<uchar>(y);

        for(int x = 0; x < bild.cols; x++) {
            double d = (double)p1[x] - (double)p2[x];
            sum += d * d;
        }
    }

    return sum / N;
}
double draw_delta(const Mat& target,
                  Mat& input,
                  int x1, int y1,
                  int x2, int y2,
                  double currentError)
{
    const double sigma = 0.7;
    const double strength = 0.6;
    const int radius = int(3.0 * sigma);

    double newErrorSum = currentError * input.rows * input.cols;

    LineIterator it(input, Point(x1, y1), Point(x2, y2), 8);

    for(int k = 0; k < it.count; k++, ++it) {
        Point p = it.pos();

        for(int dy = -radius; dy <= radius; dy++) {
            int y = p.y + dy;
            if(y < 0 || y >= input.rows) continue;

            uchar* rowInput = input.ptr<uchar>(y);
            const uchar* rowTarget = target.ptr<uchar>(y);

            for(int dx = -radius; dx <= radius; dx++) {
                int x = p.x + dx;
                if(x < 0 || x >= input.cols) continue;

                double d2 = dx * dx + dy * dy;
                double weight = exp(-d2 / (2.0 * sigma * sigma));

                uchar oldPixel = rowInput[x];
                uchar targetPixel = rowTarget[x];

                double oldDiff = (double)targetPixel - (double)oldPixel;
                double oldSq = oldDiff * oldDiff;

                uchar newPixel = (uchar)(oldPixel * (1.0 - strength * weight));

                double newDiff = (double)targetPixel - (double)newPixel;
                double newSq = newDiff * newDiff;

                newErrorSum += newSq - oldSq;

                rowInput[x] = newPixel;
            }
        }
    }

    return newErrorSum / (input.rows * input.cols);
}

void mache_striche(const string& name,const string& n, int size, int nPins, int iterations, double radius) {
    
    
    string ordner ="alle_bilder/";
    string bild  = ordner+ name + n;
    
    vector<int> path;

    resizeToSquare(bild, size);

    Mat target = imread(bild, IMREAD_GRAYSCALE);


    Mat result(size, size, CV_8UC1, Scalar(255));

    vector<Point> pins = points(nPins, radius, size);

    int current = 0;

    path.push_back(current);
    double currentError = delta(target, result);

    for(int iter = 0; iter < iterations; iter++) {
        double bestError = 1e18;
        int bestPoint = -1;
        Mat bestImage;

        for(int next = 0; next < nPins; next++) {
            if(next == current) continue;

            Mat test = result.clone();

            double error = draw_delta(
                target,
                test,
                pins[current].x,
                pins[current].y,
                pins[next].x,
                pins[next].y,
                currentError
            );

            if(error < bestError) {
                bestError = error;
                bestPoint = next;
                bestImage = test.clone();
            }
        }

       if(bestError >= currentError) {
            cout << "Stop: keine Verbesserung mehr bei Iteration " << iter << endl;
            break;
        }

        result = bestImage;
        current = bestPoint;
        currentError = bestError;
        path.push_back(current);

        if(iter % 50 == 0) {
            cout << "Iteration " << iter
                << " Fehler: " << bestError
                << " Punkt: " << current
                << endl;

            imwrite("result_progress.png", result);
        }
    }
    

    imwrite(ordner + "strich_"+ name+n, result);
    
    ofstream file(ordner + name +"_path.txt");

    for(int i = 0; i < path.size(); i++) {
        file << path[i] << "\n";
    }

    cout << "Fertig. Ergebnis gespeichert als strich_"  + name + n<< endl;
}


