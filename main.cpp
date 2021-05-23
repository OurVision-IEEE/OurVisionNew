#include <iostream>
#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>
#include <vector>
#include <algorithm>

const std::string image_path = "../billboard.jpeg";

std::string get_output_string(const std::string *image_path, const tesseract::PageSegMode segmentation_mode);
void perform_ocr(tesseract::PageSegMode segmentation_mode);

int main() {
    std::vector<tesseract::PageSegMode> segmentation_modes;
    segmentation_modes.push_back(tesseract::PSM_SINGLE_BLOCK);
    segmentation_modes.push_back(tesseract::PSM_AUTO);
    segmentation_modes.push_back(tesseract::PSM_AUTO_ONLY);
    segmentation_modes.push_back(tesseract::PSM_AUTO_OSD);
    segmentation_modes.push_back(tesseract::PSM_CIRCLE_WORD);

    std::for_each(segmentation_modes.begin(), segmentation_modes.end(), perform_ocr);

    return 0;
}

void perform_ocr(tesseract::PageSegMode segmentation_mode) {
    const std::string output_text = get_output_string(&image_path, segmentation_mode);
    std::cout << output_text << std::endl;
}
std::string get_output_string(const std::string *image_path, const tesseract::PageSegMode segmentation_mode) {
    char *output_text;

    auto *api = new tesseract::TessBaseAPI();

    if (api->Init(nullptr, "eng", tesseract::OEM_LSTM_ONLY)) {
        std::string error_message = "There was an error with tesseract API. Contact Tejas M R for this.";
        std::cout << error_message;
        return error_message;
    }

    cv::Mat image = cv::imread(*image_path);
    api->SetImage(image.data, image.cols, image.rows, 3, image.step);
    api->SetSourceResolution(343);
    api->SetPageSegMode(segmentation_mode);
    output_text = api->GetUTF8Text();
    std::string output_string(output_text);

    api->End();
    delete api;
    delete [] output_text;
    return output_string;
}
