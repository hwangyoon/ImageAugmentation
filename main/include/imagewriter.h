#ifndef IMAGEWRITER_H
#define IMAGEWRITER_H
#include <QDir>
#include <memory>
#include <QImage>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include "request.h"

/* A class that handles images saving */
class ImageWriter {
public:
    ImageWriter();
    /* The method saves all provided images to the given directory/file with the given format
     * It automatically generates names for each image
     * Each image name either contains name of algorithm that was used or 'combined'
     * if more than one algorithm was used */
    void saveToDirectory(QDir path_to_,
                         std::vector<std::pair<std::shared_ptr<QImage>, int>>,
                         QString format);
    /* The method count number of images that match each image name template */
    void countFileNames(QDir directory,
                        QMap<QString, int>& fileNameNumber);
private:
    /* Unordered_map of image names templates */
    std::unordered_map<int, QString> algoNames;
};

#endif // IMAGEWRITER_H
