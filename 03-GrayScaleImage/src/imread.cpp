//
// Created on 2025/11/15.
//

#include "imread.hpp"
#include <fstream>
#include <opencv2/opencv.hpp>

static void cvMatToImage(cv::Mat& mat, GrayScaleImage& image) {
    for(int i = 0; i < mat.size().height; ++i) {
        auto ptr = mat.ptr<uint8_t>(i);
        for(int j = 0; j < mat.size().width; ++j) {
            image.getPixel(i,j) = *(ptr + j);
        }
    }
}


void readImage(GrayScaleImage& image, const std::string& path) {
    cv::Mat mat = cv::imread(path, cv::IMREAD_GRAYSCALE);
    if(mat.empty()){
        image = GrayScaleImage(0,0);
        return;
    }

    image = GrayScaleImage(mat.size().width, mat.size().height);

    if(mat.type() == CV_8UC1) {
        cvMatToImage(mat, image);
    } else {
        cv::Mat converted_mat;
        // convert non-8UC1 mat to 8UC1
        mat.convertTo(converted_mat, CV_8UC1);
        cvMatToImage(converted_mat, image);
    }
}
