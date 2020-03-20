#include "../include/manager.h"
#include <memory>
void AlgorithmManager::process_requests(GlobalRequest r) {
    std::vector<std::shared_ptr<QImage>> images;
    for (auto i : r.get_requests()) {
        QImage img(r.get_load_directory().absolutePath());
        std::shared_ptr<Algorithm> ptr = f.get_algo(i);
        std::shared_ptr<QImage> picture(new QImage(ptr->processImage(&img)));
        images.push_back(picture);
    }
    imgwriter.save_to_directory(r.get_save_directory(), images);
}

QImage AlgorithmManager::preview(GlobalRequest r) {
    QImage q(r.get_load_directory().absolutePath());
    for (auto i : r.get_requests()) {
        std::unique_ptr<Algorithm> ptr = f.get_algo(i);
        q = ptr->processImage(&q);
    }
    return q;
}
