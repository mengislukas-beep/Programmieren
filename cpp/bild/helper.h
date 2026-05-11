#pragma once
#include <cmath>
#include <vector>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

const double PI = 3.14159265358979323846;
const double e = 2.718281828459045;

vector<vector<int>> points(int n, double r) {
    vector<vector<int>> result;

    for(int i = 0; i < n; i++) {
        result.push_back({int(r * cos(2 * PI * i / n)),int( r * sin(2 * PI * i / n))});
    }
    return result;

}   

#include <cmath>

double dist(int x_1, int y_1, int x_2, int y_2, int x_3, int y_3) {
    double numerator = std::abs(
        (y_2 - y_1) * x_3 -
        (x_2 - x_1) * y_3 +
        x_2 * y_1 -
        y_2 * x_1
    );

    double denominator = std::sqrt(
        (y_2 - y_1) * (y_2 - y_1) +
        (x_2 - x_1) * (x_2 - x_1)
    );

    return numerator / denominator;
}



void resizeToSquare(const std::string& inputPath,
                    const std::string& outputPath,
                    int targetSize)
{
    Mat img = imread(inputPath,IMREAD_GRAYSCALE);

    if (img.empty()) {
        std::cout << "Fehler beim Laden: " << inputPath << std::endl;
        return;
    }

    // 1. Skalierungsfaktor berechnen
    float scale = std::max(
        targetSize / (float)img.cols,
        targetSize / (float)img.rows
    );

    // 2. Resize (ohne Verzerrung)
    Mat resized;
    resize(img, resized, Size(), scale, scale);

    // 3. Crop zur Mitte
    int x = (resized.cols - targetSize) / 2;
    int y = (resized.rows - targetSize) / 2;

    Rect roi(x, y, targetSize, targetSize);
    Mat cropped = resized(roi);

    // 4. Speichern
    imwrite(outputPath, cropped);
}
void resizeToSquare(const std::string& inputPath,
                    int targetSize) {
    resizeToSquare(inputPath, inputPath, targetSize);
}

void draw(Mat& input, int x_1, int y_1, int x_2, int y_2) {
    double sigma = 0.5;

    for(int i = 0; i < input.cols; i++) {
        for(int j = 0; j < input.rows; j++) {
                        
            double d = dist(x_1, y_1, x_2, y_2, i, j);
            if(d > 10) continue;

            double weight = exp(-(d * d) / (2 * sigma * sigma));

            uchar& pixel = input.at<uchar>(j, i);  // Referenz!
            double strength = 0.6;

            pixel = (uchar)(pixel * (1.0 - weight*strength));
        }
    }
}

double delta(const cv::Mat& bild, const cv::Mat& testen) {
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


 