#include "guicontroller.h"

GuiController::GuiController(): request() {
}


std::shared_ptr<Request> GuiController::getRequestFromString(QString name) {
    if (name == "Crop from middle") {
        return std::make_shared<CropRequest>();
    } else if (name == "Horizontal flip") {
        return std::make_shared<FlipHRequest>();
    } else if (name == "Vertical flip") {
        return std::make_shared<FlipVRequest>();
    } else if (name == "Rotate 90 dg") {
        return std::make_shared<Rotate90Request>();
    } else if (name == "Rotate 45 dg") {
        return std::make_shared<Rotate45Request>();
    } else if (name == "Dithering") {
        return std::make_shared<DitheringRequest>();
    } else if (name == "GaussianNoise") {
        return std::make_shared<GaussianNoiseRequest>();
    } else if (name == "Kuwahara") {
        return std::make_shared<KuwaharaRequest>();
    } else if (name == "Lightening") {
        return std::make_shared<LighteningRequest>();
    } else if (name == "RGBTone") {
        return std::make_shared<RGBToneRequest>();
    } else if (name == "WhiteBlack") {
        return std::make_shared<WhiteBlackRequest>();
    }  else if (name == "BlurConvolution") {
        return std::make_shared<BlurConvolutionRequest>();
    }  else if (name == "NegativeConvolution") {
        return std::make_shared<NegativeConvolutionRequest>();
    }  else if (name == "SharpenConvolution") {
        return std::make_shared<SharpenConvolutionRequest>();
    }  else if (name == "EmbrossConvolution") {
        return std::make_shared<EmbrossConvolutionRequest>();
    }  else if (name == "LightBlurConvolution") {
        return std::make_shared<LightBlurConvolutionRequest>();
    }  else if (name == "LightSharpenConvolution") {
        return std::make_shared<LightSharpenConvolutionRequest>();
    }  else if (name == "LightEmbrossConvolution") {
        return std::make_shared<LightEmbrossConvolutionRequest>();
    }  else if (name == "GaussBlurConvolution") {
        return std::make_shared<GaussBlurConvolutionRequest>();
    } else {
        return nullptr;
    }
}

void GuiController::makeRequest(QStringList algoList, bool overlay) {
    foreach (QString algo, algoList) {
        std::shared_ptr<Request> request_ = getRequestFromString(algo);
        if (request_ != nullptr)
            request.addRequest(request_);
    }
    if (overlay) {
        request.setDepthOfOverlay({algoList.size()});
    } else {
        request.setDepthOfOverlay({1});
    }
    manager.processRequests(request);
}
QImage GuiController::makeRequestPreview(QStringList algoList) {
    foreach (QString algo, algoList) {
        std::shared_ptr<Request> request_ = getRequestFromString(algo);
        request.addRequest(request_);
    }

    return manager.preview(request);
}

void GuiController::savePathIn(QString newPathIn) {
    request.setLoadDirectoryOrFile(newPathIn);
}

void GuiController::savePathTo(QString newPathTo) {
    request.setSaveDirectory(newPathTo);
}
