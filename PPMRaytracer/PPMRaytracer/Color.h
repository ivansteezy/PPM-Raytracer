#ifndef COLOR_H
#define COLOR_H

#include "Vector3.h"

namespace rtcr
{
	struct ColorPrinter
	{
		static void WriteColor(std::ostream& os, rtcr::Color pixelColor)
		{
			os  << static_cast<int>(255.99 * pixelColor.GetX()) << ' '
				<< static_cast<int>(255.99 * pixelColor.GetY()) << ' '
				<< static_cast<int>(255.99 * pixelColor.GetZ()) << '\n';
		}
	};
}

#endif // !COLOR_H
