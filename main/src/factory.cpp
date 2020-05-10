#include "../include/factory.h"

//to do: process wrong arguments
std::unique_ptr<Algorithm> Factory::createCrop(std::shared_ptr<Request> request) {
    CropGivenPieceBuilder builder;
    std::shared_ptr<CropRequest> ptr = std::static_pointer_cast<CropRequest> (request);
    if (ptr->isSetUpperLeftXInPercent) {
        builder.setUpperLeftXInPercent(ptr->upperLeftXInPercent);
    }
    if (ptr->isSetUpperLeftYInPercent) {
        builder.setUpperLeftYInPercent(ptr->upperLeftYInPercent);
    }
    if (ptr->isSetDownRightXInPercent) {
        builder.setDownRightXInPercent(ptr->downRightXInPercent);
    }
    if (ptr->isSetDownRightYInPercent) {
        builder.setDownRightYInPercent(ptr->downRightYInPercent);
    }
    return std::make_unique<CropGivenPiece>(builder.build());
}

std::unique_ptr<Algorithm> Factory::createGaussNoise(std::shared_ptr<Request> request) {
    GaussianNoiseBuilder builder;
    std::shared_ptr<GaussianNoiseRequest> ptr =
            std::static_pointer_cast<GaussianNoiseRequest> (request);
    if (ptr->isSetDegreeOfNoise) {
        builder.setDegreeOfNoise(ptr->degreeOfNoise);
    }
    if (ptr->isSetMono) {
        builder.setMono(ptr->mono);
    }
    return std::make_unique<GaussianNoise>(builder.build());
}

std::unique_ptr<Algorithm> Factory::createKuwahara(std::shared_ptr<Request> request) {
    KuwaharaBuilder builder;
    std::shared_ptr<KuwaharaRequest> ptr =
            std::static_pointer_cast<KuwaharaRequest>(request);
    if (ptr->isSetDegreeOfBlur) {
        builder.setDegreeOfBlur(ptr->degreeOfBlur);
    }
    return std::make_unique<Kuwahara>(builder.build());
}

std::unique_ptr<Algorithm> Factory::createLight(std::shared_ptr<Request> request) {
    LighteningBuilder builder;
    std::shared_ptr<LighteningRequest> ptr =
            std::static_pointer_cast<LighteningRequest>(request);
    if (ptr->isSetDegreeOfLightening) {
        builder.setdDegreeOfLightening(ptr->degreeOfLightening);
    }
    return std::make_unique<Lightening>(builder.build());
}

std::unique_ptr<Algorithm> Factory::createRotate90(std::shared_ptr<Request> request) {
    Rotate90Builder builder;
    std::shared_ptr<Rotate90Request> ptr =
            std::static_pointer_cast<Rotate90Request>(request);
    if (ptr->isSetDirection) {
        builder.setDirection(ptr->d);
    }
    return std::make_unique<Rotate90>(builder.build());
}

std::unique_ptr<Algorithm> Factory::createRotate45(std::shared_ptr<Request> request) {
    Rotate45Builder builder;
    std::shared_ptr<Rotate45Request> ptr =
            std::static_pointer_cast<Rotate45Request>(request);
    if (ptr->isSetdirection45) {
        builder.setDirection(ptr->d);
    }
    return std::make_unique<Rotate45>(builder.build());
}

std::unique_ptr<Algorithm> Factory::createRGB(std::shared_ptr<Request> request) {
    RGBToneBuilder builder;
    std::shared_ptr<RGBToneRequest> ptr =
            std::static_pointer_cast<RGBToneRequest>(request);
    if (ptr->isSetDegreeOfTone) {
        builder.setdDegreeOfTone(ptr->degreeOfTone);
    }
    if (ptr->isSetColor) {
        builder.setColor(ptr->color);
    }
    return std::make_unique<RGBTone>(builder.build());
}

std::unique_ptr<Algorithm> Factory::createBlur(std::shared_ptr<Request> request) {
    MatrixConvolutionBuilder builder;
    std::shared_ptr<BlurConvolutionRequest> ptr =
            std::static_pointer_cast<BlurConvolutionRequest>(request);
    if (ptr->isSetWorkingDegree) {
        builder.setWorkingDegree(ptr->degree);
    }
    builder.setWorkingMode(blur);
    return std::make_unique<MatrixConvolution>(builder.build());
}

std::unique_ptr<Algorithm> Factory::createNegative(std::shared_ptr<Request> request) {
    MatrixConvolutionBuilder builder;
    std::shared_ptr<NegativeConvolutionRequest> ptr =
            std::static_pointer_cast<NegativeConvolutionRequest>(request);
    if (ptr->isSetWorkingDegree) {
        builder.setWorkingDegree(ptr->degree);
    }
    builder.setWorkingMode(negative);
    return std::make_unique<MatrixConvolution>(builder.build());
}

std::unique_ptr<Algorithm> Factory::createRandomCrop(std::shared_ptr<Request> request) {
    RandomCropBuilder builder;
    std::shared_ptr<RandomCropRequest> ptr =
            std::static_pointer_cast<RandomCropRequest>(request);
    if (ptr->isSetWidth) {
        builder.setUpperLeftXInPercent(ptr->widthInPercent);
    }
    if (ptr->isSetHeight) {
        builder.setUpperLeftYInPercent(ptr->heightInPercent);
    }
    return std::make_unique<RandomCrop>(builder.build());
}

