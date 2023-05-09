#include "GraphicsNode.h"

GraphicsNode::GraphicsNode()
{
}

GraphicsNode::GraphicsNode(MeshResource newMesh, TextureResource newTexture, ShaderObject newShader, Matrix4D newTransform)
{
	mesh = std::make_shared<MeshResource>(newMesh);
	texture = std::make_shared<TextureResource>(newTexture);
	shader = std::make_shared<ShaderObject>(newShader);
	transform = newTransform;
}

GraphicsNode::GraphicsNode(GraphicsNode& gn)
{
	mesh = gn.mesh;
	texture = gn.texture;
	shader = gn.shader;
	transform = gn.transform;

}


GraphicsNode::~GraphicsNode()
{
}

std::shared_ptr<MeshResource>& GraphicsNode::getMesh()
{
	return mesh;
}

std::shared_ptr<TextureResource>& GraphicsNode::getTexture()
{
	return texture;
}

std::shared_ptr<ShaderObject>& GraphicsNode::getShader()
{
	return shader;
}

void GraphicsNode::setMesh(MeshResource newMesh)
{
	mesh = std::make_shared<MeshResource>(newMesh);
}

void GraphicsNode::setTexture(TextureResource newTexture)
{
	texture = std::make_shared<TextureResource>(newTexture);
}

void GraphicsNode::setShader(ShaderObject newShader)
{
	shader = std::make_shared<ShaderObject>(newShader);
}

void GraphicsNode::setTransform(Vector4D newTransform)
{
	transform = transform.translation(newTransform);
}
void GraphicsNode::setTransform(Matrix4D newTransform)
{
	transform = newTransform;
}

Matrix4D& GraphicsNode::getTransform()
{
	return transform;
}

void GraphicsNode::bindGraphics()
{
	
	//ShaderObject shader("./resources/vertexshader.vs", "./resources/fragmentshader.fs");

	mesh.get()->genvertexarray();
	mesh.get()->genvertexbuffer();
	mesh.get()->genindexbuffer();
	mesh.get()->setattrib();

	stbi_set_flip_vertically_on_load(true);

	texture.get()->bindTex();
	texture.get()->setTexParam();
	texture.get()->texPictureData = stbi_load("./resources/container.jpg", &texture.get()->width, &texture.get()->height, &texture.get()->nChannels, 0);
	if (texture.get()->texPictureData) {
		texture.get()->loadTex(texture.get()->texPictureData);
		std::cout << "Hey you actually hit something" << "\n";
	}
	else {
		std::cout << stbi_failure_reason() << "\n";
		std::cout << "Nice shootin' Tex" << "\n";
	}
	stbi_image_free(texture.get()->texPictureData);
	shader.get()->use();

	glUniform1i(glGetUniformLocation(shader.get()->ID, "texture1"), 0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void GraphicsNode::draw(Camera cam, Matrix4D projection)
{	



	//std::cout << "MODEL------------" << "\n";
	//transform.print();
	//std::cout << "----------------" << "\n";

	//std::cout << "VIEW------------" << "\n";
	////view.print();

	//for (int i = 0; i < 4; ++i)
	//	for (int j = 0; j < 4; ++j)
	//	{
	//		std::cout << " " << cam.getView()[i][j];
	//		if (j == 3)
	//			std::cout << "\n" << "\n";
	//	}
	//std::cout << "--------" << "\n";

	//std::cout << "----------------" << "\n";

	//std::cout << "PROJECTION------------" << "\n";
	////projection.print();
	//std::cout << "----------------" << "\n";



	shader.get()->setMat4(std::string("model"), transform);
	shader.get()->setMat4(std::string("view"), cam.getView());
	shader.get()->setMat4(std::string("projection"), projection);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.get()->texID);


	glBindVertexArray(mesh.get()->vertexarray);
	glDrawArrays(GL_TRIANGLES, 0, 36);

}
