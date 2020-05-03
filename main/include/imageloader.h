#ifndef IMAGELOADER_H
#define IMAGELOADER_H
#include <vector>
#include <QString>
#include <QDir>

class ImageLoader {
public:
    std::vector<QString> getAbsoluteFilePaths(QDir directory);
};

#endif // IMAGELOADER_H
