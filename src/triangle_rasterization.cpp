#include "triangle_rasterization.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>


cg::TriangleRasterization::TriangleRasterization(unsigned short width, unsigned short height, std::string obj_file) : cg::Projections(width, height, obj_file)
{
}

cg::TriangleRasterization::~TriangleRasterization()
{
}

void cg::TriangleRasterization::DrawTriangle(cg::face face)
{
	float x_min = std::min(face.vertexes[0].x, std::min(face.vertexes[1].x, face.vertexes[2].x));
	float x_max = std::max(face.vertexes[0].x, std::max(face.vertexes[1].x, face.vertexes[2].x));
	float y_min = std::min(face.vertexes[0].y, std::min(face.vertexes[1].y, face.vertexes[2].y));
	float y_max = std::max(face.vertexes[0].y, std::max(face.vertexes[1].y, face.vertexes[2].y));

	bool ccw = true;
	float direction = ccw ? -1.f : 1.f;
	float area = direction * EdgeFunction(face.vertexes[0].xy(), face.vertexes[1].xy(), face.vertexes[2].xy());

	for (float x = x_min; x <= x_max; x++) {
		for (float y = y_min; y <= y_max; y++) {
			float2 point{ x, y };
			float e0 = direction * EdgeFunction(face.vertexes[0].xy(), face.vertexes[1].xy(), point);
			float e1 = direction * EdgeFunction(face.vertexes[1].xy(), face.vertexes[2].xy(), point);
			float e2 = direction * EdgeFunction(face.vertexes[2].xy(), face.vertexes[0].xy(), point);

			if (e0 >= 0 && e1 >= 0 && e2 >= 0) {
				float3 bary = { e0 / area, e1 / area, e2 / area };
				SetPixel(round(x), round(y), PixelShader(point, bary, face.primitive_id));
			}
		}
	}

	DrawLine(face.vertexes[0].x, face.vertexes[0].y, face.vertexes[1].x, face.vertexes[1].y, color(255, 0, 0));
	DrawLine(face.vertexes[1].x, face.vertexes[1].y, face.vertexes[2].x, face.vertexes[2].y, color(0, 255, 0));
	DrawLine(face.vertexes[2].x, face.vertexes[2].y, face.vertexes[0].x, face.vertexes[0].y, color(0, 0, 255));
}

void cg::TriangleRasterization::DrawScene()
{
	int id = 0;
	std::vector<cg::face> vs_faces;
	for (face face : parser->GetFaces())
	{
		face.primitive_id = id++;
		for (int i = 0; i < 3; i++) {
			face.vertexes[i] = VertexShader(face.vertexes[i]);
		}

		vs_faces.push_back(face);
	}

	std::sort(vs_faces.begin(), vs_faces.end(), [](cg::face face1, cg::face face2) {
		return face1.vertexes[2].z < face2.vertexes[2].z;
		});

	for (cg::face face : vs_faces) {
		Rasterizer(face);
	}
}

cg::color cg::TriangleRasterization::PixelShader(float2 coordinates, float3 bary, int id)
{
	float3 inter_color = bary * 255;
	return color(round(inter_color.x), round(inter_color.y), round(inter_color.z));
	switch (id % 7) {
	case 0: return color(200, 0, 0);
	case 1: return color(0, 200, 0);
	case 2: return color(0, 0, 200);
	case 3: return color(200, 200, 0);
	case 4: return color(200, 0, 200);
	case 5: return color(0, 200, 200);
	case 6: return color(200, 200, 200);
	} 
}

float cg::TriangleRasterization::EdgeFunction(float2 p1, float2 p2, float2 p)
{
	return (p.x - p1.x)* (p2.y - p1.y) - (p.y - p1.y) * (p2.x - p1.x);
}


