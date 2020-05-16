#ifndef JSONFILEPARSER_H
#define JSONFILEPARSER_H

#include <QJsonObject>
#include <QJsonValue>
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include "request.h"
#include "configfileexceptions.h"
#include "enumconvolution.h"

/* A class that provides parses config file in json format */
class JsonParser {
public:
    JsonParser() = default;
    /* Gets GlobalRequest from given configuration file
    throws exception if file or format is invalid */
    GlobalRequest getInformationFromConfigFile(QFile& file);
private:
    /* Verifies that config file exists and can be parsed */
    void checkConfigFileCorrect(QFile& file) const;
    /* Gets argument for the given key
     * throws exception if it is not provided */
    QJsonValue getValue(const QJsonObject& data, const QString& key);
};

#endif // JSONFILEPARSER_H
