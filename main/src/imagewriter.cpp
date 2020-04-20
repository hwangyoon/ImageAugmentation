#include "../include/imagewriter.h"
#include <cstdlib>
#include <ctime>
#include <memory>
#include <cassert>

ImageWriter::ImageWriter() {
    srand(time(NULL));
    algoNames[crop] = "crop";
    algoNames[dithering] = "dithering";
    algoNames[kuwahara] = "kuwahara";
    algoNames[gaussiannoise] = "gaussiannoise";
    algoNames[hflip] = "hflip";
    algoNames[vflip] = "vflip";
    algoNames[whiteblack] = "whiteblack";
    algoNames[rotate90] = "rotate90";
    algoNames[light] = "lightening";
    algoNames[rgb] = "rgb";
}

QString ImageWriter::generate_string(std::size_t n) {
    QString str = "/";
    for (std::size_t i = 0; i < n; i++) {
        str += (rand()%('z' - 'a' + 1) + 'a');
    }
    return str;
}

void ImageWriter::save_to_directory(QDir path_to_,
                                    std::vector<std::pair<std::shared_ptr<QImage>, int>> images,
                                    QString format) {
    for (auto i : images) {
        QString algoName = algoNames[i.second];
        i.first->save(path_to_.absolutePath() + "/" + algoName + "." + format);
    }
}

void save_to_file(QDir path_to_, QImage& img) {
    img.save(path_to_.absolutePath());
}
