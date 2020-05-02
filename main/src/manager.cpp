#include "../include/manager.h"
#include <memory>
void AlgorithmManager::process_requests(GlobalRequest r) {
    std::vector<std::pair<std::shared_ptr<QImage>, int>> images;
    for (auto i : r.getRequests()) {
        QImage img(r.getLoadDirectoryOrFile().absoluteFilePath());
        std::shared_ptr<Algorithm> ptr = f.getAlgo(i);
        std::shared_ptr<QImage> picture = std::make_shared<QImage>(ptr->processImage(&img));
        images.push_back(std::make_pair(picture, i->type));
    }
    imgwriter.saveToDirectory(r.getSaveDirectory().absoluteFilePath(), images, r.getFileFormat());
}

QImage AlgorithmManager::preview(GlobalRequest r) {
    QImage q(r.getLoadDirectoryOrFile().absoluteFilePath());
    for (auto i : r.getRequests()) {
        std::unique_ptr<Algorithm> ptr = f.getAlgo(i);
        q = ptr->processImage(&q);
    }
    return q;
}
