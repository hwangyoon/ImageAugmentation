#ifndef FABRIC_H
#define FABRIC_H

#include <memory>
#include "request.h"
#include "algo.h"
#include "../include/verticalflip.h"
#include "../include/horizontalflip.h"
#include "../include/cropfrommiddle.h"
#include "../include/rotate90.h"
#include "../include/rotate45.h"

class Factory {
public:
    Factory() {}
    // returns pointer to the algorithm which should be used according to the request
    std::unique_ptr<Algorithm> getAlgo(std::shared_ptr<Request> r);
};

#endif // FABRIC_H
