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
    blur(rotatedPicture, QPoint(rows, 0), QPoint(cols + rows, cols), QPoint(cols, cols + rows), QPoint(0, rows));
    return rotatedPicture;
}

static std::pair<double, double> find_coord(QPoint A, QPoint B, QPoint S) {
    double a = (A.y() - B.y());
    double b = (B.x() - A.x());
    double c = (A.x()*B.y() - B.x()*A.y());
    double c1 = a*S.y() - b*S.x();
    return std::make_pair((-a*c - b*c1)/(a*a + b*b),
                          (a*c1 - b*c)/(a*a + b*b));
}

QImage& Rotate45::blur_left_upper_angle(QImage& img,
                              int len, int height) {
    int xp, yp;
    double tan_angle = static_cast<double>(len)/height;
    for (xp = 0; xp < len; xp++) {
        yp = (len - xp) / tan_angle;
        int yp_new = yp;
        while (yp_new >= 0) {
            std::pair<double, double> coord = find_coord(QPoint(0, height), QPoint(len, 0), QPoint(xp, yp_new));
            QRgb value = img.pixel(QPoint(ceil(coord.first), ceil(coord.second)));
            img.setPixel(xp, yp_new, value);
            --yp_new;
        }
    }
}

QImage& Rotate45::blur_right_upper_angle(QImage& img,
                              int len, int height) {
    int xp, yp;
    double tan_angle = static_cast<double>(len)/height;
    for (xp = img.width() - len; xp < img.width(); xp++) {
        yp = (xp - img.width() + len) / tan_angle;
        int yp_new = yp;
        while (yp_new >= 0) {
            std::pair<double, double> coord = find_coord(QPoint(img.width(), height), QPoint(img.width() - len, 0), QPoint(xp, yp_new));
            QRgb value = img.pixel(QPoint(floor(coord.first), ceil(coord.second)));
            img.setPixel(xp, yp_new, value);
            --yp_new;
        }
    }
    return img;
}

QImage& Rotate45::blur_left_bottom_angle(QImage& img,
                              int len, int height) {
    int xp, yp;
    double tan_angle = static_cast<double>(height)/len;
    for (xp = 0; xp < len; xp++) {
        yp = img.height() - (len - xp) * tan_angle;
        int yp_new = yp;
        while (yp_new < img.height()) {
            std::pair<double, double> coord = find_coord(QPoint(0, img.height() - height), QPoint(len, img.height()), QPoint(xp, yp_new));
            QRgb value = img.pixel(QPoint(ceil(coord.first), floor(coord.second)));
            img.setPixel(xp, yp_new, value);
            ++yp_new;
        }
    }
    return img;
}

QImage& Rotate45::blur_right_bottom_angle(QImage& img,
                              int len, int height) {
    int xp, yp;
    double tan_angle = static_cast<double>(height)/len;
    for (xp = img.width() - len; xp < img.width(); xp++) {
        yp = img.height() - (xp - img.width() + len) * tan_angle;
        int yp_new = yp;
        while (yp_new < img.height()) {
            std::pair<double, double> coord = find_coord(QPoint(img.width() - len, img.height()), QPoint(img.width(), img.height() - height), QPoint(xp, yp_new));
            QRgb value = img.pixel(QPoint(floor(coord.first), floor(coord.second)));
            img.setPixel(xp, yp_new, value);
            ++yp_new;
        }
    }
    return img;
}

QImage& Rotate45::blur(QImage& img,
                       QPoint LeftUpperAngle,
                       QPoint RightUpperAngle,
                       QPoint RightBottomAngle,
                       QPoint LeftBottomAngle) {
    const int Inaccuracy = 5;
    blur_left_upper_angle(img,
                          LeftUpperAngle.x() - LeftBottomAngle.x() + Inaccuracy,
                          LeftBottomAngle.y() - LeftUpperAngle.y() + Inaccuracy);
    blur_right_upper_angle(img,
                           RightUpperAngle.x() - LeftUpperAngle.x() + Inaccuracy,
                           RightUpperAngle.y() - LeftUpperAngle.y() + Inaccuracy);
    blur_left_bottom_angle(img,
                           RightBottomAngle.x() - LeftBottomAngle.x() + Inaccuracy,
                           RightBottomAngle.y() - LeftBottomAngle.y() + Inaccuracy);
    blur_right_bottom_angle(img,
                            RightUpperAngle.x() - RightBottomAngle.x() + Inaccuracy,
                            RightBottomAngle.y() - RightUpperAngle.y() + Inaccuracy);
    return img;
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
