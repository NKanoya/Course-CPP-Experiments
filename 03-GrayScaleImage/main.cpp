#include "image.hpp"
#include "imread.hpp"

int main() {
    GrayScaleImage img;
    readImage(img, "test.png");
    return 0;
}
