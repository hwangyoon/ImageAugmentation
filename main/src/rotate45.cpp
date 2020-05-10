#include "../include/rotate45.h"

QImage Rotate45::processImage(const QImage *workingModel) {
    int32_t cols = workingModel->width();
    int32_t rows = workingModel->height();
    QImage rotatedPicture(rows + cols, cols + rows, workingModel->format());
    for (int32_t i = 0; i < cols; i++) {
        for (int32_t j = 0; j < rows; j++) {
            if (direct == CLOCKWISE45) {
                rotatedPicture.setPixel(i - j + rows, i + j, workingModel->pixel(QPoint(i,j)));
                rotatedPicture.setPixel(i - j + rows - 1, i + j, workingModel->pixel(QPoint(i,j)));
            }
            else {
                rotatedPicture.setPixel(i + j,j - i + cols, workingModel->pixel(QPoint(i,j)));
                rotatedPicture.setPixel(i + j,j - i + cols - 1,workingModel->pixel(QPoint(i,j)));
            }
        }
    }
    if (direct == CLOCKWISE45) {
         blur(rotatedPicture, QPoint(rows, 0), QPoint(cols + rows, cols),
              QPoint(cols, cols + rows), QPoint(0, rows));
    } else {
         blur(rotatedPicture, QPoint(cols, 0), QPoint(cols + rows, rows),
              QPoint(rows, cols + rows), QPoint(0, cols));
    }
    return rotatedPicture;
}

static std::pair<double, double> findCoord(QPoint A, QPoint B, QPoint S) {
    double a = (A.y() - B.y());
    double b = (B.x() - A.x());
    double c = (A.x()*B.y() - B.x()*A.y());
    double c1 = a*S.y() - b*S.x();
    return std::make_pair((-a*c - b*c1)/(a*a + b*b),
                          (a*c1 - b*c)/(a*a + b*b));
}

QImage& Rotate45::blurLeftUpperAngle(QImage& image,
                              int length, int height) {
    int xp, yp;
    double tanAngle = static_cast<double>(length)/height;
    for (xp = 0; xp < length; xp++) {
        yp = (length - xp) / tanAngle;
        int yp_new = yp;
        while (yp_new >= 0) {
            std::pair<double, double> coord = findCoord(QPoint(0, height),
                                                         QPoint(length, 0),
                                                         QPoint(xp, yp_new));
            QRgb value = image.pixel(QPoint(ceil(coord.first), ceil(coord.second)));
            image.setPixel(xp, yp_new, value);
            --yp_new;
        }
    }
    return image;
}

QImage& Rotate45::blurRightUpperAngle(QImage& image,
                              int length, int height) {
    int xp, yp;
    double tanAngle = static_cast<double>(length)/height;
    for (xp = image.width() - length; xp < image.width(); xp++) {
        yp = (xp - image.width() + length) / tanAngle;
        int yp_new = yp;
        while (yp_new >= 0) {
            std::pair<double, double> coord = findCoord(QPoint(image.width(), height),
                                                         QPoint(image.width() - length, 0),
                                                         QPoint(xp, yp_new));
            QRgb value = image.pixel(QPoint(floor(coord.first), ceil(coord.second)));
            image.setPixel(xp, yp_new, value);
            --yp_new;
        }
    }
    return image;
}

QImage& Rotate45::blurLeftBottomAngle(QImage& image,
                              int length, int height) {
    int xp, yp;
    double tanAngle = static_cast<double>(height)/length;
    for (xp = 0; xp < length; xp++) {
        yp = image.height() - (length - xp) * tanAngle;
        int yp_new = yp;
        while (yp_new < image.height()) {
            std::pair<double, double> coord = findCoord(QPoint(0, image.height() - height),
                                                         QPoint(length, image.height()),
                                                         QPoint(xp, yp_new));
            QRgb value = image.pixel(QPoint(ceil(coord.first), floor(coord.second)));
            image.setPixel(xp, yp_new, value);
            ++yp_new;
        }
    }
    return image;
}

QImage& Rotate45::blurRightBottomAngle(QImage& image,
                              int length, int height) {
    int xp, yp;
    double tanAngle = static_cast<double>(height)/length;
    for (xp = image.width() - length; xp < image.width(); xp++) {
        yp = image.height() - (xp - image.width() + length) * tanAngle;
        int yp_new = yp;
        while (yp_new < image.height()) {
            std::pair<double, double> coord = findCoord(QPoint(image.width() - length, image.height()),
                                                         QPoint(image.width(), image.height() - height),
                                                         QPoint(xp, yp_new));
            QRgb value = image.pixel(QPoint(floor(coord.first), floor(coord.second)));
            image.setPixel(xp, yp_new, value);
            ++yp_new;
        }
    }
    return image;
}

QImage& Rotate45::blur(QImage& image,
                       QPoint leftUpperAngle,
                       QPoint rightUpperAngle,
                       QPoint rightBottomAngle,
                       QPoint leftBottomAngle) {
    const int Inaccuracy = 5;
    blurLeftUpperAngle(image,
                          leftUpperAngle.x() - leftBottomAngle.x() + Inaccuracy,
                          leftBottomAngle.y() - leftUpperAngle.y() + Inaccuracy);
    blurRightUpperAngle(image,
                           rightUpperAngle.x() - leftUpperAngle.x() + Inaccuracy,
                           rightUpperAngle.y() - leftUpperAngle.y() + Inaccuracy);
    blurLeftBottomAngle(image,
                           rightBottomAngle.x() - leftBottomAngle.x() + Inaccuracy,
                           rightBottomAngle.y() - leftBottomAngle.y() + Inaccuracy);
    blurRightBottomAngle(image,
                            rightUpperAngle.x() - rightBottomAngle.x() + Inaccuracy,
                            rightBottomAngle.y() - rightUpperAngle.y() + Inaccuracy);
    return image;
}

Rotate45Builder::Rotate45Builder() {
    direct = CLOCKWISE45;
}

Rotate45Builder Rotate45Builder::setDirection(Direction45 d) {
    this->direct = d;
    return *this;
}

Rotate45 Rotate45Builder::build() {
    Rotate45 algo;
    algo.direct = this->direct;
    return algo;
}
