#pragma once

#include <string>
#include <vector>

namespace cg
{

	struct color
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;

		color()
		{
			r = 0;
			g = 0;
			b = 0;
		}

		color(uint8_t in_r, uint8_t in_g, uint8_t in_b)
		{
			r = in_r;
			g = in_g;
			b = in_b;
		}
	};


	class ClearRenderTarget
	{
	public:
		ClearRenderTarget(int32_t width, int32_t height);
		virtual ~ClearRenderTarget();

		void Clear();
		void Save(std::string filename) const;

	protected:
		void SetPixel(int32_t x, int32_t y, color color);

		int32_t height;
		int32_t width;

		std::vector<color> frame_buffer;
	};


}

