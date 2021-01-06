// たのしく はじめましよう!
#include <iostream>
#include <fstream>

#include "HittableList.h"
//#include "Material.h"
// #include "Vector3.h"
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

rtcr::Color MapRayColor(const rtcr::Ray<double>& ray, const rtcr::HittableList& world, int depth)
{
    rtcr::HitRecord record;

    if (depth <= 0)
    {
        return rtcr::Color(0.0, 0.0, 0.0);
    }

    if (world.Hit(ray, 0.001, infinity, record))
    {
        /*rtcr::Point3 target = record.p + record.normal + rtcr::RandomUnitVector();
        return 0.5 * MapRayColor(rtcr::Ray<double>(record.p, target - record.p), world, depth-1);*/

        rtcr::Ray<double> scattered;
        rtcr::Color attenuation;

        if (record.materialPtr->Scatter(ray, record, attenuation, scattered))
            return attenuation * MapRayColor(scattered, world, depth - 1);
        return rtcr::Color(0.0, 0.0, 0.0);
    }

    auto unitDirection = rtcr::Vector3<double>::UnitVector(ray.GetDirection());
    auto t = 0.5 * (unitDirection.GetY() + 1.0);
    return (1.0 - t) * rtcr::Color(1.0, 1.0, 1.0) + (t * rtcr::Color(0.5, 0.7, 1.0));
}

int main() 
{
    const auto aspectRatio    = 16.0 / 9.0;
    const double imageWidth   = 1024;
    const double imageHeight  = static_cast<int>(imageWidth / aspectRatio);      // podemos calcular la altura de la imagen dividendolo entre la relacion de aspecto
    const int samplesPerPixel = 20;
    const int maxStackDepth   = 50;

    //World
    rtcr::HittableList world;
    
    auto material_ground = std::make_shared<rtcr::Lambertian>(rtcr::Color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<rtcr::Lambertian>(rtcr::Color(0.7, 0.3, 0.3));
    auto material_left   = std::make_shared<rtcr::Metal>(rtcr::Color(0.8, 0.8, 0.8));
    auto material_right  = std::make_shared<rtcr::Metal>(rtcr::Color(0.8, 0.6, 0.2));

    world.Add(std::make_shared<rtcr::Sphere>(rtcr::Point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.Add(std::make_shared<rtcr::Sphere>(rtcr::Point3(0.0, 0.0, -1.0), 0.5, material_center));
    world.Add(std::make_shared<rtcr::Sphere>(rtcr::Point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.Add(std::make_shared<rtcr::Sphere>(rtcr::Point3(1.0, 0.0, -1.0), 0.5, material_right));

    // Camera
    rtcr::Camera camera;

    std::ofstream of;
    of.open("image.ppm", std::ios::app);
    of << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = imageHeight - 1; j >= 0; --j) 
    {
        std::cerr << "\rHorizontal Scanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i)
        {
            rtcr::Color pixelColor(0, 0, 0);
            for (int s = 0; s < samplesPerPixel; ++s)
            {
                auto u = (i + GenRandomNumber()) / (imageWidth - 1);
                auto v = (j + GenRandomNumber()) / (imageHeight - 1);
                auto ray = camera.GetRay(u, v);
                pixelColor += MapRayColor(ray, world, maxStackDepth);
            }
            rtcr::WriteColor(of, pixelColor, samplesPerPixel);
        }
    }

    std::cout << "Done!" << std::endl;
    of.close();
}