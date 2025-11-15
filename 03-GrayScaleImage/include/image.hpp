//
// Created on 2025/11/15.
//

#ifndef GRAYSCALEIMAGE_IMAGE_HPP
#define GRAYSCALEIMAGE_IMAGE_HPP

#include <cstdint>
#include <vector>

class GrayScaleImage {
    unsigned int m_width;
    unsigned int m_height;

    std::vector<uint8_t> m_matrix;

public:
    GrayScaleImage();
    GrayScaleImage(unsigned int width, unsigned int height);

    GrayScaleImage(const GrayScaleImage& image) noexcept;
    GrayScaleImage(GrayScaleImage&& image) noexcept;
    GrayScaleImage& operator=(const GrayScaleImage& image) noexcept;
    GrayScaleImage& operator=(GrayScaleImage&& image) noexcept;

    inline std::pair<std::size_t, std::size_t> getSize() const {
        return {m_width, m_height};
    }

    inline uint8_t& getPixel(unsigned int x, unsigned y) {
        return m_matrix[y * m_height + x];
    }

    inline bool empty() const noexcept {
        return m_matrix.empty();
    }

    template <class Func>
    void forEach(Func&& func) {
        for(auto& px: m_matrix) {
            func(px);
        }
    }

    template <class Func>
    void forEach(Func&& func) const {
        for(const auto& px: m_matrix) {
            func(px);
        }
    }
};

#endif //GRAYSCALEIMAGE_IMAGE_HPP
