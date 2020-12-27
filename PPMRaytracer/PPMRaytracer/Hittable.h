#ifndef HITTABLE_H
#define HITTABLE_H
#define interface struct

#include <memory>

#include "Ray.h"

namespace rtcr
{
	struct HitRecord
	{
		rtcr::Point3 p {};
		rtcr::Vector3<double> normal {};
		double t { 0.0 };
		bool frontFace { false };

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
}

#endif