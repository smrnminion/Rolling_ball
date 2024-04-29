
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
     * @param shrinkfactor Коэффициент сжатия для оптимизации размера.
     */
    void build(int radius, int arctrimper, int shrinkfactor);
};

/**
 * @brief Прокатывет "шар" по изображению для вычитания фона.
 * @param ball Объект RollingBall, содержащий данные "шара".
 * @param smallImage Уменьшенное изображение, к которому применяется "шар".
 * @return Матрица, представляющая фон изображения.
 */
cv::Mat roll_ball(RollingBall& ball, cv::Mat& smallImage);

/**
 * @brief Выполняет вычитание фона у изображений с помощью метода прокатывания шара.
 * @param img Исходное изображение для обработки.
 * @param radius Радиус "шара".
 * @param lightbackground Указывает, является ли фон светлым.
 * @param returnbackground Возвращать ли фон вместо вычитанного изображения.
 * @return Обработанное изображение или фон, в зависимости от параметра returnbackground.
 */
cv::Mat rolling_ball_background(cv::Mat img, int radius, bool lightbackground = false, bool returnbackground = false);

#endif // ROLLING_BALL_H
