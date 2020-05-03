#ifndef CONFIGFILEEXCEPTIONS_H
#define CONFIGFILEEXCEPTIONS_H

#include <exception>
#include <QString>

class ConfigFileException : public std::exception {
protected:
    const char* message = "Unexpected error with config file";
public:
    virtual const char* what() const noexcept {
        return message;
    }
};

class FileNotFoundException : public ConfigFileException {
public:
    FileNotFoundException() { message = "Error: source file/directory not found"; }
};

class FileNotReadableException : public ConfigFileException {
public:
    FileNotReadableException() { message = "Error: unable to read file"; }
    FileNotReadableException(QString error) { message = qPrintable("Error: unable to read file: " + error); }
};

class EmptyFileException : public ConfigFileException {
public:
    EmptyFileException() {
        message = "Error: no data is currently available for reading from file";
    }
};

class KeyNotGivenException : public ConfigFileException {
public:
    KeyNotGivenException() { message = "Error: key was not provided"; }
    KeyNotGivenException(QString key) { message = qPrintable("Error: key "+ key + " is not provided"); }
};

class WrongNumberOfArgumentsException : public ConfigFileException {
public:
    WrongNumberOfArgumentsException() { message = "Error: wrong number of arguments provided"; }
    WrongNumberOfArgumentsException(QString key) {
        message = qPrintable("Error: wrong number of arguments provided in " + key);
    }
};

class WrongValueException : public ConfigFileException {
public:
    WrongValueException() { message = "Error: wrong value"; }
    WrongValueException(QString key) { message = qPrintable("Error: wrong value for key " + key); }
};

class UnrecognisedKeyException : public ConfigFileException {
public:
    UnrecognisedKeyException() { message = "Error: unrecognised key"; }
    UnrecognisedKeyException(QString key) { message = qPrintable("Error: unrecognised key " + key); }
};
#endif // CONFIGFILEEXCEPTIONS_H
