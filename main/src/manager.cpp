#include "../include/manager.h"
#include <cassert>

void manager::process_requests(std::vector<Request*>& r, QString path_from, QString path_to) {
    assert(path_from == "/home/mario/Pictures/mickey.jpg");
    QImage q(path_from);
    assert(!q.isNull());
    //assert(q == "home/mario/Pictures/mickey.jpg");
    for (auto i : r) {
        assert(i != nullptr);
        std::unique_ptr<Algorithm> ptr = f.get_algo(i);
        assert(ptr != nullptr);
        q = ptr->processImage(&q);
    }
    assert(!q.isNull());
    q.save(path_to, 0, -1);
}
