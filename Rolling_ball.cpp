#include "rolling_ball.h"
#include <algorithm>
#include <cmath>

RollingBall::RollingBall(int radius) {
    shrinkfactor = radius > 100 ? 8 : (radius > 30 ? 4 : (radius > 10 ? 2 : 1));
    int arctrimper = radius > 100 ? 40 : (radius > 30 ? 32 : 24);
    build(radius, arctrimper, shrinkfactor);
}

void RollingBall::build(int radius, int arctrimper, int shrinkfactor) {
    int sballradius = radius / shrinkfactor;
    sballradius = std::max(1, sballradius);
    int rsquare = sballradius * sballradius;
    int diam = sballradius * 2;
    int xtrim = int(arctrimper * sballradius / 100);
    int halfwidth = sballradius - xtrim;
    width = 2 * halfwidth + 1;
    data.resize(width * width, 0);
    int p = 0;
    int xval, yval, temp;
    for (int y = 0; y < width; ++y) {
        for (int x = 0; x < width; ++x) {
            xval = x - halfwidth;
            yval = y - halfwidth;
            temp = rsquare - (xval * xval) - (yval * yval);
            data[p++] = temp > 0 ? std::sqrt(temp) : 0;
        }
    }
}

cv::Mat roll_ball(RollingBall& ball, cv::Mat& smallImage) {
    int width = smallImage.cols;
    int height = smallImage.rows;
    cv::Mat background = cv::Mat::zeros(height, width, CV_32FC1);
    smallImage.convertTo(smallImage, CV_32FC1);
    std::vector<float> pixels;
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            pixels.push_back(smallImage.at<float>(j, i));
        }
    }
    std::vector<float> z_ball = ball.data;
    int ball_width = ball.width;
    int radius = int(ball_width / 2);
    std::vector<float> cache;
    cache.resize(width * ball_width);
    int next_line_to_write_in_cache, next_line_to_read, src, dest, x_0, y_0, x_ball_0, y_ball_0, x_end, y_end, y_ball, cache_pointer, bp, p;
    float z, z_reduced, z_min;
    for (int y = -radius; y < height + radius; y++) {
        next_line_to_write_in_cache = (y + radius) % ball_width;
        next_line_to_read = y + radius;
        if (next_line_to_read < height) {
            src = next_line_to_read * width;
            dest = next_line_to_write_in_cache * width;
            std::copy(pixels.begin() + src, pixels.begin() + src + width, cache.begin() + dest);
            for (int i = src; i < src + width; i++)
            {
                pixels[i] = float(-INT_MAX);
            }
        }

        y_0 = std::max(0, y - radius);
        y_ball_0 = y_0 - y + radius;
        y_end = y + radius;
        if (y_end >= height)
            y_end = height - 1;
        for (int x = -radius; x < width + radius; x++) {
            z = float(INT_MAX);
            x_0 = std::max(0, x - radius);
            x_ball_0 = x_0 - x + radius;
            x_end = x + radius;
            if (x_end >= width)
                x_end = width - 1;
            y_ball = y_ball_0;
            for (int yp = y_0; yp < y_end + 1; yp++) {
                cache_pointer = (yp % ball_width) * width + x_0;
                bp = x_ball_0 + y_ball * ball_width;
                for (int xp = x_0; xp < x_end + 1; xp++) {
                    z_reduced = cache[cache_pointer] - z_ball[bp];
                    if (z > z_reduced)
                        z = z_reduced;
                    cache_pointer += 1;
                    bp += 1;
                }
                y_ball += 1;
            }
            y_ball = y_ball_0;
            for (int yp = y_0; yp < y_end + 1; yp++) {
                p = x_0 + yp * width;
                bp = x_ball_0 + y_ball * ball_width;
                for (int xp = x_0; xp < x_end + 1; xp++) {
                    z_min = z + z_ball[bp];
                    if (pixels[p] < z_min)
                        pixels[p] = z_min;
                    p += 1;
                    bp += 1;
                }
                y_ball += 1;
            }

        }
    }
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            background.at<float>(j, i) = pixels[j * smallImage.cols + i];
        }
    }
    return background;
};


cv::Mat rolling_ball_background(cv::Mat img, int radius, bool lightbackground, bool returnbackgroung) {
    bool invert = false;
    if (lightbackground)
        invert = true;
    RollingBall ball(radius);
    cv::Mat smallImage;
    cv::resize(img, smallImage, cv::Size(), 1.0 / ball.shrinkfactor, 1.0 / ball.shrinkfactor, cv::INTER_AREA);
    if (invert)
        smallImage = 255 - smallImage;
    cv::Mat sbackground = roll_ball(ball, smallImage);
    cv::Mat background;
    cv::resize(sbackground, background, img.size(), 0, 0, cv::INTER_NEAREST);
    //cv::resize(sbackground, background, img.size(), 0, 0, cv::INTER_LINEAR);
    //cv::resize(sbackground, background, img.size(), 0, 0, cv::INTER_CUBIC);
    background.convertTo(background, CV_8UC1);
    cv::Mat substracted_background;
    if (invert)
        substracted_background = 255 - ((255 - img) - background);
    else
        substracted_background = img - background;
    if (returnbackgroung)
        return background;
    else
        return substracted_background;
}
