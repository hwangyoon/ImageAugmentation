#ifndef IMAGE_IMAGE_H
#define IMAGE_IMAGE_H
#include <cstdio>
struct Pixel {
    char first_byte, second_byte, third_byte;
};

class Image {
private:
    size_t row_, col_;
    Pixel** image_data_ ;
public:
    Image(std::size_t row, size_t col);
    ~Image();

    std::size_t get_rows() const;
    std::size_t get_cols() const;
    void set(std::size_t row, std::size_t col, Pixel p);
    Pixel get(std::size_t row, std::size_t col) const;
};
#endif //IMAGE_IMAGE_H
