#include "guicontroller.h"

GuiController::GuiController(): request()
{
}

std::shared_ptr<Request> GuiController::get_request_from_str(QString name)
{
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
    } else {
        return nullptr;
    }
}

void GuiController::make_request(QStringList algo_list)
{
    foreach (QString algo, algo_list) {
        std::shared_ptr<Request> request_ = get_request_from_str(algo);
        if (request_ != nullptr)
            request.addRequest(request_);
    }
    manager.processRequests(request);
}
QImage GuiController::make_request_preview(QStringList algo_list)
{
    foreach (QString algo, algo_list) {
        std::shared_ptr<Request> request_ = get_request_from_str(algo);
        request.addRequest(request_);
    }

    return manager.preview(request);
}

void GuiController::save_path_in(QString new_path_in)
{
    request.setLoadDirectoryOrFile(new_path_in);
}

void GuiController::save_path_to(QString new_path_to)
{
    request.setSaveDirectory(new_path_to);
}
