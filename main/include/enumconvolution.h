#ifndef ENUMCONVOLUTION_H
#define ENUMCONVOLUTION_H
/*transformation types for matrix convolution algorithm,
 *  more on the link http://wb0.ru/articles/120.htm*/
enum ConvolutionMode {
    blur, negative, sharpen, embross, lightBlur, lightSharpen, lightEmbross, gaussBlur
};
#endif // ENUMCONVOLUTION_H
