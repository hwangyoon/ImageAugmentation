#ifndef REQUEST_H
#define REQUEST_H
enum {crop, vflip, hflip, rotate};

class Request {
public:
    Request(int type_) : type(type_) {}
    int type = -1;
};

class CropRequest : public Request {
public:
    CropRequest(int x_, int y_, int cols_, int rows_) : Request(crop), x(x_), y(y_), cols(cols_), rows(rows_) {}
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

class RotateRequest : public Request {
public:
    RotateRequest() : Request(rotate) {}
};

#endif // REQUEST_H
