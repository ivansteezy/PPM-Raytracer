#include "HittableList.h"

rtcr::HittableList::HittableList()
{
}

rtcr::HittableList::HittableList(HittablePtr object)
{
	Add(object);
}

void rtcr::HittableList::Clear()
{
	objects.clear();
}

void rtcr::HittableList::Add(HittablePtr object)
{
	objects.push_back(object);
}

bool rtcr::HittableList::Hit(const rtcr::Ray<double>& ray, double tMin, double tMax, HitRecord& rec) const
{
	HitRecord tempRec;
	bool hitAnything  = false;
	auto closestSoFar = tMax;
	
	for (const auto& object : objects)
	{
		if (object->Hit(ray, tMin, closestSoFar, tempRec))
		{
			hitAnything  = true;
			closestSoFar = tempRec.t;
			rec          = tempRec;
		}
	}
	return hitAnything;
}
