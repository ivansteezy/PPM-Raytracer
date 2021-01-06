#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <array>
#include <ostream>
#include <iostream>

#include "Foundation.h"

namespace rtcr
{
	template<typename T>
	class Vector3
	{
	public:
		Vector3() : e{ 0, 0, 0 } {}
		Vector3(T x, T y, T z) : e{ x, y, z } {}

		T GetX() const { return e[0]; }
		T GetY() const { return e[1]; }
		T GetZ() const { return e[2]; }

		T& operator[](size_t index) { return e[index]; }
		const T& operator[](size_t index) const { return e[index]; }

		Vector3 operator-() const { return Vector3(-e[0], -e[1], -e[2]); };

		Vector3& operator+=(const Vector3& v)
		{
			e[0] += v.e[0];
			e[1] += v.e[1];
			e[2] += v.e[2];
			return *this;
		}

		Vector3& operator*=(const T& m)
		{
			e[0] *= m;
			e[1] *= m;
			e[2] *= m;
			return *this;
		}

		Vector3& operator/=(const T& d)
		{
			return *this *= (1 / d);
		}

		T Length() const
		{
			return std::sqrt(LengthSquared());
		}

		T LengthSquared() const
		{
			return (e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]);
		}

		inline static Vector3 GetRandomVector()
		{
			return Vector3(GenRandomNumber(), GenRandomNumber(), GenRandomNumber());
		}

		inline static Vector3 GetRandomVector(double min, double max)
		{
			return Vector3(GenRandomNumber(min, max), GenRandomNumber(min, max), GenRandomNumber(min, max));
		}

		friend inline std::ostream& operator<<(std::ofstream& out, const Vector3& vec)
		{
			return out << vec.e[0] << ' ' << vec.e[1] << ' ' << vec.e[2];
		}

		friend inline Vector3 operator+(const Vector3& u, const Vector3& v)
		{
			return Vector3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
		}

		friend inline Vector3 operator-(const Vector3& u, const Vector3& v)
		{
			return Vector3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
		}

		friend inline Vector3 operator*(const Vector3& u, const Vector3& v)
		{
			return Vector3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
		}

		friend inline Vector3 operator*(T t, const Vector3& v)
		{
			return Vector3(t * v.e[0], t * v.e[1], t * v.e[2]);
		}

		friend inline Vector3 operator*(const Vector3& v, T t)
		{
			return t * v;
		}

		friend inline Vector3 operator/(Vector3 v, T t)
		{
			return (1 / t) * v;
		}

		static inline T DotProduct(const Vector3& u, const Vector3& v)
		{
			return u.e[0] * v.e[0] +
				   u.e[1] * v.e[1] +
				   u.e[2] * v.e[2];
		}

		static inline Vector3 CrossProduct(const Vector3& u, const Vector3& v)
		{
			return Vector3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
						   u.e[2] * v.e[0] - u.e[0] * v.e[2],
				           u.e[0] * v.e[1] - u.e[1] * v.e[0]);
		}

		static inline Vector3 UnitVector(Vector3 vec)
		{
			return (vec / vec.Length());
		}

		bool NearZero() const
		{
			// Return true if the vector is close to zero in all dimensions.
			const auto s = 1e-8;
			return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
		}

		static rtcr::Vector3<double> RandomPointInUnitSphere() //maybe static in vector3 class
		{
			while (true)
			{
				auto p = rtcr::Vector3<double>::GetRandomVector(-1, 1);
				if (p.LengthSquared() >= 1) continue;
				return p;
			}
		}

		static rtcr::Vector3<double> RandomUnitVector()
		{
			return rtcr::Vector3<double>::UnitVector(RandomPointInUnitSphere());
		}

		static rtcr::Vector3<double> Reflect(const rtcr::Vector3<double>& vec, const rtcr::Vector3<double>& n)
		{
			return vec - 2 * Vector3<double>::DotProduct(vec, n) * n;
		}

	public:
		std::array<T, 3> e;
	};


	using Point3 = Vector3<double>;
	using Color  = Vector3<double>;
}
#endif
