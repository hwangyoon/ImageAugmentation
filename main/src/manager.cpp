#include "../include/manager.h"
<<<<<<< HEAD

void AlgorithmManager::process_requests(std::vector<Request*>& r, QString path_from, QString path_to) {
=======
#include <cassert>

void manager::process_requests(std::vector<Request*>& r, QString path_from, QString path_to) {
>>>>>>> b12925ec1e8740785930234c87e00b42fe562cbe
    QImage q(path_from);
    for (auto i : r) {
        std::unique_ptr<Algorithm> ptr = f.get_algo(i);
        q = ptr->processImage(&q);
    }
<<<<<<< HEAD
    q.save(path_to);
=======
    q.save(path_to, 0, -1);
>>>>>>> b12925ec1e8740785930234c87e00b42fe562cbe
}
