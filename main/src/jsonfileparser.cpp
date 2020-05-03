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
    if (data.contains("rotate90")) {
        if (data.value("rotate90").toString() == "CLOCKWISE90") {
            request.addRequest(std::make_shared<Rotate90Request>(CLOCKWISE90));
        } else if (data.value("rotate90").toString() == "COUNTERCLOCKWISE90") {
            request.addRequest(std::make_shared<Rotate90Request>(COUNTERCLOCKWISE90));
        } else {
            throw WrongValueException("rotate90");
        }
    }
    if (data.contains("rotate45")) {
        if (data.value("rotate45").toString() == "CLOCKWISE45") {
            request.addRequest(std::make_shared<Rotate45Request>(CLOCKWISE45));
        } else if (data.value("rotate45").toString() == "COUNTERCLOCKWISE45") {
            request.addRequest(std::make_shared<Rotate45Request>(COUNTERCLOCKWISE45));
        } else {
            throw WrongValueException("rotate45");
        }
    }
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
    if (data.contains("rgbtone")) {
        QJsonObject rgbtone = data["rgbtone"].toObject();
        QVariant degree;
        QVariant color;
        if (rgbtone.size() == 0 || rgbtone.size() > 2) {
            throw WrongNumberOfArgumentsException("rgbtone");
        }
        if (rgbtone.contains("degreeOfTone")) {
            degree = rgbtone["degreeOfTone"].toInt();
        }
        if (rgbtone.contains("color")) {
            color = rgbtone["color"].toString();
        }
        if (!degree.isNull() && !color.isNull()) {
            if (color == "RED") {
                request.addRequest(std::make_shared<RGBToneRequest>(degree.toInt(), RED));
            }
            if (color == "GREEN") {
                request.addRequest(std::make_shared<RGBToneRequest>(degree.toInt(), GREEN));
            }
            if (color == "BLUE") {
                request.addRequest(std::make_shared<RGBToneRequest>(degree.toInt(), BLUE));
            }
        }
        if (degree.isNull() && !color.isNull()) {
            auto req = std::make_shared<RGBToneRequest>();
            if (color == "RED") {
                req->setColor(RED);
            }
            if (color == "GREEN") {
                req->setColor(GREEN);
            }
            if (color == "BLUE") {
                req->setColor(BLUE);
            }
            request.addRequest(req);
        }
        if (!degree.isNull() && color.isNull()) {
            auto req = std::make_shared<RGBToneRequest>();
            req->setDegreeOfTone(degree.toInt());
            request.addRequest(req);
        }
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
            } else {
                throw UnrecognisedKeyException();
            }
        }
    }
    return request;
}
