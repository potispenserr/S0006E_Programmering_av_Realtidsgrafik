#pragma once
#include "core/app.h"
#include "render/window.h"
#include "config.h"
class TextureResource {
public:

	TextureResource() {
		width = 0;
		height = 0;
		nChannels = 0;

	}

	~TextureResource() {
		glDeleteTextures(1, &texID);
	}

	float borderColor[4] = { 1.0f, 1.0f, 0.0f, 1.0f };

	void setTexParam();
	void bindTex();
	void loadTex(unsigned char* texData);


	int width;
	int height;
	int nChannels;

	unsigned int texID = 0;
	unsigned char* texPictureData = NULL;
	
};
