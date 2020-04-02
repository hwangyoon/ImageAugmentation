#include "../include/dithering.h"

struct Pixel {
    long long red = 0;
    long long green = 0;
    long long blue = 0;

    Pixel() = default;

    Pixel(int red, int green, int blue)
            : red(red), green(green), blue(blue) {}

    Pixel(long long red, long long green, long long blue)
            : red(red), green(green), blue(blue) {}

    explicit Pixel(QRgb colour)
            : red(qRed(colour)), green(qGreen(colour)), blue(qBlue(colour)) {}

    Pixel& operator+=(const Pixel& other) {
        red += other.red;
        green += other.green;
        blue += other.blue;
        return *this;
    }

    Pixel& operator-=(const Pixel& other) {
        red -= other.red;
        green -= other.green;
        blue -= other.blue;
        return *this;
    }

    Pixel& operator/=(int x) {
        red /= x;
        green /= x;
        blue /= x;
        return *this;
    }

    Pixel operator-(Pixel other) const {
        return Pixel(red - other.red, green - other.green, blue - other.blue);
    }

    Pixel operator*(int x) const {
        return Pixel(red * x, green * x, blue * x);
    }

    Pixel operator/(int x) const {
        return Pixel(red / x, green / x, blue / x);
    }

    Pixel operator>>(int x) const {
        return Pixel(red >> x, green >> x, blue >> x);
    }

     QRgb getRgb() {
        if (red > 255)
            red = 255;
        if (red < 0)
            red = 0;

        if (green > 255)
            green = 255;
        if (green < 0)
            green = 0;

        if (blue > 255)
            blue = 255;
        if (blue < 0)
            blue = 0;

        return qRgb(red, green, blue);
    }

    Pixel round() const {
        int redRound, greenRound, blueRound;
        if (255 - red > red) {
            redRound = 0;
        } else {
            redRound = 255;
        }

        if (255 - green > green) {
            greenRound = 0;
        } else {
            greenRound = 255;
        }
        if (255 - blue > blue) {
            blueRound = 0;
        } else {
            blueRound = 255;
        }
        return Pixel(redRound, greenRound, blueRound);
    }

};

void setError(Pixel pixel, int i, int j, std::vector<std::vector<Pixel>>& matrix) {
//Все значения берутся из фильтра Джарвиса, Джудиса, Нинке
//Храним всего 2 слоя, так как идейно динамика по скошенному профилю: идем только вправо и вниз
    if (j - 1 >= 0) {
        matrix[(i + 1) % 3][j - 1] += (pixel*5) / 48;
        matrix[(i + 2) % 3][j - 1] += pixel >> 4;
        if (j - 2 >= 0) {
            matrix[(i + 1) % 3][j - 2] += pixel >> 4;
            matrix[(i + 2) % 3][j - 2] += pixel / 48;
        }
    }
    matrix[(i + 1) % 3][j] += (pixel * 7) / 48;
    matrix[(i + 2) % 3][j] += (pixel*5) / 48;

    int rows = matrix[i % 3].size();
    if (j + 1 < rows) {
        matrix[i % 3][j + 1] += (pixel * 7) / 48;
        matrix[(i + 1) % 3][j + 1] += (pixel*5) / 48;
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
