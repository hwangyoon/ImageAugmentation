#include <random>
#include "../include/matrixconvolution.h"
#include "../include/gaussiannoise.h"
#include "../include/pixel.h"

/* Method of adding convolution matrix to a pixel */
Pixel MatrixConvolution::countPixel(const QImage* workingModel, const std::vector<std::vector<double>>& matrix,
                                    int x, int y, int cols, int rows, int offset) {
    Pixel result;
    /* Adding on each step */
    Pixel adding;
    /* Sum of the elems in matrix */
    double div = 0;
    /* Set the offset for result Pixel */
    if (offset) {
        result = Pixel(offset, offset, offset);
    }

    int size = matrix.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            /* Move half of the matrix */
            int i_tmp = x + i - size / 2, j_tmp = y + j - size / 2;

            i_tmp = std::min(std::max(0, i_tmp), cols - 1);
            j_tmp = std::min(std::max(0, j_tmp), rows - 1);

            adding = Pixel(workingModel->pixel(QPoint(i_tmp, j_tmp)));
            /* Changing the adding par of the pixel by convolution matrix */
            adding *= matrix[i][j];
            result += adding;
            div += matrix[i][j];
        }
    }
    /* In general, rounding down occurs:
     * avoid dividing by 0 in the case of a small amount of elements */
    if (div < 1) {
        div = 1;
    }
    /* Save the brightness */
    return result/div;
}

QImage MatrixConvolution::processImage(const QImage* workingModel) {
    int32_t cols = workingModel->width();
    int32_t rows = workingModel->height();
    QImage matrixPicture(cols, rows, workingModel->format());
    for (int32_t i = 0; i < cols; i++) {
        for (int32_t j = 0; j < rows; j++) {
            Pixel result = countPixel(workingModel, matrix_, i, j, cols, rows, offset_);
            matrixPicture.setPixelColor(QPoint(i, j), result.getRgb());
        }
    }
    return matrixPicture;
}

std::vector<std::vector<double>> MatrixConvolutionBuilder::getMatrix() {
    std::vector<std::vector<double>> matrix;
    /* Choose the constant matrix for convolution */
    switch (mode_) {
        case ConvolutionMode::blur:
            matrix = {{1, 1, 1},
                      {1, 1, 1},
                      {1, 1, 1}};
            break;
        case ConvolutionMode::sharpen:
            matrix = {{0,  -1, 0},
                      {-1, 5,  -1},
                      {0,  -1, 0}};
            break;
        case ConvolutionMode::embross:
            matrix = {{-2, -1, 0},
                      {-1, 1,  1},
                      {0,  1,  2}};
            break;
        case ConvolutionMode::negative:
            matrix = {{-1}};
            offset_ = 256;
            break;
        case ConvolutionMode::lightBlur:
            matrix = {{1, 1, 0},
                      {1, 1, 0},
                      {0, 0, 0}};
            break;
        case ConvolutionMode::lightSharpen:
            matrix = {{-1, 0, 0},
                      {0,  2, 0},
                      {0,  0, 0}};
            break;
        case ConvolutionMode::lightEmbross:
            matrix = {{1, 0, 0},
                      {0, 1, 0},
                      {0, 0, -1}};
            break;
        case ConvolutionMode::gaussBlur:
            std::random_device rd;
            std::mt19937 gen(rd());
            std::binomial_distribution<> d(degree_-1, binom);
            /* Compiling a table of normal discrete binomial distributions */
            matrix.assign(degree_, std::vector<double>(degree_, 0));
            for (int i = 0; i < maxIter; i++) {
                int x = d(gen);
                int y = d(gen);
                matrix[x][y]++;
            }
            for (auto& rows : matrix) {
                for (auto& value : rows) {
                    value /= maxIter;
                }
            }
    }
    return matrix;
}

MatrixConvolutionBuilder MatrixConvolutionBuilder::setWorkingMode(ConvolutionMode mode) {
    mode_ = mode;
    return *this;
}

MatrixConvolutionBuilder MatrixConvolutionBuilder::setWorkingDegree(int degree) {
    degree_ = degree;
    return *this;
}

MatrixConvolution MatrixConvolutionBuilder::build() {
    if(this->degree_ < 0 || this->degree_ > this->maxDegree) {
        throw std::invalid_argument("Invalid input: please set field in 0...70");
    }

    auto* algo = new MatrixConvolution();
    algo->matrix_ = getMatrix();
    algo->offset_ = this->offset_;
    algo->degree_ = this->degree_;
    return *algo;
}
