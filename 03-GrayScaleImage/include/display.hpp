//
// Created on 2025/11/15.
//

#ifndef GRAYSCALEIMAGE_DISPLAY_HPP
#define GRAYSCALEIMAGE_DISPLAY_HPP


#include "image.hpp"
#include "imread.hpp"
#include "statistics.hpp"

void displayHistogram(const GrayScaleIntervals& intervals);

void imageHistogram(std::string path, uint8_t interval_num);

#endif //GRAYSCALEIMAGE_DISPLAY_HPP
