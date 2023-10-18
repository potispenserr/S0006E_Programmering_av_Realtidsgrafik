#pragma once
#include <vector>
#include "mesh.h"

struct Pixel
{
	float r = 255;
	float g = 255;
	float b = 255;

	Pixel(float red, float green, float blue) :
		r(red),
		g(green),
		b(blue)
	{}

};

class Rasterizer
{
public:
	Rasterizer();



	~Rasterizer();

	void setIndexBuffer();
	void setVertexBuffer();


	void setupFramebuffer(int width, int height);
	Pixel* getFramebufferData();
	std::vector<Pixel> getFramebuffer();
	int getFramebufferSize();

	void setVertexShader();
	void setFragmentShader();

	void setPixel(int index, float r, float g, float b);






private:
	std::vector<Pixel> framebuffer;
	std::vector<Vertex> vertexbuffer;
	std::vector<int> indexbuffer;

};
