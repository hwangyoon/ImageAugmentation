#ifndef FABRIC_H
#define FABRIC_H

#include <memory>
#include "request.h"
#include "algo.h"

<<<<<<< HEAD
class Factory {
public:
    Factory() {}
=======
class factory {
public:
    factory() {}
>>>>>>> b12925ec1e8740785930234c87e00b42fe562cbe
    // returns pointer to the algorithm which should be used according to the request
    std::unique_ptr<Algorithm> get_algo(Request* r);
};

#endif // FABRIC_H
