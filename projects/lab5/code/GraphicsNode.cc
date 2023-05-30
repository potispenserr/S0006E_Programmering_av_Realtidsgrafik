#include "GraphicsNode.h"
#include "stb_image.h"
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	glDrawArrays(GL_TRIANGLES, 0, mesh.get()->verticies.size());


}

void GraphicsNode::loadObj(std::string pathToFile)
{
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> texels;
	std::vector<int> vertIndicies;
	std::vector<int> normIndicies;
	std::vector<int> texIndicies;
	std::fstream file;
	file.open(pathToFile, std::ios::in); 
	if (file.is_open()) {   
		std::string line;
		int lineNumber = 1;

		while (std::getline(file, line)) { 
			std::cout << lineNumber << ": " << line << "\n";
			std::string lineToken = line.substr(0, 2);
			lineToken.erase(std::remove_if(lineToken.begin(), lineToken.end(), isspace), lineToken.end());
			std::cout << lineToken << "\n";
			if (lineToken == "v") {
				std::vector<size_t> lineSpaces;
				std::string vertexPosition;
				lineSpaces.push_back(line.find(" "));
				lineSpaces.push_back(line.find(" ", lineSpaces[0] + 1));
				lineSpaces.push_back(line.find(" ", lineSpaces[1] + 1));
				lineSpaces.push_back(line.find(" ", lineSpaces[2] + 1));
				std::cout << "first vertex position:" << line.substr(lineSpaces[0] + 1, lineSpaces[1] - 2) << "Z" << "\n";
				std::cout << "second vertex position:" << line.substr(lineSpaces[1] + 1, (lineSpaces[2]) - (lineSpaces[1] + 1)) << "Z" << "\n";
				std::cout << "third vertex position:" << line.substr(lineSpaces[2] + 1, line.size()) << "Z" << "\n";
				vertices.push_back(std::stof(line.substr(lineSpaces[0] + 1, lineSpaces[1] - 2)));
				vertices.push_back(std::stof(line.substr(lineSpaces[1] + 1, (lineSpaces[2]) - (lineSpaces[1] + 1))));
				vertices.push_back(std::stof(line.substr(lineSpaces[2] + 1, line.size())));

			}
			if (lineToken == "vn") {
				std::vector<size_t> lineSpaces;
				std::string vertexPosition;
				lineSpaces.push_back(line.find(" "));
				lineSpaces.push_back(line.find(" ", lineSpaces[0] + 1));
				lineSpaces.push_back(line.find(" ", lineSpaces[1] + 1));
				lineSpaces.push_back(line.find(" ", lineSpaces[2] + 1));
				/*std::cout << "first vertex position:" << line.substr(lineSpaces[0] + 1, (lineSpaces[1]) - (lineSpaces[0] + 2)) << "Z" << "\n";
				std::cout << "second vertex position:" << line.substr(lineSpaces[1] + 1, (lineSpaces[2]) - (lineSpaces[1] + 1)) << "Z" << "\n";
				std::cout << "third vertex position:" << line.substr(lineSpaces[2] + 1, line.size()) << "Z" << "\n";*/
				normals.push_back(std::stof(line.substr(lineSpaces[0] + 1, (lineSpaces[1]) - (lineSpaces[0] + 2))));
				normals.push_back(std::stof(line.substr(lineSpaces[1] + 1, (lineSpaces[2]) - (lineSpaces[1] + 1))));
				normals.push_back(std::stof(line.substr(lineSpaces[2] + 1, line.size())));
			}
			if (lineToken == "vt") {
				std::vector<size_t> lineSpaces;
				std::string vertexPosition;
				lineSpaces.push_back(line.find(" "));
				lineSpaces.push_back(line.find(" ", lineSpaces[0] + 1));
				lineSpaces.push_back(line.find(" ", lineSpaces[1] + 1));
				if (lineSpaces[2] == UINT64_MAX) {
					std::cout << "first vertex position:" << line.substr(lineSpaces[0] + 1, (lineSpaces[1]) - (lineSpaces[0] + 1)) << "Z" << "\n";
					std::cout << "second vertex position:" << line.substr(lineSpaces[1] + 1, line.size()) << "Z" << "\n";
					texels.push_back(std::stof(line.substr(lineSpaces[0] + 1, (lineSpaces[1]) - (lineSpaces[0] + 1))));
					texels.push_back(std::stof(line.substr(lineSpaces[1] + 1, line.size())));
					continue;
				}
				//why even have a third texel AAAHHH
				std::cout << "first vertex position:" << line.substr(lineSpaces[0] + 1, (lineSpaces[1]) - (lineSpaces[0] + 1)) << "Z" << "\n";
				std::cout << "second vertex position:" << line.substr(lineSpaces[1] + 1, (lineSpaces[2]) - (lineSpaces[1] + 1)) << "Z" << "\n";
				texels.push_back(stof(line.substr(lineSpaces[0] + 1, (lineSpaces[1]) - (lineSpaces[0] + 1))));
				texels.push_back(stof(line.substr(lineSpaces[1] + 1, (lineSpaces[2]) - (lineSpaces[1] + 1))));
				
			}
			if (lineToken == "f") {
				std::vector<size_t> lineSpaces;
				std::vector<size_t> slashPos;
				std::string vertexPosition;
				lineSpaces.push_back(line.find(" "));
				lineSpaces.push_back(line.find(" ", lineSpaces[0] + 1));
				lineSpaces.push_back(line.find(" ", lineSpaces[1] + 1));
				slashPos.push_back(line.find("/"));
				for (int i = 0; i < 5; i++) {
					slashPos.push_back(line.find("/", slashPos[i] + 1));
				}
				std::cout << "slashes found at:";
				for (int i = 0; i < 5; i++) {
					std::cout << " " << slashPos[i] << " ";
				}
				std::cout << "\n";
				std::cout << "first vertex: " << line.substr(lineSpaces[0] + 1, (slashPos[0]) - (lineSpaces[0] + 1)) << "\n";
				std::cout << "first tex: " << line.substr(slashPos[0] + 1, (slashPos[1]) - (slashPos[0] + 1)) << "\n";
				std::cout << "first norm: " << line.substr(slashPos[1] + 1, (lineSpaces[1]) - (slashPos[1] + 1)) << "\n";

				vertIndicies.push_back(std::stof(line.substr(lineSpaces[0] + 1, (slashPos[0]) - (lineSpaces[0] + 1))));
				texIndicies.push_back(std::stof(line.substr(slashPos[0] + 1, (slashPos[1]) - (slashPos[0] + 1))));
				normIndicies.push_back(std::stof(line.substr(slashPos[1] + 1, (lineSpaces[1]) - (slashPos[1] + 1))));
				

				std::cout << "second vertex: " << line.substr(lineSpaces[1] + 1, (slashPos[2]) - (lineSpaces[1] + 1)) << "\n";
				std::cout << "second tex: " << line.substr(slashPos[2] + 1, (slashPos[3]) - (slashPos[2] + 1)) << "\n";
				std::cout << "second norm: " << line.substr(slashPos[3] + 1, (lineSpaces[2]) - (slashPos[3] + 1)) << "\n";

				vertIndicies.push_back(std::stof(line.substr(lineSpaces[1] + 1, (slashPos[2]) - (lineSpaces[1] + 1))));
				texIndicies.push_back(std::stof(line.substr(slashPos[2] + 1, (slashPos[3]) - (slashPos[2] + 1))));
				normIndicies.push_back(std::stof(line.substr(slashPos[3] + 1, (lineSpaces[2]) - (slashPos[3] + 1))));

				std::cout << "third vertex: " << line.substr(lineSpaces[2] + 1, (slashPos[4]) - (lineSpaces[2] + 1)) << "\n";
				std::cout << "third tex: " << line.substr(slashPos[4] + 1, (slashPos[5]) - (slashPos[4] + 1)) << "\n";
				std::cout << "third norm: " << line.substr(slashPos[5] + 1, (line.size()) - (slashPos[5] + 1)) << "\n";

				vertIndicies.push_back(std::stof(line.substr(lineSpaces[2] + 1, (slashPos[4]) - (lineSpaces[2] + 1))));
				texIndicies.push_back(std::stof(line.substr(slashPos[4] + 1, (slashPos[5]) - (slashPos[4] + 1))));
				normIndicies.push_back(std::stof(line.substr(slashPos[5] + 1, (line.size()) - (slashPos[5] + 1))));


			}
			lineNumber++;
		}
		file.close();

		std::vector<float> finalVerts;
		std::vector<float> finalNorms;
		std::vector<float> finalTex;
		for (int i = 0; i < vertIndicies.size(); i++) {
			float vert = vertices[vertIndicies[i] - 1];
			float norm = normals[normIndicies[i] - 1];
			float tex = texels[texIndicies[i] - 1];

			finalVerts.push_back(vert);
			finalNorms.push_back(norm);
			finalTex.push_back(tex);
		}
		std::cout << "finished loading obj" << "\n";
		mesh.get()->setMesh(finalVerts, finalTex);
	}
}
