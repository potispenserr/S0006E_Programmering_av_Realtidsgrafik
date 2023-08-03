#include "LightNode.h"
#include <stb_image.h>
LightNode::LightNode()
{
	lightCube.setMesh(MeshResource());
	lightCube.setShader(ShaderObject("./resources/LightCubeVS.vs", "./resources/LightCubeFS.fs"));
	lightCube.setTexture(TextureResource());
	lightCube.setTransform(Matrix4D());
	lightCube.loadObj("./resources/cube2.obj");
	//lightCube.bindGraphics("./resources/BotellaText.jpg");
	lightShader = ShaderObject("./resources/LightingVS.vs", "./resources/LightingFS.fs");
}

LightNode::~LightNode()
{
}


void LightNode::bindLighting()
{
	
	lightCube.updateTransform(lightCube.getTransform().translation(lightPos));
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, lightCube.getMesh().get()->vertexbuffer);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	
	//set normal attributes
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, meshNorm));
	//enable the normal attribute
	glEnableVertexAttribArray(1);

	
	//set texture attributes
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

	//enable the texture attribute
	glEnableVertexAttribArray(2);

	diffuseTex.loadTex("./resources/container2fixed.png");
	specularTex.loadTex("./resources/container2_specularfixed.png");
	

	lightShader.use();
	//lightShader.setVec3(std::string("objectColor"), Vector4D(1.0f, 0.5f, 0.31f));
	lightShader.setVec3(std::string("lightColor"), lightColor);
	lightShader.setFloat(std::string("ambientIntensity"), 0.1f);
	//glUniform1f(glGetUniformLocation(lightShader.ID, "ambientIntensity"), 0.1);

	lightShader.setInt(std::string("material.textureDiffuse"), 0);
	lightShader.setInt(std::string("material.textureSpecular"), 1);
	//lightShader.setVec3(std::string("material.specular"), Vector4D(0.5f, 0.5f, 0.5f));
	lightShader.setFloat(std::string("material.shininess"), 32.0f);

	lightShader.setVec3(std::string("light.ambient"), Vector4D(0.2f, 0.2f, 0.2f));
	lightShader.setVec3(std::string("light.diffuse"), Vector4D(0.5f, 0.5f, 0.5f));
	lightShader.setVec3(std::string("light.specular"), Vector4D(1.0f, 1.0f, 1.0f));


	
	model = model * model.scale(Vector4D(0.5f, 0.5f, 0.5f));

	model = model * model.translation(Vector4D(0.5f, 0.0f, -0.5f));

	model = model * Matrix4D::scale(Vector4D(1.5f, 1.5f, 1.5f));
	

	lightCube.updateTransform(lightCube.getTransform().scale(Vector4D(0.2f, 0.2f, 0.2f)));
	//lightCube.setTransform(Matrix4D::scale((Vector4D(0.2f, 0.2f, 0.2f))));
}

void LightNode::render(Camera cam, Matrix4D projection)
{
	Matrix4D translate;
	lightCube.setTransform(translate.translation(lightPos));
	lightCube.updateTransform(Matrix4D::scale(Vector4D(0.2f, 0.2f, 0.2f)));
	lightCube.draw(cam, projection);

	/*lightShader.use();
	lightColor = lightColor * intensity;
	lightShader.setVec3(std::string("objectColor"), Vector4D(1.0f, 0.5f, 0.31f));
	lightShader.setVec3(std::string("lightColor"), lightColor);*/
	
	//Vector4D camPos = cam.camPos * 1;


	lightShader.use();
	lightShader.setMat4(std::string("model"), model);
	lightShader.setMat4(std::string("view"), cam.getView());
	lightShader.setMat4(std::string("projection"), projection);

	lightShader.setVec3(std::string("light.pos"), this->lightPos);
	lightShader.setVec3(std::string("viewPosition"), cam.camPos);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseTex.texID);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularTex.texID);

	glBindVertexArray(lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, lightCube.getMesh().get()->verticies.size());
}


