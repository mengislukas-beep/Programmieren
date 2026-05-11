#include "helper_2.h"

#include <opencv2/opencv.hpp>



int main() {

    int size = 1000;
    int nPins = 200;
    int iterations = 2000;
    double radius = 450.0;

    mache_striche("pferd_9",".png", size, nPins, iterations, radius);

    return 0;
}
