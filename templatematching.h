#ifndef TEMPLATEMATCHING_H
#define TEMPLATEMATCHING_H

#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;
using namespace std;

class TemplateMatching {
private:

    Mat image, templ, imageColor;

public:

    TemplateMatching(const string& imagePath, const string& templPath) : image(imread(imagePath, IMREAD_GRAYSCALE)), templ(imread(templPath, IMREAD_GRAYSCALE)), imageColor(imread(imagePath)) {}

    pair<Mat, int> getPositionsOfTemplate(float threshold);
};

#endif // TEMPLATEMATCHING_H
