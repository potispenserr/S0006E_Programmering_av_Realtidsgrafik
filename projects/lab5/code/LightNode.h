#include "Vector4D.h"
#include "GraphicsNode.h"
class LightNode
{
public:
	LightNode();
	~LightNode();
	Vector4D position;
	Vector4D color;
	float intensity = 0;
	GraphicsNode lightCube;
	ShaderObject lightShader;


private:

};

