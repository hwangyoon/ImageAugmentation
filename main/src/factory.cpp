#include "../include/factory.h"
#include "../include/algo.h"
#include "../include/rotate90clockwise.h"
#include "../include/verticalflip.h"
#include "../include/horizontalflip.h"
#include "../include/cropfrommiddle.h"
#include <memory>
#include <cassert>

//to do: process wrong arguments
std::unique_ptr<Algorithm> factory::get_algo(Request* r) {
    if (r->type == crop) {
        CropRequest* ptr = static_cast<CropRequest*> (r);
        assert(ptr != nullptr);
        return std::make_unique<CropGivenPiece>(ptr->x, ptr->y, ptr->cols, ptr->rows);
    }
    if (r->type == hflip) {
        return std::make_unique<HorizontalFlip>();
    }
    if (r->type == vflip) {
        return std::make_unique<VerticalFlip>();
    }
    if (r->type == rotate) {
        return std::make_unique<Rotate90Clockwise>();
    }
}
