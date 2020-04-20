#ifndef REQUEST_H
#define REQUEST_H
#include <QDir>
#include <memory>
#include "rotate90.h"
#include "rotate45.h"
enum {crop, vflip, hflip, rotate90, rotate45};

class Request {
public:
    Request(int type_) : type(type_) {}
    int type = -1;
};

class CropRequest : public Request {
public:
    CropRequest(int x_ = -INT_MAX, int y_ = -INT_MAX, int cols_ = -INT_MAX, int rows_ = -INT_MAX) :
        Request(crop), x(x_), y(y_), cols(cols_), rows(rows_) {}
    int x, y, cols, rows; // x, y - coordinates of upper left corner; cols, rows - width and height of cropping piece
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
    Rotate90Request(Direction90 d_ = CLOCKWISE90) : Request(rotate90), d(d_) {}
    Direction90 d;
};

class Rotate45Request : public Request {
public:
    Rotate45Request(Direction45 d_ = CLOCKWISE45) : Request(rotate45), d(d_) {}
    Direction45 d;
};

class GlobalRequest {
public:
    GlobalRequest(QDir path_from_, QDir path_to_) : path_from(path_from_), path_to(path_to_) {}
    GlobalRequest() = default;
    ~GlobalRequest() = default;
    void set_load_directory(QDir path_from_) {
        path_from = path_from_;
    }
    void set_save_directory(QDir path_to_) {
        path_to = path_to_;
    }

    QDir get_load_directory() {
        return path_from;
    }
    QDir get_save_directory() {
        return path_to;
    }

    void add_request(std::shared_ptr<Request> r) {
        requests.push_back(r);
    }

    std::vector<std::shared_ptr<Request>> get_requests() {
        return requests;
    }

private:
    QDir path_from;
    QDir path_to;
    std::vector<std::shared_ptr<Request>> requests;
};

#endif // REQUEST_H
