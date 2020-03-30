#include "../include/factory.h"
#include "../include/algo.h"
#include "../include/rotate90.h"
#include "../include/verticalflip.h"
#include "../include/horizontalflip.h"
#include "../include/cropfrommiddle.h"
#include <memory>
#include <cassert>

//to do: process wrong arguments
std::unique_ptr<Algorithm> Factory::get_algo(std::shared_ptr<Request> r) {
    if (r->type == crop) {
        CropGivenPieceBuilder builder;
        std::shared_ptr<CropRequest> ptr = std::static_pointer_cast<CropRequest> (r);
        if (ptr->x != -INT_MAX) {
            builder.setX(ptr->x);
        }
        if (ptr->x != -INT_MAX) {
            builder.setY(ptr->y);
        }
        if (ptr->x != -INT_MAX) {
            builder.setCols(ptr->cols);
        }
        if (ptr->x != -INT_MAX) {
            builder.setRows(ptr->rows);
        }
        return std::make_unique<CropGivenPiece>(builder.build());
    }
    if (r->type == hflip) {
        return std::make_unique<HorizontalFlip>();
    }
    if (r->type == vflip) {
        return std::make_unique<VerticalFlip>();
    }
    if (r->type == rotate90) {
        Rotate90Builder builder;
        return std::make_unique<Rotate90>(builder.build());
    }
    if (r->type == rotate45) {
        Rotate45Builder builder;
        return std::make_unique<Rotate45>(builder.build());
    }
}
