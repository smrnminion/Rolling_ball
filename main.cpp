/**
 * @file main.cpp
 * @brief Основной исполняемый файл для демонстрации вычитания фона с использованием шара.
 *
 * Этот файл содержит основную функцию, которая демонстрирует, как использовать
 * класс RollingBall и связанные функции для вычитания фона из изображения.
 * Пользователь задает путь к изображению, параметры шара и настройки вывода.
 */

#include <iostream>
#include "rolling_ball.h"
#include <opencv2/opencv.hpp>

/**
 * @brief Основная функция для демонстрации вычитания фона из изображения.
 *
 * Запрашивает у пользователя путь к изображению, размер радиуса для шара,
 * указание, является ли фон светлым, и нужно ли показывать только фон.
 * Обрабатывает изображение с использованием заданных параметров и отображает результаты.
 *
 * @return Возвращает 0 при успешном выполнении и 1 при ошибке загрузки изображения.
 */
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
