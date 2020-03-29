#include "../include/imagewriter.h"
#include <cstdlib>
#include <ctime>
#include <memory>
#include <cassert>

QString ImageWriter::generate_string(std::size_t n) {
    QString str = "/";
    for (std::size_t i = 0; i < n; i++) {
        str += (rand()%('z' - 'a' + 1) + 'a');
    }
    return str;
}

void ImageWriter::save_to_directory(QDir path_to_, std::vector<std::shared_ptr<QImage>> images, QString format) {
    for (auto i : images) {
        i->save(path_to_.absolutePath() + generate_string(10) + format);
    }
}

void save_to_file(QDir path_to_, QImage& img) {
    img.save(path_to_.absolutePath());
}
