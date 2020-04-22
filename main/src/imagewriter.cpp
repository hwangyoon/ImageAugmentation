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
    algoNames[rotate45] = "rotate45";
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

void ImageWriter::countFileNames(QDir directory,
                                 QMap<QString, int>& fileNameNumber) {
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
        QString fileName = imageInfo.completeBaseName();
        int index = fileName.indexOf(QChar('_'));
        // returns -1 if not found or file name starts with '_'
        if (index > 0) {
            QString algoName = fileName.mid(0, index);
            fileNameNumber[algoName] = fileNameNumber[algoName] + 1;
        }
    }
}

void ImageWriter::save_to_directory(QDir path_to_,
                                    std::vector<std::pair<std::shared_ptr<QImage>, int>> images,
                                    QString format) {
    QMap<QString, int> fileNameNumber;
    countFileNames(path_to_, fileNameNumber);
    for (auto i : images) {
        QString algoName = algoNames[i.second];
        if (fileNameNumber.find(algoName) != fileNameNumber.end()) {
            algoName += ("_" + QString::number(fileNameNumber[algoName] + 1) + ".");
        } else {
            algoName += ("_" + QString::number(1) + ".");
        }
        i.first->save(path_to_.absolutePath() + "/" + algoName + format);
    }
}

void save_to_file(QDir path_to_, QImage& img) {
    img.save(path_to_.absolutePath());
}