std::unique_ptr<Algorithm> Factory::createGaussBlur(std::shared_ptr<Request> request) {
    MatrixConvolutionBuilder builder;
    std::shared_ptr<GaussBlurConvolutionRequest> ptr =
            std::static_pointer_cast<GaussBlurConvolutionRequest>(request);
    if (ptr->isSetWorkingDegree) {
        builder.setWorkingDegree(ptr->degree);
    }
    builder.setWorkingMode(gaussBlur);
    return std::make_unique<MatrixConvolution>(builder.build());
}

std::unique_ptr<Algorithm> Factory::createLightEmbross(std::shared_ptr<Request> request) {
    MatrixConvolutionBuilder builder;
    std::shared_ptr<LightEmbrossConvolutionRequest> ptr =
            std::static_pointer_cast<LightEmbrossConvolutionRequest>(request);
    if (ptr->isSetWorkingDegree) {
        builder.setWorkingDegree(ptr->degree);
    }
    builder.setWorkingMode(lightEmbross);
    return std::make_unique<MatrixConvolution>(builder.build());
}

std::unique_ptr<Algorithm> Factory::createLightSharpen(std::shared_ptr<Request> request) {
    MatrixConvolutionBuilder builder;
    std::shared_ptr<LightSharpenConvolutionRequest> ptr =
            std::static_pointer_cast<LightSharpenConvolutionRequest>(request);
    if (ptr->isSetWorkingDegree) {
        builder.setWorkingDegree(ptr->degree);
    }
    builder.setWorkingMode(lightSharpen);
    return std::make_unique<MatrixConvolution>(builder.build());
}

std::unique_ptr<Algorithm> Factory::createLightBlur(std::shared_ptr<Request> request) {
    MatrixConvolutionBuilder builder;
    std::shared_ptr<LightBlurConvolutionRequest> ptr =
            std::static_pointer_cast<LightBlurConvolutionRequest>(request);
    if (ptr->isSetWorkingDegree) {
        builder.setWorkingDegree(ptr->degree);
    }
    builder.setWorkingMode(lightBlur);
    return std::make_unique<MatrixConvolution>(builder.build());
}

std::unique_ptr<Algorithm> Factory::createEmbross(std::shared_ptr<Request> request) {
    MatrixConvolutionBuilder builder;
    std::shared_ptr<EmbrossConvolutionRequest> ptr =
            std::static_pointer_cast<EmbrossConvolutionRequest>(request);
    if (ptr->isSetWorkingDegree) {
        builder.setWorkingDegree(ptr->degree);
    }
    builder.setWorkingMode(embross);
    return std::make_unique<MatrixConvolution>(builder.build());
}

std::unique_ptr<Algorithm> Factory::createSharpen(std::shared_ptr<Request> request) {
    MatrixConvolutionBuilder builder;
    std::shared_ptr<SharpenConvolutionRequest> ptr =
            std::static_pointer_cast<SharpenConvolutionRequest>(request);
    if (ptr->isSetWorkingDegree) {
        builder.setWorkingDegree(ptr->degree);
    }
    builder.setWorkingMode(sharpen);
    return std::make_unique<MatrixConvolution>(builder.build());
}

std::unique_ptr<Algorithm> Factory::getAlgo(std::shared_ptr<Request> request) {
    if (request->type == crop) {
        return createCrop(request);
    }
    if (request->type == gaussiannoise) {
        return createGaussNoise(request);
    }
    if (request->type == dithering) {
        DitheringBuilder builder;
        return std::make_unique<Dithering>(builder.build());
    }
    if (request->type == kuwahara) {
        return createKuwahara(request);
    }
    if (request->type == light) {
        return createLight(request);
    }
    if (request->type == rgb) {
        return createRGB(request);
    }
    if (request->type == hflip) {
        HorizontalFlipBuilder builder;
        return std::make_unique<HorizontalFlip>(builder.build());
    }
    if (request->type == whiteblack) {
        WhiteBlackBuilder builder;
        return std::make_unique<WhiteBlack>(builder.build());
    }
    if (request->type == vflip) {
        VerticalFlipBuilder builder;
        return std::make_unique<VerticalFlip>(builder.build());
    }
    if (request->type == rotate90) {
        return createRotate90(request);
    }
    if (request->type == rotate45) {
        return createRotate45(request);
    }
    if (request->type == blurConvolution) {
        return createBlur(request);
    }
    if (request->type == negativeConvolution) {
        return createNegative(request);
    }
    if (request->type == sharpenConvolution) {
        return createSharpen(request);
    }
    if (request->type == embrossConvolution) {
        return createEmbross(request);
    }
    if (request->type == lightBlurConvolution) {
        return createLightBlur(request);
    }
    if (request->type == lightSharpenConvolution) {
        return createLightSharpen(request);
    }
    if (request->type == lightEmbrossConvolution) {
        return createLightEmbross(request);
    }
    if (request->type == gaussBlurConvolution) {
        return createGaussBlur(request);
    }
    if (request->type == randomcrop) {
        return createRandomCrop(request);
    }
}
