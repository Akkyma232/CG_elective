#pragma once


#include "projections.h"

namespace cg
{
	class TriangleRasterization : public Projections
	{
	public:
		TriangleRasterization(unsigned short width, unsigned short height, std::string obj_file);
		virtual ~TriangleRasterization();
		void DrawScene();

	protected:
		void DrawTriangle(face face);
		color PixelShader(float2 coordinates, float3 bary, int id);
		float EdgeFunction(float2 p1, float2 p2, float2 p);
	};
}
