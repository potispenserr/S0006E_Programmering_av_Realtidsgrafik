#include "rasterizer.h"

Rasterizer::Rasterizer()
{
}

Rasterizer::~Rasterizer()
{
}

void Rasterizer::setIndexBuffer()
{
}

void Rasterizer::setVertexBuffer()
{
}


void Rasterizer::setupFramebuffer(int width, int height)
{
	for (size_t i = 0; i < width * height; i++)
	{
		Pixel p(0.698, 0.133, 0.133);
		framebuffer.push_back(p);
	}
}

Pixel* Rasterizer::getFramebufferData()
{
	return framebuffer.data();
}

std::vector<Pixel> Rasterizer::getFramebuffer()
{
	return framebuffer;
}

int Rasterizer::getFramebufferSize()
{
	return framebuffer.size();
}

void Rasterizer::setVertexShader()
{
}

void Rasterizer::setFragmentShader()
{
}

void Rasterizer::setPixel(int index, float r, float g, float b)
{
	framebuffer[index] = { r, g, b };
}
