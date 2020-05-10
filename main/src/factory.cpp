#include "../include/factory.h"
#include "../include/algo.h"
#include "../include/rotate90.h"
#include "../include/verticalflip.h"
#include "../include/horizontalflip.h"
#include "../include/cropfrommiddle.h"
#include "../include/dithering.h"
#include "../include/gaussiannoise.h"
#include "../include/kuwahara.h"
#include "../include/lightening.h"
#include "../include/whiteblack.h"
#include <memory>
#include <cassert>

//to do: process wrong arguments
std::unique_ptr<Algorithm> Factory::getAlgo(std::shared_ptr<Request> r) {
    if (r->type == crop) {
        CropGivenPieceBuilder builder;
        std::shared_ptr<CropRequest> ptr = std::static_pointer_cast<CropRequest> (r);
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
    if (r->type == gaussiannoise) {
        GaussianNoiseBuilder builder;
        std::shared_ptr<GaussianNoiseRequest> ptr =
                std::static_pointer_cast<GaussianNoiseRequest> (r);
        if (ptr->isSetDegreeOfNoise) {
            builder.setDegreeOfNoise(ptr->degreeOfNoise);
        }
        if (ptr->isSetMono) {
            builder.setMono(ptr->mono);
        }
        return std::make_unique<GaussianNoise>(builder.build());
    }
    if (r->type == dithering) {
        DitheringBuilder builder;
        return std::make_unique<Dithering>(builder.build());
    }
    if (r->type == kuwahara) {
        KuwaharaBuilder builder;
        std::shared_ptr<KuwaharaRequest> ptr =
                std::static_pointer_cast<KuwaharaRequest> (r);
        if (ptr->isSetDegreeOfBlur) {
            builder.setDegreeOfBlur(ptr->degreeOfBlur);
        }
        return std::make_unique<Kuwahara>(builder.build());
    }
    if (r->type == light) {
        LighteningBuilder builder;
        std::shared_ptr<LighteningRequest> ptr =
                std::static_pointer_cast<LighteningRequest> (r);
        if (ptr->isSetDegreeOfLightening) {
            builder.setdDegreeOfLightening(ptr->degreeOfLightening);
        }
        return std::make_unique<Lightening>(builder.build());
    }
    if (r->type == rgb) {
        RGBToneBuilder builder;
        std::shared_ptr<RGBToneRequest> ptr =
                std::static_pointer_cast<RGBToneRequest> (r);
        if (ptr->isSetDegreeOfTone) {
            builder.setdDegreeOfTone(ptr->degreeOfTone);
        }
        if (ptr->isSetColor) {
            builder.setColor(ptr->color);
        }
        return std::make_unique<RGBTone>(builder.build());
    }
    if (r->type == convolution) {
        MatrixConvolutionBuilder builder;
        std::shared_ptr<MatrixConvolutionRequest> ptr =
                std::static_pointer_cast<MatrixConvolutionRequest> (r);
        if (ptr->isSetWorkingDegree) {
            builder.setWorkingDegree(ptr->degree);
        }
        if (ptr->isSetWorkingMode) {
            builder.setWorkingMode(ptr->mode);
        }
        return std::make_unique<MatrixConvolution>(builder.build());
    }
    if (r->type == hflip) {
        HorizontalFlipBuilder builder;
        return std::make_unique<HorizontalFlip>(builder.build());
    }
    if (r->type == whiteblack) {
        WhiteBlackBuilder builder;
        return std::make_unique<WhiteBlack>(builder.build());
    }
    if (r->type == vflip) {
        VerticalFlipBuilder builder;
        return std::make_unique<VerticalFlip>(builder.build());
    }
    if (r->type == rotate90) {
        Rotate90Builder builder;
        std::shared_ptr<Rotate90Request> ptr =
                std::static_pointer_cast<Rotate90Request> (r);
        if (ptr->isSetDirection) {
            builder.setDirection(ptr->d);
        }
        return std::make_unique<Rotate90>(builder.build());
    }
    if (r->type == rotate45) {
        Rotate45Builder builder;
        std::shared_ptr<Rotate45Request> ptr =
                std::static_pointer_cast<Rotate45Request> (r);
        if (ptr->isSetdirection45) {
            builder.setDirection(ptr->d);
        }
        return std::make_unique<Rotate45>(builder.build());
    }
}
