
#ifndef ROLLING_BALL_H
#define ROLLING_BALL_H

#include <opencv2/opencv.hpp>
#include <vector>
/**
 * @brief Класс для создания структуры "шара" для вычитания фона.
 * @details Этот класс создает структуру "шара", которая может быть использована для моделирования
 * удаления фона из изображений. "Шар" представляет собой матрицу значений, имитирующую объемный шар, который
 * катится под изображением для удаления фоновых элементов.
 */
class RollingBall {
public:
    std::vector<float> data; ///< Вектор, содержащий "высоты" шара.
    int width; ///< Ширина участка (patch width), используемая для обработки изображений.
    int shrinkfactor; ///< Коэффициент сжатия, используемый для оптимизации обработки.

    /**
     * @brief Конструктор класса RollingBall.
     * @param radius Радиус шара, определяющий его начальный размер.
     */
    RollingBall(int radius);

private:
    /**
     * @brief Генерирует структуру "шара".
     * @param radius Радиус "шара".
     * @param arctrimper Процентное усечение арки "шара".
     * @param shrinkfactor Коэффициент сжатия для оптимизации.
     */
    void build(int radius, int arctrimper, int shrinkfactor);
};

/**
 * @brief Класс для обработки изображений с использованием RollingBall.
 */
class RollingBallProcessor {
public:
    /**
     * @brief Конструктор класса RollingBallProcessor.
     * @param radius Радиус шара, используемый для обработки.
     * @param lightbackground Определяет, обрабатывается ли изображение с светлым фоном.
     * @param returnbackground Возврат фона вместо вычитанного изображения.
     */
    RollingBallProcessor(int radius, bool lightbackground = false, bool returnbackground = false);

    /**
     * @brief Выполняет вычитание фона для изображений с помощью метода прокатывания шара.
     * @param img Исходное изображение для обработки.
     * @return Обработанное изображение или фон.
     */
    cv::Mat rolling_ball_background(cv::Mat img);

private:
    RollingBall ball; ///< Экземпляр RollingBall для использования в обработке.
    bool lightbackground; ///< Флаг для обработки светлого фона.
    bool returnbackground; ///< Флаг для возврата фона.

    /**
     * @brief Применяет "шар" к маленькому изображению для вычитания фона.
     * @param smallImage Уменьшенное изображение для обработки.
     * @return Матрица, представляющая фон изображения.
     */
    static cv::Mat roll_ball(RollingBall& ball, cv::Mat& smallImage);
};

#endif // ROLLING_BALL_H
