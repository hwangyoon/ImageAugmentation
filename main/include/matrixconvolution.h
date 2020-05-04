#ifndef MAIN_MATRIXCONVOLUTION_HPP
#define MAIN_MATRIXCONVOLUTION_HPP

#include "algo.h"
#include "pixel.h"
#include <QVariant>
#include <exception>
#include "../include/enumconvolution.h"

class MatrixConvolution : public Algorithm {
public:
  friend class MatrixConvolutionBuilder;
  QImage processImage(const QImage* workingModel) override;
private:
  std::vector<std::vector<double>> matrix_;
  int offset_ = 0;
  int degree_;
  MatrixConvolution() = default;
  static Pixel countPixel(const QImage* workingModel, const std::vector<std::vector<double>>& matrix, int x, int y, int cols,
             int rows, int offset);
};

class MatrixConvolutionBuilder {
private:
    ConvolutionMode mode_ = ConvolutionMode::gaussBlur;
    int offset_ = 0;
    int32_t degree_ = 30;
    const int32_t maxDegree = 70;
    const double binom = 0.5;
    const int maxIter = 100000;
    std::vector<std::vector<double>> getMatrix();
public:
  MatrixConvolutionBuilder() = default;
  MatrixConvolutionBuilder setWorkingMode(ConvolutionMode mode);
  MatrixConvolutionBuilder setWorkingDegree(int degree);
  MatrixConvolution build();
};

#endif  // MAIN_MATRIXCONVOLUTION_HPP
