#ifndef IMAGEWRITER_H
#define IMAGEWRITER_H
#include <QDir>
#include <memory>
#include <QImage>
#include <unordered_map>
#include "request.h"

class ImageWriter {
public:
    ImageWriter();
    void save_to_directory(QDir path_to_,
                           std::vector<std::pair<std::shared_ptr<QImage>, int>>,
                           QString format);
    void countFileNames(QDir directory,
                        QMap<QString, int>& fileNameNumber);
    void save_to_file(QDir path_to, QImage& img);
private:
    QString generate_string(std::size_t n);
    std::unordered_map<int, QString> algoNames;
};

#endif // IMAGEWRITER_H
