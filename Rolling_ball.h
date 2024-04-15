
#ifndef ROLLING_BALL_H
#define ROLLING_BALL_H

#include <opencv2/opencv.hpp>
#include <vector>

class RollingBall {
public:
    std::vector<float> data;
    int width, shrinkfactor;

    RollingBall(int radius);

private:
    void build(int radius, int arctrimper, int shrinkfactor);
};

cv::Mat roll_ball(RollingBall& ball, cv::Mat& smallImage);
cv::Mat rolling_ball_background(cv::Mat img, int radius, bool lightbackground = false, bool returnbackground = false);

#endif // ROLLING_BALL_H
