﻿// たのしく はじめましよう!
#include <iostream>
#include <fstream>

#include "HittableList.h"
#include "Foundation.h"
#include "Camera.h"
#include "Sphere.h"
#include "Color.h"


double RayHitSphere(const rtcr::Point3& center, double radius, const rtcr::Ray<double>& ray)
{
    auto oc = ray.GetOrigin() - center;                                                  // in the equation (A-C)
    auto a  = rtcr::Vector3<double>::DotProduct(ray.GetDirection(), ray.GetDirection()); // in the equation (b°b)
    auto b  = 2.0 * rtcr::Vector3<double>::DotProduct(oc, ray.GetDirection());           // in the equation 2b ° (A-C)
    auto c  = rtcr::Vector3<double>::DotProduct(oc, oc) - (radius * radius);             // in the equation (A-C)°(A-C) - r^2
    auto discriminant = (b * b) - (4 * a * c);                                           // chicharronera

    return discriminant < 0 ? -1.0 : (-b - std::sqrt(discriminant)) / (2.0 * a);
}

rtcr::Color MapRayColor(const rtcr::Ray<double>& ray, const rtcr::HittableList& world)
{
    rtcr::HitRecord record;
    if (world.Hit(ray, 0, infinity, record))
    {
        return 0.5 * (record.normal + rtcr::Color(1, 1, 1));
    }

    auto unitDirection = rtcr::Vector3<double>::UnitVector(ray.GetDirection());
    auto t = 0.5 * (unitDirection.GetY() + 1.0);
    return (1.0 - t) * rtcr::Color(1.0, 1.0, 1.0) + (t * rtcr::Color(0.0, 0.0, 1.0));
}

int main() 
{
    const auto aspectRatio   = 16.0 / 9.0;
    const double imageWidth  = 800;
    const double imageHeight = static_cast<int>(imageWidth / aspectRatio);      // podemos calcular la altura de la imagen dividendolo entre la relacion de aspecto
    const int samplesPerPixel = 0;

    //World
    rtcr::HittableList world;
    world.Add(std::make_shared<rtcr::Sphere>(rtcr::Point3(0, 0, -1), 0.5));
    world.Add(std::make_shared<rtcr::Sphere>(rtcr::Point3(0, -100.5, -1), 100));

    // Camera
    rtcr::Camera camera;

    std::ofstream of;
    of.open("image.ppm", std::ios::app);
    of << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = imageHeight - 1; j >= 0; --j) 
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i)
        {
            rtcr::Color pixelColor(0, 0, 0);
            for (int s = 0; s < samplesPerPixel; ++s)
            {
                auto u = (i + GenRandomNumber()) / (imageWidth - 1);
                auto v = (j + GenRandomNumber()) / (imageHeight - 1);
                auto ray = camera.GetRay(u, v);
                pixelColor += MapRayColor(ray, world);
            }
            rtcr::WriteColor(of, pixelColor, samplesPerPixel);
        }
    }
    of.close();

    std::cout << "Done!" << std::endl;
}