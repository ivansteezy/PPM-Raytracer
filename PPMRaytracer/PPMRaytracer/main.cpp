// たのしく はじめましよう!
#include <iostream>
#include <fstream>

#include "HittableList.h"
#include "Foundation.h"
#include "Sphere.h"
#include "Color.h"


double RayHitSphere(const rtcr::Point3& center, double radius, const rtcr::Ray<double>& ray)
{
    auto oc = ray.GetOrigin() - center;                                                  //in the equation (A-C)
    auto a  = rtcr::Vector3<double>::DotProduct(ray.GetDirection(), ray.GetDirection()); //in the equation (b°b)
    auto b  = 2.0 * rtcr::Vector3<double>::DotProduct(oc, ray.GetDirection());           //in the equation 2b ° (A-C)
    auto c  = rtcr::Vector3<double>::DotProduct(oc, oc) - (radius * radius);             //in the equation (A-C)°(A-C) - r^2
    auto discriminant = (b * b) - (4 * a * c);                                           //chicharronera

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
    const double imageWidth  = 400;
    const double imageHeight = static_cast<int>(imageWidth / aspectRatio);      // podemos calcular la altura de la imagen dividendolo entre la relacion de aspecto

    //World
    rtcr::HittableList world;
    world.Add(std::make_shared<rtcr::Sphere>(rtcr::Point3(0, 0, -1), 0.5));
    world.Add(std::make_shared<rtcr::Sphere>(rtcr::Point3(0, -100.5, -1), 100));

    // Camera
    auto viewportHeight = 2.0;                                                  // altura de la visibilidad
    auto viewportWidth  = aspectRatio * viewportHeight;                         //anchura de la visibildad
    auto focalLength    = 1.0;                                                  //distancia focal a travez de la cual se ve la imagen (zoom)

    auto origin          = rtcr::Point3(0, 0, 0);                               //punto de origen de la camara
    auto horizontal      = rtcr::Vector3<double>(viewportWidth, 0, 0);
    auto vertical        = rtcr::Vector3<double>(0, viewportHeight, 0);
    auto lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - rtcr::Vector3<double>(0, 0, focalLength);

    std::ofstream of;

    of.open("image.ppm", std::ios::app);
    of << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
    for (int j = imageHeight - 1; j >= 0; --j) {
        for (int i = 0; i < imageWidth; ++i)
        {
            auto u = double(i) / (imageWidth - 1.0);
            auto v = double(j) / (imageHeight - 1.0);
            rtcr::Ray<double> r(origin, lowerLeftCorner + u * horizontal + v * vertical - origin); //rayo recibe un origen y una direccion, 
            rtcr::Color pixel_color = MapRayColor(r, world);
            rtcr::ColorPrinter::WriteColor(of, pixel_color);
        }
    }
    of.close();

    std::cout << "Done!" << std::endl;
}