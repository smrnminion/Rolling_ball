#include <iostream>
#include "rolling_ball.h"
#include <opencv2/opencv.hpp>

int main() {
    std::string imagePath;
    int radius;
    bool lightBackground, showBackground;

    std::cout << "Enter path to the image: ";
    std::cin >> imagePath;

    cv::Mat img = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);
    if (img.empty()) {
        std::cerr << "Failed to load image" << std::endl;
        return 1;
    }

    std::cout << "Enter radius of the rolling ball (int): ";
    std::cin >> radius;

    std::cout << "Light background (0 = no, 1 = yes): ";
    std::cin >> lightBackground;

    std::cout << "Show backgound (0 = no, 1 = yes): ";
    std::cin >> showBackground;

    cv::Mat processedImage = rolling_ball_background(img, radius, lightBackground, showBackground);

    if (!showBackground) {
        cv::imshow("Original Image", img);
        cv::imshow("Substracted Background Image", processedImage);
        cv::waitKey(0);
    } else {
        cv::imshow("Original Image", img);
        cv::imshow("Background", processedImage);
        cv::waitKey(0);
    }

    return 0;
}
