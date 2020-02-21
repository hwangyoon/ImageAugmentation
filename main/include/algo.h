//
// Created by lizazhemchuzhina on 20.02.2020.
//

#ifndef PROJECT_ALGO_H
#define PROJECT_ALGO_H

#include <cstdint>
#include <cstdlib>
#include "../ImageClass/Image.h"


void rotate(Image *my_image);//поворот на 90 градусов

void crop(Image *whole_image, Image *my_image,
          int32_t x, int32_t y, int32_t cols, int32_t rows);//вырезание куска из картинки

void flip(Image *my_image);//отражение относительно вертикали

#endif //PROJECT_ALGO_H
