#include "algo.h"


void rotate(Image *my_image) {

    int32_t cols = my_image->get_cols();
    int32_t rows = my_image->get_rows();


    Image temp(cols, rows);

    for (int32_t i = 0; i < rows; i++)
        for (int32_t j = 0; j < cols; j++)
            temp.set(j, i, my_image->get(i, cols - j - 1));

    *my_image = temp;
}

void crop(Image *whole_image, Image *my_image,
          int32_t x, int32_t y, int32_t cols, int32_t rows) {

    for (int32_t i = 0; i < cols; i++)
        for (int32_t j = 0; j < rows; j++) {
            my_image->set(i, j, whole_image->get(i + x, j + y));
        }

    my_image->set_cols(cols);
    my_image->set_rows(rows);


}

void flip(Image *my_image) {
    int32_t cols = my_image->get_cols();
    int32_t rows = my_image->get_rows();
    for (int32_t i = 0; i < rows; i++)
        for (int32_t j = 0; j < cols / 2; j++) {
            Pixel temp = my_image->get(i, j);
            my_image->set(i, j, my_image->get(i, cols - 1 - j));
            my_image->set(i, cols - 1 - j, temp);
        }
}