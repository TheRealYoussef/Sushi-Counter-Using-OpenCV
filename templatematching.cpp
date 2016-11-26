#include "templatematching.h"
#include <vector>
#include <algorithm>
#include <qdebug.h>
#include <fstream>
#include <cmath>

pair<Mat, int> TemplateMatching::getPositionsOfTemplate(float thresh) {
    Mat dst;
    vector<pair<float, Point> > allPoints;
    vector<Point> points;

    //Match template and normalize
    //CV_TM_CCOEFF_NORMED: highest values are matches
    matchTemplate(image, templ, dst, CV_TM_CCOEFF_NORMED);
    normalize(dst, dst, 0.0, 1.0, NORM_MINMAX, -1, Mat());

    //Get local maximumums and store them in allPoints
    for (int i = 0; i < dst.rows; i += templ.rows) {
        for (int j = 0; j < dst.cols; j += templ.cols) {
            float maxPixel = 0.f;
            int row, col;
            for (int k = 0; k < templ.rows; ++k) {
                if (i + k >= dst.rows)
                    break;
                for (int l = 0; l < templ.cols; ++l) {
                    if (j + l >= dst.cols)
                        break;
                    if (dst.at<float>(i + k, j + l) > maxPixel) {
                        maxPixel = dst.at<float>(i + k, j + l);
                        row = i + k;
                        col = j + l;
                    }
                }
            }
            if (maxPixel > thresh)
                allPoints.push_back(make_pair(maxPixel, Point(col, row)));
        }
    }

    //Sort allPoints
    bool swapped;
    do {
        swapped = false;
        for (int i = 1; i < (int)allPoints.size(); ++i) {
            if (allPoints[i].first > allPoints[i - 1].first) {
                swap(allPoints[i], allPoints[i - 1]);
                swapped = true;
            }
        }
    } while (swapped);

    //Remove repititions from allPoints and store correct subset in points
    for (int i = 0; i < (int)allPoints.size(); ++i) {
        bool equal = false;
        for (int j = 0; j < (int)points.size() && !equal; ++j) {
            if (sqrt(pow(allPoints[i].second.x - points[j].x, 2) + pow(allPoints[i].second.y - points[j].y, 2)) < min(templ.rows, templ.cols) / 1.5)
                equal = true;
        }
        if (!equal) {
            points.push_back(allPoints[i].second);
        }
    }

    //Add rectangles
    for (int i = 0; i < (int)points.size(); ++i)
        rectangle(imageColor, points[i], Point(points[i].x + templ.cols, points[i].y + templ.rows), Scalar(0, 0, 0), 2);

    return make_pair(imageColor, (int)points.size());
}
