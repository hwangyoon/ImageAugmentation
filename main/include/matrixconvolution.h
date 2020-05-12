#ifndef MAIN_MATRIXCONVOLUTION_HPP
#define MAIN_MATRIXCONVOLUTION_HPP

#include "algo.h"
#include "pixel.h"
#include <QVariant>
#include <exception>
#include "../include/enumconvolution.h"

/*8 matrix convolution algorithm (user selects one of the modes)*/
class MatrixConvolution : public Algorithm {
public:
  friend class MatrixConvolutionBuilder;
  QImage processImage(const QImage* workingModel) override;
private:
  /*convolution matrix*/
  std::vector<std::vector<double>> matrix_;
  /*the degree of offset the picture*/
  int offset_ = 0;
  /*the degree of gaussBlur mode*/
  int degree_;
  MatrixConvolution() = default;
  static Pixel countPixel(const QImage* workingModel, const std::vector<std::vector<double>>& matrix, int x, int y, int cols,
             int rows, int offset);
};

/*A builder class that implements the phased construction of an algorithm object*/

class MatrixConvolutionBuilder {
private:
    ConvolutionMode mode_ = ConvolutionMode::blur;
    int offset_ = 0;
    /* the default degree of gaussBlur*/
    int32_t degree_ = 30;
    /*the ceil of degree in gaussBlur*/
    const int32_t maxDegree = 70;
    /*the coef of binom distribution*/
    const double binom = 0.5;
    /*the amount of steps while generating normal binomial discret distribution*/
    const int maxIter = 100000;
    std::vector<std::vector<double>> getMatrix();
public:
  MatrixConvolutionBuilder() = default;
  /*methods that set the fields of the class, for convenience,
   *  return an object of the class builder, there is no parameter check in them*/
  MatrixConvolutionBuilder setWorkingMode(ConvolutionMode mode);
  MatrixConvolutionBuilder setWorkingDegree(int degree);
  /*a method in which the entered values ​​are checked
   *  and exceptions are thrown in case of incorrect input,
   * the builder fields are set to the algorithm object and this object is returned*/
  MatrixConvolution build();
};

#endif  // MAIN_MATRIXCONVOLUTION_HPP
