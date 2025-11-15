//
// Created on 2025/11/15.
//

#include "display.hpp"
#include <iostream>
#include <cmath>

void displayHistogram(const GrayScaleIntervals& intervals) {
    for(auto& current: intervals) {
        auto begin = current.interval.begin;
        auto end = current.interval.end;
        printf("%d ~ %d", current.interval.begin, current.interval.end);
        if((begin == 0 && end > 100) || (begin < 100 && end < 100)) {
            printf("\t");
        }
        printf("\t | ");

        int count = std::ceil(current.proportion / 4.0);
        for(int i = 0; i < count; ++i) {
            printf("*");
        }

        for(int i = count; i < 25; ++i) {
            printf(" ");
        }
        printf(" | ");
        printf("%.2f%%\t\t | %d\n",current.proportion ,current.count );
    }

    std::fflush(stdout);
}

static void repeatPrint(char ch, uint8_t num) {
    for(int i = 0; i < num; ++i) {
        printf("%c", ch);
    }
}

static void printHeading() {
    printf("Interval\t | Histogram");
    repeatPrint(' ', 16);
    printf(" | Proportion\t | Count\n");
    std::fflush(stdout);
}

void imageHistogram(std::string path, uint8_t interval_num) {
    GrayScaleImage img;
    readImage(img, path);
    if(img.empty()) {
        std::cerr << "[WARN]" << path << " is not a valid image\n";
        return;
    }
    printHeading();
    auto& intervals = computeGrayScaleIntervals(img, interval_num);
    displayHistogram(intervals);
}