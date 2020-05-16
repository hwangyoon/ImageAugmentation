#ifndef IMAGELOADER_H
#define IMAGELOADER_H
#include <vector>
#include <QString>
#include <QDir>

/* A class that returns vector of all images paths in the given directory */
class ImageLoader {
public:
    std::vector<QString> getAbsoluteFilePaths(QDir directory);
};

#endif // IMAGELOADER_H
