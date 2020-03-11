#ifndef FABRIC_H
#define FABRIC_H

#include <memory>
#include "request.h"
#include "algo.h"

class Factory {
public:
    Factory() {}
    // returns pointer to the algorithm which should be used according to the request
    std::unique_ptr<Algorithm> get_algo(Request* r);
};

#endif // FABRIC_H
