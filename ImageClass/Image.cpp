#include "Image.h"

#include <cassert>

Image::Image(std::size_t row, std::size_t col) : row_(row), col_(col), image_data_(new Pixel*[row_]()) {
    for (std::size_t row_i = 0; row_i != row_; ++row_i) {
        image_data_[row_i] = new Pixel[col_];
    }
}

Image::~Image() {
    for (std::size_t row_i = 0; row_i != row_; ++row_i) {
        delete[] image_data_[row_i];
    }
    delete[] image_data_;
}

std::size_t Image::get_rows() const { return row_; }
std::size_t Image::get_cols() const { return col_; }

void Image::set(std::size_t row, std::size_t col, Pixel p) {
    assert(row < row_ && col < col_);
    image_data_[row][col] = p;
}

Pixel Image::get(std::size_t row, std::size_t col) const {
    assert(row < row_ && col < col_);
    return image_data_[row][col];
}
