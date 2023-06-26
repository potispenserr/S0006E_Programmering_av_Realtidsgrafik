#include "Vector4D.h"
#include "GraphicsNode.h"
class LightNode
{
public:
	LightNode();
	~LightNode();
	Vector4D position;
	Vector4D lightColor;
	//intensity ranges from 0 - 1
	float intensity = 0;
	GraphicsNode lightCube;
	ShaderObject lightShader;
	Matrix4D model;
	unsigned int lightVAO = -1;

	void bindLighting();

	void render(Camera cam, Matrix4D projection);



private:

};

