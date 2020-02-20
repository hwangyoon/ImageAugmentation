#include "algo.h"

struct Pixel **build(int32_t rows, int32_t cols) {
    auto **data_new = (struct Pixel **) malloc(rows * sizeof(struct Pixel *));
    data_new[0] = (struct Pixel *) malloc(rows * cols * sizeof(struct Pixel));
    for (int32_t i = 1; i < rows; i++) {
        data_new[i] = data_new[i - 1] + cols;
    }
    return data_new;
}


void freebuild(struct Pixel **data) {
    free(data[0]);
    free(data);
}

void rotate(Image *my_image) {
//    struct Pixel **data_new = build(my_image->get_cols(), my_image->get_rows());

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


//     my_image->height = h;
//     my_image->width = w;
//     my_image->data = build(h, w);
//
//    my_image->header = whole_image->header;
//
//    int8_t trx = w % 4;
//
//    my_image->header.size = size_of_pixel* h * (w + trx) + sizeof(BMPHeader);
//    my_image->header.width_px = w;
//    my_image->header.height_px= h;
//     my_image->header.image_size_bytes = size_of_pixel* h * (w + trx);
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