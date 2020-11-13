#include "clear_rendertarget.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <stdexcept>
#include <algorithm>


cg::ClearRenderTarget::ClearRenderTarget(int32_t width, int32_t height):
    width(width),
    height(height)
{
    frame_buffer.reserve((size_t) width * height);
}

cg::ClearRenderTarget::~ClearRenderTarget()
{

}

void cg::ClearRenderTarget::Clear()
{   
    /*for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            SetPixel(x, y, color(0, 0, 0));
        }
    }*/
    frame_buffer.assign(width*height, color(0,0,0));
}

void cg::ClearRenderTarget::Save(std::string filename) const
{
    int result = stbi_write_png(filename.c_str(), width, height, 3, frame_buffer.data(), width * sizeof(color));
    if (result != 1) {
        throw std::runtime_error("Can not save image");
    }
}

void cg::ClearRenderTarget::SetPixel(int32_t x, int32_t y, color color)
{
    frame_buffer[y * width + x] = color;
}
