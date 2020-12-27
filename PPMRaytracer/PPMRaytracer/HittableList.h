#ifndef HITTABLELIST_H
#define HITTABLELIST_H

#include <memory>
#include <vector>

#include "Hittable.h"

namespace rtcr
{
	class HittableList : public rtcr::Hittable
	{
	public:
		HittableList();
		HittableList(HittablePtr object);

	public:
		void Clear();
		void Add(HittablePtr object);

		virtual bool Hit(const rtcr::Ray<double>& ray, double tMin, double tMax, HitRecord& rec) const override;

	public:
		std::vector<HittablePtr> objects; //watchout for encapsulate this
	};
}

#endif
