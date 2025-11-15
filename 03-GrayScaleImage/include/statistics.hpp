//
// Created on 2025/11/15.
//

#ifndef GRAYSCALEIMAGE_STATISTICS_HPP
#define GRAYSCALEIMAGE_STATISTICS_HPP

#include "image.hpp"

struct IntervalInfo{
    struct {
        uint8_t begin;
        uint8_t end;
    } interval;

    std::size_t count;
    double proportion;
};

using GrayScaleIntervals = std::vector<IntervalInfo>;

const GrayScaleIntervals& computeGrayScaleIntervals(const GrayScaleImage& image, uint8_t interval_nums);

#endif //GRAYSCALEIMAGE_STATISTICS_HPP
