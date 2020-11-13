#pragma once


#include "clear_rendertarget.h"

namespace cg
{

	class LineDrawing : public ClearRenderTarget
	{
	public:
		LineDrawing(int32_t width, int32_t height);
		virtual ~LineDrawing();

		void DrawLine(int32_t x_begin, int32_t y_begin, int32_t x_end, int32_t y_end, color color);

		void DrawScene();

	};

}
