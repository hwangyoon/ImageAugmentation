
#ifndef MAIN_MATRIXCONVOLUTION_HPP
#define MAIN_MATRIXCONVOLUTION_HPP

#include "algo.h"
#include <QVariant>
#include <exception>

enum ConvolutionMode {
    blur_, negative_, sharpen_, embross_, light_blur_, light_sharpen_, light_embross_, gauss_blur_
};

class MatrixConvolution : public Algorithm {
public:
  friend class MatrixConvolutionBuilder;
  QImage processImage(const QImage* workingModel) override;
private:
  std::vector<std::vector<double>> matrix_;
  int offset_ = 0;
  int degree_;
  MatrixConvolution() = default;
};

class MatrixConvolutionBuilder {
private:
    ConvolutionMode mode_ = ConvolutionMode::gauss_blur_;
    int offset_ = 0;
    int32_t degree_ = 5;
    std::vector<std::vector<double>> getMatrix();
public:
  MatrixConvolutionBuilder() = default;
  MatrixConvolutionBuilder setWorkingMode(ConvolutionMode mode);
  MatrixConvolutionBuilder setWorkingDegree(int degree);
  MatrixConvolution build();
};

#endif  // MAIN_MATRIXCONVOLUTION_HPP
