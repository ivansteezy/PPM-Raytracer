#ifndef COLOR_H
#define COLOR_H

#include "Vector3.h"

namespace rtcr
{
	/*struct ColorPrinter
	{*/
		void WriteColor(std::ostream& os, rtcr::Color pixelColor, int samplesPerPixel)
		{
			auto r = pixelColor.GetX();
			auto g = pixelColor.GetY();
			auto b = pixelColor.GetZ();

			// Divide the color by the number of samples.
			auto scale = 1.0 / samplesPerPixel;
			r *= std::sqrt(scale * r);
			g *= std::sqrt(scale * g);
			b *= std::sqrt(scale * b);

			os  << static_cast<int>(256 * Clamp(r, 0.0, 0.999)) << ' '
				<< static_cast<int>(256 * Clamp(g, 0.0, 0.999)) << ' '
				<< static_cast<int>(256 * Clamp(b, 0.0, 0.999)) << '\n';
		}
	/*};*/
}

#endif // !COLOR_H
