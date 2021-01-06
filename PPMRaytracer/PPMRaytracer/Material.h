#ifndef MATERIAL_H
#define MATERIAL_H

#include "Foundation.h"
//#include "Vector3.h"
//#include "Ray.h"

namespace rtcr
{
	struct HitRecord;

	interface Material
	{
		virtual bool Scatter(const rtcr::Ray<double>& rayIn, const rtcr::HitRecord& record, rtcr::Color& attenuation, rtcr::Ray<double>& scattered) const = 0;
	};

	using MaterialPtr = std::shared_ptr<Material>;

	struct HitRecord
	{
		rtcr::Point3 p{};
		rtcr::Vector3<double> normal{};
		std::shared_ptr<rtcr::Material> materialPtr;
		double t{ 0.0 };
		bool frontFace{ false };

		inline void SetFaceNormal(const rtcr::Ray<double>& ray, const rtcr::Vector3<double>& outNormal)
		{
			frontFace = rtcr::Vector3<double>::DotProduct(ray.GetDirection(), outNormal) < 0;
			normal = frontFace ? outNormal : -outNormal;
		}
	};

	interface Hittable
	{
		virtual bool Hit(const rtcr::Ray<double>& ray, double tMin, double tMax, HitRecord& rec) const = 0;
	};

	using HittablePtr = std::shared_ptr<Hittable>;

	class Lambertian : public Material
	{
	public:
		Lambertian(const rtcr::Color& a) : albedo(a) {}
		virtual bool Scatter(const rtcr::Ray<double>& rayIn, const rtcr::HitRecord& record, rtcr::Color& attenuation, rtcr::Ray<double>& scattered) const override
		{
			auto scatterDirection = record.normal + rtcr::Vector3<double>::RandomUnitVector();
			scattered = rtcr::Ray<double>(record.p, scatterDirection);
			attenuation = albedo;

			return true;
		}

	public:
		rtcr::Color albedo;
	};

	class Metal : public Material
	{
	public:
		Metal(const rtcr::Color& a) : albedo(a) {}
		virtual bool Scatter(const rtcr::Ray<double>& rayIn, const rtcr::HitRecord& record, rtcr::Color& attenuation, rtcr::Ray<double>& scattered) const override
		{
			auto reflected = rtcr::Vector3<double>::Reflect(rtcr::Vector3<double>::UnitVector(rayIn.GetDirection()), record.normal);
			scattered = rtcr::Ray<double>(record.p, reflected);
			attenuation = albedo;

			return (rtcr::Vector3<double>::DotProduct(scattered.GetDirection(), record.normal) > 0);
		}

	public:
		rtcr::Color albedo;
	};
}

#endif