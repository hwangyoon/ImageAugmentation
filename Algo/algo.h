//
// Created by lizazhemchuzhina on 20.02.2020.
//

#ifndef PROJECT_ALGO_H
#define PROJECT_ALGO_H

#include <cstdint>
#include <cstdlib>
#include "../ImageClass/Image.h"


struct Pixel **build(int32_t rows, int32_t cols);


void freebuild(struct Pixel **data);

void rotate(Image *my_image);

void crop(Image *whole_image, Image *my_image,
          int32_t x, int32_t y, int32_t cols, int32_t rows);

void flip(Image *my_image);

#endif //PROJECT_ALGO_H
