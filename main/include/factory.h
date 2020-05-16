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
#include "../include/dithering.h"
#include "../include/gaussiannoise.h"
#include "../include/kuwahara.h"
#include "../include/lightening.h"
#include "../include/whiteblack.h"
#include "../include/randomcrop.h"

/* A class that returns pointer to the algorithm that should be used according to the request */
class Factory {
public:
    Factory() {}
    /* Returns pointer to the algorithm with all arguments set
     * according to information in given Request object*/
    std::unique_ptr<Algorithm> getAlgo(std::shared_ptr<Request> r);
private:
    /* Set of methods that create and fill object of derived Algortihm class */
    std::unique_ptr<Algorithm> createCrop(std::shared_ptr<Request> request);
    std::unique_ptr<Algorithm> createGaussNoise(std::shared_ptr<Request> request);
    std::unique_ptr<Algorithm> createKuwahara(std::shared_ptr<Request> request);
    std::unique_ptr<Algorithm> createLight(std::shared_ptr<Request> request);
    std::unique_ptr<Algorithm> createRGB(std::shared_ptr<Request> request);
    std::unique_ptr<Algorithm> createRotate90(std::shared_ptr<Request> request);
    std::unique_ptr<Algorithm> createRotate45(std::shared_ptr<Request> request);
    std::unique_ptr<Algorithm> createBlur(std::shared_ptr<Request> request);
    std::unique_ptr<Algorithm> createNegative(std::shared_ptr<Request> request);
    std::unique_ptr<Algorithm> createSharpen(std::shared_ptr<Request> request);
    std::unique_ptr<Algorithm> createEmbross(std::shared_ptr<Request> request);
    std::unique_ptr<Algorithm> createLightBlur(std::shared_ptr<Request> request);
    std::unique_ptr<Algorithm> createLightSharpen(std::shared_ptr<Request> request);
    std::unique_ptr<Algorithm> createLightEmbross(std::shared_ptr<Request> request);
    std::unique_ptr<Algorithm> createGaussBlur(std::shared_ptr<Request> request);
    std::unique_ptr<Algorithm> createRandomCrop(std::shared_ptr<Request> request);
};

#endif // FABRIC_H
