#include "../include/jsonfileparser.h"
#include <cassert>

void JsonParser::checkConfigFileCorrect(QFile& file) const {
    if (!file.exists()){
        throw FileNotFoundException();
    }
    QFileDevice::FileError err = QFileDevice::NoError;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //specify error
        err = file.error();
        throw FileNotReadableException(QString(err));
    }
    QString settings = file.readAll();
    if (file.error() != QFile::NoError) {
        file.close();
        throw FileNotReadableException();
    }
    if (settings.isEmpty()) {
        file.close();
        throw EmptyFileException();
    }
    file.close();
}

QJsonValue JsonParser::getValue(const QJsonObject& data, const QString& key) {
    QJsonValue value = data[key];
    if (value.isUndefined()) {
        throw KeyNotGivenException(QString(key));
    }
    return value;
}

GlobalRequest JsonParser::getInformationFromConfigFile(QFile& file) {
    GlobalRequest request;
    checkConfigFileCorrect(file);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString settings = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(settings.toUtf8());
    if (doc.isNull()) {
        throw FileNotReadableException();
    }
    QJsonObject data = doc.object();
    if (data.contains("crop")) {
        QJsonObject crop = data["crop"].toObject();
        int upperLeftXInPercent = getValue(crop, "upperLeftXInPercent").toInt();
        int upperLeftYInPercent = getValue(crop, "upperLeftYInPercent").toInt();
        int downRightXInPercent = getValue(crop, "downRightXInPercent").toInt();
        int downRightYInPercent = getValue(crop, "downRightYInPercent").toInt();
        if (crop.size() != 4) {
            throw WrongNumberOfArgumentsException("crop");
        }
        request.addRequest(std::make_shared<CropRequest>(upperLeftXInPercent,
                                                          upperLeftYInPercent,
                                                          downRightXInPercent,
                                                          downRightYInPercent));
    }
    if (data.contains("blur")) {
        QJsonObject blur_ = data["blur"].toObject();
        int degree = getValue(blur_, "degree").toInt();
        request.addRequest(std::make_shared<MatrixConvolutionRequest>(degree, blur));
    }
    if (data.contains("negative")) {
        QJsonObject negative_ = data["negative"].toObject();
        int degree = getValue(negative_, "degree").toInt();
        request.addRequest(std::make_shared<MatrixConvolutionRequest>(degree, negative));
    }
    if (data.contains("sharpen")) {
        QJsonObject sharpen_ = data["sharpen"].toObject();
        int degree = getValue(sharpen_, "degree").toInt();
        request.addRequest(std::make_shared<MatrixConvolutionRequest>(degree, sharpen));
    }
    if (data.contains("embross")) {
        QJsonObject embross_ = data["embross"].toObject();
        int degree = getValue(embross_, "degree").toInt();
        request.addRequest(std::make_shared<MatrixConvolutionRequest>(degree, embross));
    }
    if (data.contains("lightBlur")) {
        QJsonObject lightBlur_ = data["lightBlur"].toObject();
        int degree = getValue(lightBlur_, "degree").toInt();
        request.addRequest(std::make_shared<MatrixConvolutionRequest>(degree, lightBlur));
    }
    if (data.contains("lightSharpen")) {
        QJsonObject lightSharpen_ = data["lightSharpen"].toObject();
        int degree = getValue(lightSharpen_, "degree").toInt();
        request.addRequest(std::make_shared<MatrixConvolutionRequest>(degree, lightSharpen));
    }
    if (data.contains("lightEmbross")) {
        QJsonObject lightEmbross_ = data["lightEmbross"].toObject();
        int degree = getValue(lightEmbross_, "degree").toInt();
        request.addRequest(std::make_shared<MatrixConvolutionRequest>(degree, lightEmbross));
    }
    if (data.contains("gaussBlur")) {
        QJsonObject gaussBlur_ = data["gaussBlur"].toObject();
        int degree = getValue(gaussBlur_, "degree").toInt();
        request.addRequest(std::make_shared<MatrixConvolutionRequest>(degree, gaussBlur));
    }
    if (data.contains("gaussiannoise")) {
        QJsonObject gaussnoise = data["gaussiannoise"].toObject();
        QVariant degree;
        QVariant mono;
        if (gaussnoise.size() == 0 || gaussnoise.size() > 2) {
            throw WrongNumberOfArgumentsException("gaussiannoise");
        }
        if (gaussnoise.contains("degreeOfNoise")) {
            degree = gaussnoise["degreeOfNoise"].toInt();
        }
        if (gaussnoise.contains("mono")) {
            mono = gaussnoise["mono"].toBool();
        }
        if (!degree.isNull() && !mono.isNull()) {
            request.addRequest(std::make_shared<GaussianNoiseRequest>(degree.toInt(), mono.toBool()));
        }
        if (degree.isNull() && !mono.isNull()) {
            request.addRequest(std::make_shared<GaussianNoiseRequest>(mono.toBool()));
        }
        if (!degree.isNull() && mono.isNull()) {
            request.addRequest(std::make_shared<GaussianNoiseRequest>(degree.toInt()));
        }
    }
    if (data.contains("redRGBTone")) {
        QJsonObject redRGBTone = data["redRGBTone"].toObject();
        int degreeOfTone = getValue(redRGBTone, "degreeOfTone").toInt();
        request.addRequest(std::make_shared<RGBToneRequest>(degreeOfTone, RED));
    }
    if (data.contains("blueRGBTone")) {
        QJsonObject blueRGBTone = data["blueRGBTone"].toObject();
        int degreeOfTone = getValue(blueRGBTone, "degreeOfTone").toInt();
        request.addRequest(std::make_shared<RGBToneRequest>(degreeOfTone, BLUE));
    }
    if (data.contains("greenRGBTone")) {
        QJsonObject greenRGBTone = data["greenRGBTone"].toObject();
        int degreeOfTone = getValue(greenRGBTone, "degreeOfTone").toInt();
        request.addRequest(std::make_shared<RGBToneRequest>(degreeOfTone, GREEN));
    }
    if (data.contains("kuwahara")) {
        QJsonObject kuwahara = data["kuwahara"].toObject();
        QVariant degree;
        if (kuwahara.size() != 1) {
            throw WrongNumberOfArgumentsException("kuwahara");
        }
        degree = getValue(kuwahara, "degreeOfBlur").toInt();
        request.addRequest(std::make_shared<KuwaharaRequest>(degree.toInt()));
    }
    if (data.contains("lightening")) {
        QJsonObject lightening = data["lightening"].toObject();
        QVariant degree;
        if (lightening.size() != 1) {
            throw WrongNumberOfArgumentsException("lightening");
        }
        degree = getValue(lightening, "degreeOfLightening").toInt();
        request.addRequest(std::make_shared<LighteningRequest>(degree.toInt()));
    }
    if (data.contains("enable")) {
        QJsonValue value = data.value("enable");
        QJsonArray array = value.toArray();
        for (auto algo : array) {
            if (algo.toString() == "hflip") {
                request.addRequest(std::make_shared<FlipHRequest>());
            } else if (algo.toString() == "vflip") {
                request.addRequest(std::make_shared<FlipVRequest>());
            } else if (algo.toString() == "dithering") {
                request.addRequest(std::make_shared<DitheringRequest>());
            } else if (algo.toString() == "whiteblack") {
                request.addRequest(std::make_shared<WhiteBlackRequest>());
            } else if (algo.toString() == "rotate90Clockwise") {
                request.addRequest(std::make_shared<Rotate90Request>(CLOCKWISE90));
            } else if (algo.toString() == "rotate90Counterclockwise") {
                request.addRequest(std::make_shared<Rotate90Request>(COUNTERCLOCKWISE90));
            } else if (algo.toString() == "rotate45Clockwise") {
                request.addRequest(std::make_shared<Rotate45Request>(CLOCKWISE45));
            } else if (algo.toString() == "rotate45Counterclockwise") {
                request.addRequest(std::make_shared<Rotate45Request>(COUNTERCLOCKWISE45));
            } else {
                throw UnrecognisedKeyException();
            }
        }
    }
    return request;
}
