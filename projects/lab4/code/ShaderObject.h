#pragma once
#include "core/app.h"
#include "render/window.h"
#include "config.h"
#include "Matrix4D.h"
#include <fstream>
#include <sstream>
#include <iostream>

class ShaderObject {
public:
	ShaderObject(const char* vertexPath, const char* fragmentPath);

	~ShaderObject();

	void use();

	void setMat4(std::string& name, Matrix4D matrix);

	void setVec4(std::string& name, Vector4D vector);

	unsigned int ID = 0;

};