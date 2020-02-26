#include "blur.h"

static std::pair<double, double> find_coord(QPoint A, QPoint B, QPoint S) {
    double a = (A.y() - B.y());
    double b = (B.x() - A.x());
    double c = (A.x()*B.y() - B.x()*A.y());
    double c1 = a*S.y() - b*S.x();
    return std::make_pair((-a*c - b*c1)/(a*a + b*b),
                          (a*c1 - b*c)/(a*a + b*b));
}

void blur_left_upper_angle(QImage& img,
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

void blur_right_upper_angle(QImage& img,
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
}

void blur_left_bottom_angle(QImage& img,
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
}

void blur_right_bottom_angle(QImage& img,
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
}

void blur(QImage& img, int len, int height) {
    len += 5;
    height += 5;
    blur_left_upper_angle(img, len, height);
    blur_right_upper_angle(img, len, height);
    blur_left_bottom_angle(img, len, height);
    blur_right_bottom_angle(img, len, height);
}
