//
// Created by pilip on 2025/11/15.
//

#include "image.hpp"
#include <algorithm>

Image::Image() : m_width(0), m_height(0), m_matrix() {}

Image::Image(unsigned int width, unsigned int height) : m_width(width), m_height(height) {
    m_matrix.resize(width * height);
    std::fill(m_matrix.begin(), m_matrix.end(), 0);
}

Image::Image(const Image& image) noexcept : m_width(image.m_width), m_height(image.m_height), m_matrix(image.m_matrix) {}

Image::Image(Image&& image) noexcept : m_width(image.m_width), m_height(image.m_height), m_matrix(std::move(image.m_matrix)) {}

