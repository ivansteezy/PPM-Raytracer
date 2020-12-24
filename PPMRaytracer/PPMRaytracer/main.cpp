#include <iostream>
#include <fstream>

#include "Vector3.h"
#include "Color.h"

int main() 
{
    const double image_width = 256;
    const double image_height = 256;
    std::ofstream of;

    of.open("image.ppm", std::ios::app);
    of << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = image_height - 1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) 
        {
            rtcr::Color pixelColor(static_cast<double>(i) / (image_width - 1), static_cast<double>(j) / (image_height - 1), 0.25);
            rtcr::ColorPrinter::WriteColor(of, pixelColor);
        }
    }
    of.close();

    std::cout << "Done" << std::endl;
}