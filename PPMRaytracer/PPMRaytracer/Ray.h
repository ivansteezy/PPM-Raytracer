#ifndef RAY_H
#define RAY_H

#include "Vector3.h"

namespace rtcr
{
	template<typename T>
	class Ray
	{
	public:
		Ray() {}
		Ray(const rtcr::Point3& origin, const rtcr::Point3& direction) : m_Origin(origin), m_Direction(direction) {}

		Point3 GetOrigin() const { return m_Origin; }
		Point3 GetDirection() const { return m_Direction; }

		Point3 At(T t) const
		{
			return m_Origin + (t * m_Direction);
		}

	private:
		rtcr::Point3 m_Origin;
		rtcr::Point3 m_Direction;
	};
}

#endif
