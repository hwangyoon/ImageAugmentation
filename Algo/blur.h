#ifndef ALGO_H
#define ALGO_H
#include <QImage>
#include <cmath>

void blur_left_upper_angle(QImage& img,
                              int len, int height);
void blur_right_upper_angle(QImage& img,
                              int len, int height);
void blur_left_bottom_angle(QImage& img,
                              int len, int height);
void blur_right_bottom_angle(QImage& img,
                              int len, int height);
void blur(QImage& img, int len, int height);
#endif // ALGO_H
