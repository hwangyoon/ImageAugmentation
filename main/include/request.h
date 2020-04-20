#ifndef REQUEST_H
#define REQUEST_H
#include <QDir>
#include <memory>
#include "rotate90.h"
#include "rotate45.h"
#include "rgbtone.h"
#include "matrixconvolution.h"
#include "algotype.h"

class Request {
public:
    Request(int type_) : type(type_) {}
    int type = -1;
};

class CropRequest : public Request {
public:
    CropRequest(int32_t upperLeftXInPercent_, int32_t upperLeftYInPercent_,
                int32_t downRightXInPercent_, int32_t downRightYInPercent_) :
                Request(crop),
                upperLeftXInPercent(upperLeftXInPercent_),
                upperLeftYInPercent(upperLeftYInPercent_),
                downRightXInPercent(downRightXInPercent_),
                downRightYInPercent(downRightYInPercent_) {
        isSetUpperLeftXInPercent = true;
        isSetUpperLeftYInPercent = true;
        isSetDownRightXInPercent = true;
        isSetDownRightYInPercent = true;

    }
    CropRequest() : Request(crop) {}
    bool isSetUpperLeftXInPercent = false;
    bool isSetUpperLeftYInPercent = false;
    bool isSetDownRightXInPercent = false;
    bool isSetDownRightYInPercent = false;
    int32_t upperLeftXInPercent, upperLeftYInPercent;
    int32_t downRightXInPercent, downRightYInPercent;
};

class FlipVRequest : public Request {
public:
    FlipVRequest() : Request(vflip) {}
};

class FlipHRequest : public Request {
public:
    FlipHRequest() : Request(hflip) {}
};

class Rotate90Request : public Request {
public:
    Rotate90Request(Direction90 d_) : Request(rotate90), d(d_) {
        isSetDirection = true;
    }
    Rotate90Request() : Request(rotate90) {}
    bool isSetDirection = false;
    Direction90 d;
};

class KuwaharaRequest : public Request {
public:
    KuwaharaRequest(int32_t degreeOfBlur_) : Request(kuwahara), degreeOfBlur(degreeOfBlur_) {
        isSetDegreeOfBlur = true;
    }
    KuwaharaRequest() : Request(kuwahara) {}
    bool isSetDegreeOfBlur = false;
    int32_t degreeOfBlur;
};

class RGBToneRequest : public Request {
public:
    RGBToneRequest(int32_t degreeOfTone_, Color color_) : Request(rgb),
                                                          degreeOfTone(degreeOfTone_),
                                                          color(color_) {
        isSetColor = true;
        isSetDegreeOfTone = true;
    }
    void setColor(Color color_) {
        color = color_;
        isSetColor = true;
    }
    void setDegreeOfTone(int32_t degree) {
        degreeOfTone = degree;
        isSetDegreeOfTone = true;
    }
    RGBToneRequest() : Request(rgb) {}
    bool isSetDegreeOfTone = false;
    bool isSetColor = false;
    int32_t degreeOfTone;
    Color color;
};

class LighteningRequest : public Request {
public:
    LighteningRequest(int32_t degreeOfLightening_) : Request(light),
                                                    degreeOfLightening(degreeOfLightening_) {
        isSetDegreeOfLightening = true;
    }
    LighteningRequest() : Request(light) {}
    bool isSetDegreeOfLightening = false;
    int32_t degreeOfLightening;
};

class Rotate45Request : public Request {
public:
    Rotate45Request(Direction45 d_) : Request(rotate45), d(d_) {
        isSetdirection45 = true;
    }
    Rotate45Request() : Request(rotate45) {}
    bool isSetdirection45 = false;
    Direction45 d;
};

class DitheringRequest : public Request {
public:
    DitheringRequest() : Request(dithering) {}
};

class WhiteBlackRequest : public Request {
public:
    WhiteBlackRequest() : Request(whiteblack) {}
};

