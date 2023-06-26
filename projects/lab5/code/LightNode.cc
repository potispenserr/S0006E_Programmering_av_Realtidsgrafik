#include "LightNode.h"
LightNode::LightNode()
{
	lightCube.setMesh(MeshResource());
	lightCube.setShader(ShaderObject("./resources/vertexshader.vs", "./resources/LightCubeFS.fs"));
	lightCube.setTexture(TextureResource());
	lightCube.setTransform(Matrix4D());
	lightCube.loadObj("./resources/cube.obj");
	lightShader = ShaderObject("./resources/LightingVS.vs", "./resources/LightingFS.fs");
}

LightNode::~LightNode()
{
}

void LightNode::bindLighting()
{
	
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, lightCube.getMesh().get()->vertexbuffer);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	lightShader.use();
	lightColor = lightColor * intensity;
	lightShader.setVec3(std::string("objectColor"), Vector4D(1.0f, 0.5f, 0.31f));
	lightShader.setVec3(std::string("lightColor"), lightColor);
	
	model = model * model.scale(Vector4D(0.5f, 0.5f, 0.5f));

	lightCube.updateTransform(lightCube.getTransform().translation(position));
	lightCube.updateTransform(lightCube.getTransform().scale(Vector4D(0.2f, 0.2f, 0.2f)));
}

void LightNode::render(Camera cam, Matrix4D projection)
{
	lightCube.draw(cam, projection);

	/*lightShader.use();
	lightColor = lightColor * intensity;
	lightShader.setVec3(std::string("objectColor"), Vector4D(1.0f, 0.5f, 0.31f));
	lightShader.setVec3(std::string("lightColor"), lightColor);*/

	lightShader.use();
	lightShader.setMat4(std::string("model"), model);
	lightShader.setMat4(std::string("view"), cam.getView());
	lightShader.setMat4(std::string("projection"), projection);

	glBindVertexArray(lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, lightCube.getMesh().get()->verticies.size());
}
