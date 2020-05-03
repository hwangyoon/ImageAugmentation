#include "../include/imageloader.h"

std::vector<QString> ImageLoader::getAbsoluteFilePaths(QDir directory) {
    std::vector<QString> imagePaths;
    QStringList filter;
    //QLatin1String is a very thin wrapper around a const char*
    filter << QLatin1String("*.png");
    filter << QLatin1String("*.jpeg");
    filter << QLatin1String("*.jpg");
    filter << QLatin1String("*.JPG");
    filter << QLatin1String("*.JPEG");
    filter << QLatin1String("*.gif");
    filter << QLatin1String("*.bmp");
    filter << QLatin1String("*.dib");
    QFileInfoList files = directory.entryInfoList(filter, QDir::Files);
    for (auto imageInfo : files) {
        QString fileName = imageInfo.absoluteFilePath();
        imagePaths.push_back(fileName);
    }
    return imagePaths;
}
