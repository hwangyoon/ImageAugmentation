#ifndef REQUEST_H
#define REQUEST_H
#include <QDir>
#include <memory>
#include "rotate90.h"
#include "rotate45.h"
#include "rgbtone.h"
#include "matrixconvolution.h"
#include "algotype.h"

/* A base abstract class, classes derived from Request contain necessary arguments for each algorithm */
class Request {
public:
    Request(int type_) : type(type_) {}
    int type = -1;
};

/* Request for algorithm that cuts out part of the image */
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
    /* Verify arguments were provided by user */
    bool isSetUpperLeftXInPercent = false;
    bool isSetUpperLeftYInPercent = false;
    bool isSetDownRightXInPercent = false;
    bool isSetDownRightYInPercent = false;
    /* Coordinates in percent of upper left corner */
    int32_t upperLeftXInPercent, upperLeftYInPercent;
    /* Width and height in percent of cropping piece */
    int32_t downRightXInPercent, downRightYInPercent;
};

/* Request for algorithm of vertical image mirroring */
class FlipVRequest : public Request {
public:
    FlipVRequest() : Request(vflip) {}
};

/* Request for algorithm of horizontal image mirroring */
class FlipHRequest : public Request {
public:
    FlipHRequest() : Request(hflip) {}
};

/* Request for algorithm that rotates the start picture on 90 degrees in choosen direction */
class Rotate90Request : public Request {
public:
    Rotate90Request(Direction90 d_) : Request(rotate90), d(d_) {
        isSetDirection = true;
    }
    Rotate90Request() : Request(rotate90) {}
    /* Verify direction was provided by user */
    bool isSetDirection = false;
    /* Rotation direction */
    Direction90 d;
};

/* Request for an algorithm that creates effect of a painted picture */
class KuwaharaRequest : public Request {
public:
    KuwaharaRequest(int32_t degreeOfBlur_) : Request(kuwahara), degreeOfBlur(degreeOfBlur_) {
        isSetDegreeOfBlur = true;
    }
    KuwaharaRequest() : Request(kuwahara) {}
    /* Verify degree of blur was provided by user */
    bool isSetDegreeOfBlur = false;
    int32_t degreeOfBlur;
};

/* Request for an algorithm that creates amplification
 * of one of the components of the RGB vector */
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
    /* Verify arguments were provided by user */
    bool isSetDegreeOfTone = false;
    bool isSetColor = false;
    int32_t degreeOfTone;
    /* RED, BLUE or GREEN */
    Color color;
};

/* Request for algorithm of lightening the tone of the picture */
class LighteningRequest : public Request {
public:
    LighteningRequest(int32_t degreeOfLightening_) : Request(light),
                                                    degreeOfLightening(degreeOfLightening_) {
        isSetDegreeOfLightening = true;
    }
    LighteningRequest() : Request(light) {}
    /* Verify argument was provided by user */
    bool isSetDegreeOfLightening = false;
    int32_t degreeOfLightening;
};

/* Request for algorithm that rotates the start picture on 45 degrees in choosen direction */
class Rotate45Request : public Request {
public:
    Rotate45Request(Direction45 d_) : Request(rotate45), d(d_) {
        isSetdirection45 = true;
    }
    Rotate45Request() : Request(rotate45) {}
    /* Verify direction was provided by user */
    bool isSetdirection45 = false;
    /* Rotation direction */
    Direction45 d;
};

/* Request for an algorithm expressing unused colors in a palette through existing ones */
class DitheringRequest : public Request {
public:
    DitheringRequest() : Request(dithering) {}
};

/* Request for an algorithm changing the color palette of an image to black and white */
class WhiteBlackRequest : public Request {
public:
    WhiteBlackRequest() : Request(whiteblack) {}
};

/* Request for matrix convolution algorithm (blur mode) */
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
    /* Verify arguments were provided by user */
    bool isSetWorkingMode = false;
    bool isSetWorkingDegree = false;
};

