#ifndef CAMERA_H
#define CAMERA_H

#include "Foundation.h"

namespace rtcr
{
	class Camera
	{
	public:
		Camera()
		{
			auto aspectRatio    = 16.0 / 9.0;
			auto viewportHeight = 2.0;
			auto viewportWidth  = aspectRatio * viewportHeight;
			auto focalLength    = 1.0;

			m_origin            = rtcr::Point3(0, 0, 0);
			m_horizontal        = rtcr::Vector3<double>(viewportWidth, 0.0, 0.0);
			m_vertical          = rtcr::Vector3(0.0, viewportHeight, 0.0);
			m_lowerLeftCorner   = m_origin - (m_horizontal / 2) - (m_vertical / 2) - rtcr::Vector3<double>(0, 0, focalLength);
		}

		rtcr::Ray<double> GetRay(double u, double v) const
		{
			return rtcr::Ray<double>(m_origin, m_lowerLeftCorner + u * m_horizontal + v * m_vertical - m_origin);
		}

	private:
		rtcr::Point3		  m_origin;
		rtcr::Point3		  m_lowerLeftCorner;
		rtcr::Vector3<double> m_horizontal;
		rtcr::Vector3<double> m_vertical;
	};
};

#endif
