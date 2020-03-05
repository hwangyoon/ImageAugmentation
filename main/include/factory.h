#ifndef FABRIC_H
#define FABRIC_H

#include <memory>
#include "request.h"
#include "algo.h"

class factory {
public:
    factory() {}
    std::unique_ptr<Algorithm> get_algo(Request* r);
};

#endif // FABRIC_H