/* Request for matrix convolution algorithm (negative mode) */
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
    /* Verify arguments were provided by user */
    bool isSetWorkingMode = false;
    bool isSetWorkingDegree = false;
};

/* Request for matrix convolution algorithm (sharpen mode) */
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
    /* Verify arguments were provided by user */
    bool isSetWorkingMode = false;
    bool isSetWorkingDegree = false;
};

/* Request for matrix convolution algorithm (embross mode) */
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
    /* Verify arguments were provided by user */
    bool isSetWorkingMode = false;
    bool isSetWorkingDegree = false;
};

/* Request for matrix convolution algorithm (light blur mode) */
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
    /* Verify arguments were provided by user */
    bool isSetWorkingMode = false;
    bool isSetWorkingDegree = false;
};

/* Request for matrix convolution algorithm (light sharpen mode) */
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
    /* Verify arguments were provided by user */
    bool isSetWorkingMode = false;
    bool isSetWorkingDegree = false;
};

/* Request for matrix convolution algorithm (light embross mode) */
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
    /* Verify arguments were provided by user */
    bool isSetWorkingMode = false;
    bool isSetWorkingDegree = false;
};

/* Request for matrix convolution algorithm (gauss blur mode) */
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
    /* Verify arguments were provided by user */
    bool isSetWorkingMode = false;
    bool isSetWorkingDegree = false;
};

/* Request for algorithm of Gaussian normally distributed image */
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
    /* Verify arguments were provided by user */
    bool isSetDegreeOfNoise = false;
    bool isSetMono = false;
    int32_t degreeOfNoise;
    bool mono;
};

/* Request for algorithm randomly choosing the location of a black rectangle
 * of a given relative size */
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

/* A class containing all information needed to process user's request */
class GlobalRequest {
public:
    GlobalRequest(QFileInfo pathFrom_, QFileInfo pathTo_) : pathFrom(pathFrom_), pathTo(pathTo_) {}
    GlobalRequest() = default;
    ~GlobalRequest() = default;
    /* Sets maximum number of pictures generated */
    void setLimitOfPictures(int32_t limit_) {
        limitOfPictures = limit_;
    }
    /* Sets vector of possible numbers of overlay */
    void setDepthOfOverlay(std::vector<int32_t> depth) {
        depthOfOverlay = depth;
    }
    /* Returns vector of possible numbers of overlay */
    std::vector<int32_t> getDepthsOfOverlay() {
        return depthOfOverlay;
    }
    /* Returns maximum number of pictures generated */
    int32_t getLimitOfPictures() {
        return limitOfPictures;
    }
    /* Sets source file/directory */
    void setLoadDirectoryOrFile(QFileInfo pathFrom_) {
        pathFrom = pathFrom_;
    }
    /* Sets destination directory */
    void setSaveDirectory(QFileInfo pathTo_) {
        pathTo = pathTo_;
    }
    /* Returns source file/directory */
    QFileInfo getLoadDirectoryOrFile() {
        return pathFrom;
    }
    /* Returns destination directory */
    QFileInfo getSaveDirectory() {
        return pathTo;
    }
    /* Sets format of output file */
    void setFileFormat(const QString format) {
        fileFormat = format;
    }
    /* Returns format of output file */
    QString getFileFormat() {
        return fileFormat;
    }
    /* Add request for a particular algorithm to be used */
    void addRequest(std::shared_ptr<Request> r) {
        requests.push_back(r);
    }
    /* Return vector of all requests */
    std::vector<std::shared_ptr<Request>> getRequests() {
        return requests;
    }

private:
    /*  vector of possible numbers of overlay */
    std::vector<int32_t> depthOfOverlay = {1};
    /* maximum number of pictures generated */
    int32_t limitOfPictures = 25;
    /* source file/directory */
    QFileInfo pathFrom;
    /* destination directory */
    QFileInfo pathTo;
    /* format of output file */
    QString fileFormat = "jpg";
    /* vector of all requests  */
    std::vector<std::shared_ptr<Request>> requests;
};

#endif // REQUEST_H
