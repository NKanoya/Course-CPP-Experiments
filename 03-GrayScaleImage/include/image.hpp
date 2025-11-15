//
// Created by pilip on 2025/11/15.
//

#ifndef GRAYSCALEIMAGE_IMAGE_HPP
#define GRAYSCALEIMAGE_IMAGE_HPP

#include <cstdint>
#include <vector>

class Image {
    unsigned int m_width;
    unsigned int m_height;

    std::vector<uint8_t> m_matrix;

public:
    Image();
    Image(unsigned int width, unsigned int height);
    Image(const Image& image) noexcept;
    Image(Image&& image) noexcept;

    inline uint8_t& getPixel(unsigned int x, unsigned y) {
        return m_matrix[y * m_height + x];
    }

    inline bool empty() const noexcept {
        return m_matrix.empty();
    }
};

#endif //GRAYSCALEIMAGE_IMAGE_HPP