class BlurConvolutionRequest : public Request {
public:
    BlurConvolutionRequest() : Request(blurConvolution) {
        isSetWorkingMode = true;
    }
    BlurConvolutionRequest(int32_t degree_) : Request(blurConvolution), degree(degree_) {
        isSetWorkingDegree = true;
        isSetWorkingMode = true;
    }
    void setWorkingDegree(int32_t degree_) {
        degree = degree_;
        isSetWorkingDegree = true;
    }
    int32_t degree;
    bool isSetWorkingMode = false;
    bool isSetWorkingDegree = false;
};

class NegativeConvolutionRequest : public Request {
public:
    NegativeConvolutionRequest() : Request(negativeConvolution) {
        isSetWorkingMode = true;
    }
    NegativeConvolutionRequest(int32_t degree_) : Request(negativeConvolution), degree(degree_) {
         isSetWorkingDegree = true;
         isSetWorkingMode = true;
    }
    void setWorkingDegree(int32_t degree_) {
        degree = degree_;
        isSetWorkingDegree = true;
    }
    int32_t degree;
    bool isSetWorkingMode = false;
    bool isSetWorkingDegree = false;
};

class SharpenConvolutionRequest : public Request {
public:
    SharpenConvolutionRequest() : Request(sharpenConvolution) {
        isSetWorkingMode = true;
    }
    SharpenConvolutionRequest(int32_t degree_) : Request(sharpenConvolution), degree(degree_) {
         isSetWorkingDegree = true;
         isSetWorkingMode = true;
    }
    void setWorkingDegree(int32_t degree_) {
        degree = degree_;
        isSetWorkingDegree = true;
    }
    int32_t degree;
    bool isSetWorkingMode = false;
    bool isSetWorkingDegree = false;
};

class EmbrossConvolutionRequest : public Request {
public:
    EmbrossConvolutionRequest() : Request(embrossConvolution) {
        isSetWorkingMode = true;
    }
    EmbrossConvolutionRequest(int32_t degree_) : Request(embrossConvolution), degree(degree_) {
         isSetWorkingDegree = true;
         isSetWorkingMode = true;
    }
    void setWorkingDegree(int32_t degree_) {
        degree = degree_;
        isSetWorkingDegree = true;
    }
    int32_t degree;
    bool isSetWorkingMode = false;
    bool isSetWorkingDegree = false;
};

class LightBlurConvolutionRequest : public Request {
public:
    LightBlurConvolutionRequest() : Request(lightBlurConvolution) {
        isSetWorkingMode = true;
    }
    LightBlurConvolutionRequest(int32_t degree_) : Request(lightBlurConvolution), degree(degree_) {
         isSetWorkingDegree = true;
         isSetWorkingMode = true;
    }
    void setWorkingDegree(int32_t degree_) {
        degree = degree_;
        isSetWorkingDegree = true;
    }
    int32_t degree;
    bool isSetWorkingMode = false;
    bool isSetWorkingDegree = false;
};

class LightSharpenConvolutionRequest : public Request {
public:
    LightSharpenConvolutionRequest() : Request(lightSharpenConvolution) {
        isSetWorkingMode = true;
    }
    LightSharpenConvolutionRequest(int32_t degree_) : Request(lightSharpenConvolution), degree(degree_) {
         isSetWorkingDegree = true;
         isSetWorkingMode = true;
    }
    void setWorkingDegree(int32_t degree_) {
        degree = degree_;
        isSetWorkingDegree = true;
    }
    int32_t degree;
    bool isSetWorkingMode = false;
    bool isSetWorkingDegree = false;
};


class LightEmbrossConvolutionRequest : public Request {
public:
    LightEmbrossConvolutionRequest() : Request(lightEmbrossConvolution) {
        isSetWorkingMode = true;
    }
    LightEmbrossConvolutionRequest(int32_t degree_) : Request(lightEmbrossConvolution), degree(degree_) {
         isSetWorkingDegree = true;
         isSetWorkingMode = true;
    }
    void setWorkingDegree(int32_t degree_) {
        degree = degree_;
        isSetWorkingDegree = true;
    }
    int32_t degree;
    bool isSetWorkingMode = false;
    bool isSetWorkingDegree = false;
};

