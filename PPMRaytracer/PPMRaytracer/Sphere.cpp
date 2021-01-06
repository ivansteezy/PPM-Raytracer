#include "Sphere.h"

rtcr::Sphere::Sphere()
{
}

rtcr::Sphere::Sphere(rtcr::Point3 center, double radius, MaterialPtr material) :
	m_center(center),
	m_radius(radius),
	m_material(material)
{
}

rtcr::Point3 rtcr::Sphere::GetCenter() const
{
	return m_center;
}

double rtcr::Sphere::GetRadius() const
{
	return m_radius;
}

bool rtcr::Sphere::Hit(const rtcr::Ray<double>& ray, double tMin, double tMax, HitRecord& rec) const
{

	auto oc = ray.GetOrigin() - m_center;
	auto a = ray.GetDirection().LengthSquared();
	auto halfb = rtcr::Vector3<double>::DotProduct(oc, ray.GetDirection());
	auto c = oc.LengthSquared() - (m_radius * m_radius);
	auto discriminant = (halfb * halfb) - (a * c);
	
	if (discriminant < 0) return false;
	auto squareRootDiscriminant = std::sqrt(discriminant);

	auto root = (-halfb - squareRootDiscriminant) / a;
	if (root < tMin || tMax < root)
	{
		root = (-halfb + squareRootDiscriminant) / a;
		if (root < tMin || tMax < root)
		{
			return false;
		}
	}

	rec.t = root;
	rec.p = ray.At(rec.t);
	auto outNormal = (rec.p - m_center) / m_radius;
	rec.SetFaceNormal(ray, outNormal);
	rec.materialPtr = m_material;
	return true;
}
