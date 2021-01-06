#ifndef SPHERE_H
#define SPHERE_H

#include "Material.h"
#include "Vector3.h"
#include "Ray.h"

namespace rtcr
{
	class Sphere : public rtcr::Hittable
	{
	public:
		Sphere();
		Sphere(rtcr::Point3 center, double radius, MaterialPtr material);

	public:
		rtcr::Point3 GetCenter() const;
		double GetRadius() const;

		virtual bool Hit(const rtcr::Ray<double>& ray, double tMin, double tMax, HitRecord& rec) const override;

	private:
		rtcr::Point3 m_center;
		double m_radius;
		MaterialPtr m_material;
	};
}

#endif