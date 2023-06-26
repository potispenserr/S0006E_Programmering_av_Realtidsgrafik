#include "LightNode.h"
LightNode::LightNode()
{
	lightCube.setMesh(MeshResource());
	lightCube.setShader(ShaderObject("./resources/vertexshader.vs", "./resources/fragmentshader.fs"));
	lightCube.setTexture(TextureResource());
	lightCube.setTransform(Matrix4D());
	lightCube.loadObj("./resources/cube.obj");
}

LightNode::~LightNode()
{
}