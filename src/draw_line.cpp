#include "draw_line.h"


#define _USE_MATH_DEFINES
#include <math.h>

#include <algorithm>


cg::LineDrawing::LineDrawing(int32_t width, int32_t height): cg::ClearRenderTarget(width, height)
{
    
}

cg::LineDrawing::~LineDrawing()
{
    
}

void cg::LineDrawing::DrawLine(int32_t x_begin, int32_t y_begin, int32_t x_end, int32_t y_end, color color)
{
	if (abs(y_end - y_begin) < abs(x_end - x_begin)) {
		double slope = (double) (y_end - y_begin) / (x_end - x_begin);
		for (int32_t x = x_begin; x < x_end; x++) {
			int32_t y = y_begin + slope * (x - x_begin);
			SetPixel(x, y, color);
		}
		for (int32_t x = x_begin; x > x_end; x--) {
			int32_t y = y_begin + slope * (x - x_begin);
			SetPixel(x, y, color);
		}
	}
	else {
		double slope = (double) (x_end - x_begin) / (y_end - y_begin);
		for (int32_t y = y_begin; y < y_end; y++) {
			int32_t x = x_begin + slope * (y - y_begin);
			SetPixel(x, y, color);
		}
		for (int32_t y = y_begin; y > y_end; y--) {
			int32_t x = x_begin + slope * (y - y_begin);
			SetPixel(x, y, color);
		}
	}
}

void cg::LineDrawing::DrawScene()
{
	int32_t x_center = width / 2;
	int32_t y_center = height / 2;
	int32_t radius = std::min(x_center, y_center) - 1;
	for (double angle = 0.0; angle < 360.; angle += 5.0)
	{
		DrawLine(x_center, y_center, x_center + radius * cos(angle * M_PI / 180), y_center + radius * sin(angle * M_PI / 180),
            color(static_cast<uint8_t>(255 * sin(angle * M_PI / 180)), static_cast<uint8_t>(255 * cos(angle * M_PI / 180)), 255));
	}

}

