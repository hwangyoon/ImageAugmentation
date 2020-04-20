#include "../include/manager.h"
#include <memory>
void AlgorithmManager::process_requests(GlobalRequest r) {
    std::vector<std::pair<std::shared_ptr<QImage>, int>> images;
    for (auto i : r.get_requests()) {
        QImage img(r.get_load_directory().absolutePath());
        std::shared_ptr<Algorithm> ptr = f.get_algo(i);
        std::shared_ptr<QImage> picture = std::make_shared<QImage>(ptr->processImage(&img));
        images.push_back(std::make_pair(picture, i->type));
    }
    imgwriter.save_to_directory(r.get_save_directory(), images, r.getFileFormat());
}

QImage AlgorithmManager::preview(GlobalRequest r) {
    QImage q(r.get_load_directory().absolutePath());
    for (auto i : r.get_requests()) {
        std::unique_ptr<Algorithm> ptr = f.get_algo(i);
        q = ptr->processImage(&q);
    }
    return q;
}
