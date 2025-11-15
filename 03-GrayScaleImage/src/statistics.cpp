//
// Created on 2025/11/15.
//

#include "statistics.hpp"
#include <numeric>

static GrayScaleIntervals m_stat;
static uint8_t m_interval_nums;
static uint8_t m_step;

static void constructIntervals(uint8_t interval_nums) {
    if(interval_nums == 0) interval_nums = 10;
    m_interval_nums = interval_nums;
    m_stat.resize(m_interval_nums);
    m_step = static_cast<uint8_t>(256.0 / interval_nums);

    int current = 0;
    for(int i = 0; i < interval_nums - 1; ++i) {
        m_stat[i].interval.begin = current;
        m_stat[i].interval.end = current + m_step - 1;
        current += m_step;
    }

    m_stat[interval_nums - 1].interval.begin = current;
    m_stat[interval_nums - 1].interval.end = 255;
}

static void computeStatistics(const GrayScaleImage& image, uint8_t interval_nums) {
    auto countFunction = [](const uint8_t& pixel){
        m_stat[pixel / m_step].count += 1;
    };

    image.forEach(countFunction);
}

static void computeProportion(const GrayScaleImage& image) {
    uint32_t sum = image.getSize().first * image.getSize().second;
    for(auto& info: m_stat) {
        info.proportion = static_cast<long double>(info.count) / sum * 100;
    }
}

const std::vector<IntervalInfo>& computeGrayScaleIntervals(const GrayScaleImage& image, uint8_t interval_nums) {
    constructIntervals(interval_nums);
    computeStatistics(image, interval_nums);
    computeProportion(image);
    return m_stat;
}

