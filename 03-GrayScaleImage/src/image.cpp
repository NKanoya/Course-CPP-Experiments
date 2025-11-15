//
// Created on 2025/11/15.
//

#include "image.hpp"
#include <algorithm>

GrayScaleImage::GrayScaleImage() : m_width(0), m_height(0), m_matrix() {}

GrayScaleImage::GrayScaleImage(unsigned int width, unsigned int height) : m_width(width), m_height(height) {
    m_matrix.resize(width * height);
    std::fill(m_matrix.begin(), m_matrix.end(), 0);
}

GrayScaleImage::GrayScaleImage(const GrayScaleImage& image) noexcept : m_width(image.m_width), m_height(image.m_height), m_matrix(image.m_matrix) {}

GrayScaleImage::GrayScaleImage(GrayScaleImage&& image) noexcept : m_width(image.m_width), m_height(image.m_height), m_matrix(std::move(image.m_matrix)) {}

GrayScaleImage &GrayScaleImage::operator=(const GrayScaleImage& image) noexcept {
    if(&image == this){
        return *this;
    }
    m_width = image.m_width;
    m_height = image.m_height;
    m_matrix = image.m_matrix;
    return *this;
}

GrayScaleImage &GrayScaleImage::operator=(GrayScaleImage &&image) noexcept {
    if(&image == this){
        return *this;
    }
    m_width = image.m_width;
    m_height = image.m_height;
    m_matrix = std::move(image.m_matrix);
    return *this;
}

