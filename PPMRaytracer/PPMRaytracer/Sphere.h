#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"
#include "Vector3.h"

namespace rtcr
{
	class Sphere : public rtcr::Hittable
	{
	public:
		Sphere();
		Sphere(rtcr::Point3 center, double radius);

	public:
		rtcr::Point3 GetCenter() const;
		double GetRadius() const;

		virtual bool Hit(const rtcr::Ray<double>& ray, double tMin, double tMax, HitRecord& rec) const override;

	private:
		rtcr::Point3 m_center;
		double m_radius;
	};
}

#endif