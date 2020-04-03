
#include "../include/dithering.h"
#include "../include/pixel.h"
void setError(Pixel pixel, int i, int j, std::vector<std::vector<Pixel>>& matrix) {
    //Все значения берутся из фильтра Джарвиса, Джудиса, Нинке
    //Храним всего 2 слоя, так как идейно динамика по скошенному профилю: идем только вправо и вниз
    if (j - 1 >= 0) {
        matrix[(i + 1) % 3][j - 1] += (pixel * 5) / 48;
        matrix[(i + 2) % 3][j - 1] += pixel >> 4;
        if (j - 2 >= 0) {
            matrix[(i + 1) % 3][j - 2] += pixel >> 4;
            matrix[(i + 2) % 3][j - 2] += pixel / 48;
        }
    }
    matrix[(i + 1) % 3][j] += (pixel * 7) / 48;
    matrix[(i + 2) % 3][j] += (pixel * 5) / 48;

    int rows = matrix[i % 3].size();
    if (j + 1 < rows) {
        matrix[i % 3][j + 1] += (pixel * 7) / 48;
        matrix[(i + 1) % 3][j + 1] += (pixel * 5) / 48;
        matrix[(i + 2) % 3][j + 1] += pixel >> 4;

        if (j + 2 < rows) {
            matrix[i % 3][j + 2] += (pixel * 5) / 48;
            matrix[(i + 1) % 3][j + 2] += pixel >> 4;
            matrix[(i + 2) % 3][j + 2] += pixel / 48;
        }
    }
}


QImage Dithering::processImage(const QImage* workingModel) {
    int32_t cols = workingModel->width();
    int32_t rows = workingModel->height();
    std::vector<std::vector<Pixel>> matrix(3, std::vector<Pixel>(rows));

    QImage ditheredPicture(cols, rows, workingModel->format());
    for (int32_t i = 0; i < cols; i++) {
        matrix[(i + 2) % 3].assign(rows, Pixel());
        for (int32_t j = 0; j < rows; j++) {
            Pixel new_pixel(workingModel->pixel(QPoint(i, j)));
            new_pixel += matrix[i % 3][j];
            Pixel error = new_pixel - new_pixel.round();
            setError(error, i, j, matrix);
            ditheredPicture.setPixelColor(QPoint(i, j), new_pixel.round().getRgb());
        }
    }
    return ditheredPicture;
}

Dithering DitheringBuilder::build() {
    Dithering* algo = new Dithering();
    return *algo;
}
