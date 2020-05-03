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
    void saveToDirectory(QDir path_to_,
                           std::vector<std::pair<std::shared_ptr<QImage>, int>>,
                           QString format);
    void countFileNames(QDir directory,
                        QMap<QString, int>& fileNameNumber);
    void saveToFile(QDir path_to, QImage& img);
private:
    std::unordered_map<int, QString> algoNames;
};

#endif // IMAGEWRITER_H
