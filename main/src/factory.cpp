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
            builder.setUpperLeftXInPercent(ptr->x);
        }
        if (ptr->x != -INT_MAX) {
            builder.setUpperLeftYInPercent(ptr->y);
        }
        if (ptr->x != -INT_MAX) {
            builder.setDownRightXInPercent(ptr->cols);
        }
        if (ptr->x != -INT_MAX) {
            builder.setDownRightYInPercent(ptr->rows);
        }
        return std::make_unique<CropGivenPiece>(builder.build());
    }
    if (r->type == hflip) {
        HorizontalFlipBuilder builder;
        return std::make_unique<HorizontalFlip>(builder.build());
    }
    if (r->type == vflip) {
        VerticalFlipBuilder builder;
        return std::make_unique<VerticalFlip>(builder.build());
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
