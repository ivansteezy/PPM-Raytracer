#ifndef HITTABLE_H
#define HITTABLE_H
#define interface struct

#include "Ray.h"

namespace rtcr
{
	struct HitRecord
	{
		rtcr::Point3 p;
		rtcr::Vector3<double> normal;
		double t;
	};

	interface Hittable
	{
		virtual bool Hit(const rtcr::Ray<double>& ray, double tMin, double tMax, HitRecord& rec) const = 0;
	};
}

#endif