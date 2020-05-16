#ifndef ALGOTYPE_H
#define ALGOTYPE_H
#include <set>

/* Types of all algorithms
   more about each algorithm in README*/
enum AlgoType {
    crop, vflip, hflip, rotate90, rotate45, dithering, gaussiannoise, kuwahara, light, rgb, whiteblack,
    blurConvolution, negativeConvolution, sharpenConvolution, embrossConvolution, combined,
    lightBlurConvolution, lightSharpenConvolution, lightEmbrossConvolution,
    gaussBlurConvolution, randomcrop
};

#endif // ALGOTYPE_H
