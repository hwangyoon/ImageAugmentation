#ifndef ALGOTYPE_H
#define ALGOTYPE_H
#include <set>

enum AlgoType {
    crop, vflip, hflip, rotate90, rotate45, dithering, gaussiannoise, kuwahara, light, rgb, whiteblack,
    blurConvolution, negativeConvolution, sharpenConvolution, embrossConvolution, combined,
    lightBlurConvolution, lightSharpenConvolution, lightEmbrossConvolution,
    gaussBlurConvolution, randomcrop
};

#endif // ALGOTYPE_H
