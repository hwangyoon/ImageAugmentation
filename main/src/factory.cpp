#include "../include/factory.h"
#include "../include/algo.h"
#include "../include/rotate90clockwise.h"
#include "../include/verticalflip.h"
#include "../include/horizontalflip.h"
#include "../include/cropfrommiddle.h"
#include <memory>
#include <cassert>

//to do: process wrong arguments
<<<<<<< HEAD
std::unique_ptr<Algorithm> Factory::get_algo(Request* r) {
    if (r->type == crop) {
        CropRequest* ptr = static_cast<CropRequest*> (r);
=======
std::unique_ptr<Algorithm> factory::get_algo(Request* r) {
    if (r->type == crop) {
        CropRequest* ptr = static_cast<CropRequest*> (r);
        assert(ptr != nullptr);
>>>>>>> b12925ec1e8740785930234c87e00b42fe562cbe
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
