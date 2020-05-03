#include "../include/manager.h"
#include <memory>
void AlgorithmManager::processRequests(GlobalRequest r) {
    if (r.getLoadDirectoryOrFile().isFile()) {
        processSingleImage(r);
    } else {
        processDirectory(r);
    }
}

void AlgorithmManager::processSingleImage(GlobalRequest r) {
    std::vector<std::pair<std::shared_ptr<QImage>, int>> images;
    QString fileName = r.getLoadDirectoryOrFile().absoluteFilePath();
    QImage image(fileName);
    if (image.isNull()) {
        fprintf(stderr, "%s\n", qPrintable("Error: unable to process " + fileName));
        return;
    }
    for (auto request : r.getRequests()) {
        QImage img(fileName);
        std::shared_ptr<Algorithm> ptr = f.getAlgo(request);
        std::shared_ptr<QImage> picture = std::make_shared<QImage>(ptr->processImage(&img));
        images.push_back(std::make_pair(picture, request->type));
    }
    imgwriter.saveToDirectory(r.getSaveDirectory().absoluteFilePath(), images, r.getFileFormat());
}

void AlgorithmManager::processDirectory(GlobalRequest r) {
    ImageLoader imgloader;
    QDir directory = r.getLoadDirectoryOrFile().absoluteFilePath();
    std::vector<QString> filePaths = imgloader.getAbsoluteFilePaths(directory);
    for (auto path : filePaths) {
        r.setLoadDirectoryOrFile(QFileInfo(path));
        processSingleImage(r);
    }
}

QImage AlgorithmManager::preview(GlobalRequest r) {
    QString fileName = r.getLoadDirectoryOrFile().absoluteFilePath();
    QImage q(fileName);
    if (q.isNull()) {
         throw std::invalid_argument("Error: unable to process image");
    }
    for (auto request : r.getRequests()) {
        std::unique_ptr<Algorithm> ptr = f.getAlgo(request);
        q = ptr->processImage(&q);
    }
    return q;
}