class GaussBlurConvolutionRequest : public Request {
public:
    GaussBlurConvolutionRequest() : Request(gaussBlurConvolution) {
        isSetWorkingMode = true;
    }
    GaussBlurConvolutionRequest(int32_t degree_) : Request(gaussBlurConvolution), degree(degree_) {
         isSetWorkingDegree = true;
         isSetWorkingMode = true;
    }
    void setWorkingDegree(int32_t degree_) {
        degree = degree_;
        isSetWorkingDegree = true;
    }
    int32_t degree;
    bool isSetWorkingMode = false;
    bool isSetWorkingDegree = false;
};


class GaussianNoiseRequest : public Request {
public:
    GaussianNoiseRequest(int32_t degreeOfNoise_, bool mono_) : Request(gaussiannoise),
                                                               degreeOfNoise(degreeOfNoise_),
                                                               mono(mono_) {
        isSetDegreeOfNoise = true;
        isSetMono = true;
    }
    GaussianNoiseRequest(int32_t degreeOfNoise_) : Request(gaussiannoise),
                                                   degreeOfNoise(degreeOfNoise_) {
        isSetDegreeOfNoise = true;
    }
    GaussianNoiseRequest(bool mono_) : Request(gaussiannoise), mono(mono_) {
        isSetMono = true;
    }
    GaussianNoiseRequest() : Request(gaussiannoise) {}
    bool isSetDegreeOfNoise = false;
    bool isSetMono = false;
    int32_t degreeOfNoise;
    bool mono;
};

class RandomCropRequest : public Request {
public:
    RandomCropRequest() : Request(randomcrop) {}
    RandomCropRequest(int32_t width, int32_t height) : Request(randomcrop),
                                                       widthInPercent(width),
                                                       heightInPercent(height) {
        isSetHeight = true;
        isSetWidth = true;
    }
    int32_t widthInPercent;
    int32_t heightInPercent;
    bool isSetHeight = false;
    bool isSetWidth = false;
};

class GlobalRequest {
public:
    GlobalRequest(QFileInfo pathFrom_, QFileInfo pathTo_) : pathFrom(pathFrom_), pathTo(pathTo_) {}
    GlobalRequest(QDir path_from_, QDir path_to_) : path_from(path_from_), path_to(path_to_) {}
    GlobalRequest() = default;
    ~GlobalRequest() = default;
    void setLimitOfPictures(int32_t limit_) {
        limitOfPictures = limit_;
    }
    void setDepthOfOverlay(std::vector<int32_t> depth) {
        depthOfOverlay = depth;
    }
    std::vector<int32_t> getDepthsOfOverlay() {
        return depthOfOverlay;
    }
    int32_t getLimitOfPictures() {
        return limitOfPictures;
    }
    void setLoadDirectoryOrFile(QFileInfo pathFrom_) {
        pathFrom = pathFrom_;
    }
    void setSaveDirectory(QFileInfo pathTo_) {
        pathTo = pathTo_;
    }

    QFileInfo getLoadDirectoryOrFile() {
        return pathFrom;
    }
    QFileInfo getSaveDirectory() {
        return pathTo;
    }
    void setFileFormat(const QString format) {
        fileFormat = format;
    }
    QString getFileFormat() {
        return fileFormat;
    }

    void addRequest(std::shared_ptr<Request> r) {
        requests.push_back(r);
    }

    std::vector<std::shared_ptr<Request>> getRequests() {
        return requests;
    }

private:
    std::vector<int32_t> depthOfOverlay = {1};
    int32_t limitOfPictures = 25;
    QFileInfo pathFrom;
    QFileInfo pathTo;
    QString fileFormat = "jpg";
    std::vector<std::shared_ptr<Request>> requests;
};

#endif // REQUEST_H
