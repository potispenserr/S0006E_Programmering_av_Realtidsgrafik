#include "GraphicsNode.h"
#include "stb_image.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

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

void GraphicsNode::updateTransform(Matrix4D transformToAdd)
{
	transform = transform * transformToAdd;
}

Matrix4D& GraphicsNode::getTransform()
{
	return transform;
}

void GraphicsNode::bindGraphics(std::string pathToTextureFile)
{
	
	//ShaderObject shader("./resources/vertexshader.vs", "./resources/fragmentshader.fs");

	

	stbi_set_flip_vertically_on_load(true);

	texture.get()->bindTex();
	texture.get()->setTexParam();
	texture.get()->texPictureData = stbi_load(pathToTextureFile.c_str(), &texture.get()->width, &texture.get()->height, &texture.get()->nChannels, 0);
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
	shader.get()->use();
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
	std::vector<Vector4D> vertices;
	std::vector<Vector4D> normals;
	std::vector<Vector4D> texCoords;
	std::vector<int> vertIndicies;
	std::vector<int> normIndicies;
	std::vector<int> texIndicies;
	std::fstream file;
	file.open(pathToFile, std::ios::in); 
	if (file.is_open()) {   
		std::string line;
		int lineNumber = 1;

		while (std::getline(file, line)) { 
			std::string lineToken = line.substr(0, 2);
			lineToken.erase(std::remove_if(lineToken.begin(), lineToken.end(), isspace), lineToken.end());
			if (lineToken == "v") {

				std::vector<size_t> lineSpaces;
				std::string vertexPosition;
				lineSpaces.push_back(line.find(" "));
				lineSpaces.push_back(line.find(" ", lineSpaces[0] + 1));
				lineSpaces.push_back(line.find(" ", lineSpaces[1] + 1));
				lineSpaces.push_back(line.find(" ", lineSpaces[2] + 1));
				float x = std::stof(line.substr(lineSpaces[0] + 1, lineSpaces[1] - 2));
				float y = std::stof(line.substr(lineSpaces[1] + 1, (lineSpaces[2]) - (lineSpaces[1] + 1)));
				float z = std::stof(line.substr(lineSpaces[2] + 1, line.size()));
				vertices.push_back(Vector4D(x, y, z));

			}
			if (lineToken == "vn") {
				std::vector<size_t> lineSpaces;
				std::string vertexPosition;
				lineSpaces.push_back(line.find(" "));
				lineSpaces.push_back(line.find(" ", lineSpaces[0] + 1));
				lineSpaces.push_back(line.find(" ", lineSpaces[1] + 1));
				lineSpaces.push_back(line.find(" ", lineSpaces[2] + 1));
				float x = std::stof(line.substr(lineSpaces[0] + 1, lineSpaces[1] - 2));
				float y = std::stof(line.substr(lineSpaces[1] + 1, (lineSpaces[2]) - (lineSpaces[1] + 1)));
				float z = std::stof(line.substr(lineSpaces[2] + 1, line.size()));
				normals.push_back(Vector4D(x, y, z));
			}
			if (lineToken == "vt") {
				std::vector<size_t> lineSpaces;
				std::string vertexPosition;
				lineSpaces.push_back(line.find(" "));
				lineSpaces.push_back(line.find(" ", lineSpaces[0] + 1));
				lineSpaces.push_back(line.find(" ", lineSpaces[1] + 1));
				if (lineSpaces[2] == UINT64_MAX) {
					float x = std::stof(line.substr(lineSpaces[0] + 1, (lineSpaces[1]) - (lineSpaces[0] + 1)));
					float y = std::stof(line.substr(lineSpaces[1] + 1, line.size()));
					texCoords.push_back(Vector4D(x, y, 0.0f, 0.0f));
					continue;
				}
				//why even have a third texel AAAHHH
				float x = stof(line.substr(lineSpaces[0] + 1, (lineSpaces[1]) - (lineSpaces[0] + 1)));
				float y = stof(line.substr(lineSpaces[1] + 1, (lineSpaces[2]) - (lineSpaces[1] + 1)));
				texCoords.push_back(Vector4D(x, y, 0.0f, 0.0f));
				
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
				if (slashPos[4] == UINT64_MAX) {
					throw std::invalid_argument("Faces is not in the format of X/Y/Z");
				}
				
				vertIndicies.push_back(std::stof(line.substr(lineSpaces[0] + 1, (slashPos[0]) - (lineSpaces[0] + 1))));
				texIndicies.push_back(std::stof(line.substr(slashPos[0] + 1, (slashPos[1]) - (slashPos[0] + 1))));
				normIndicies.push_back(std::stof(line.substr(slashPos[1] + 1, (lineSpaces[1]) - (slashPos[1] + 1))));

				vertIndicies.push_back(std::stof(line.substr(lineSpaces[1] + 1, (slashPos[2]) - (lineSpaces[1] + 1))));
				texIndicies.push_back(std::stof(line.substr(slashPos[2] + 1, (slashPos[3]) - (slashPos[2] + 1))));
				normIndicies.push_back(std::stof(line.substr(slashPos[3] + 1, (lineSpaces[2]) - (slashPos[3] + 1))));

				vertIndicies.push_back(std::stof(line.substr(lineSpaces[2] + 1, (slashPos[4]) - (lineSpaces[2] + 1))));
				texIndicies.push_back(std::stof(line.substr(slashPos[4] + 1, (slashPos[5]) - (slashPos[4] + 1))));
				normIndicies.push_back(std::stof(line.substr(slashPos[5] + 1, (line.size()) - (slashPos[5] + 1))));


			}
			lineNumber++;
		}
		file.close();

		std::vector<Vertex> finalVerts;
		for (int i = 0; i < vertIndicies.size(); i++) {
			Vector4D vert = vertices[vertIndicies[i] - 1];
			Vector4D norm = normals[normIndicies[i] - 1];
			Vector4D tex = texCoords[texIndicies[i] - 1];

			finalVerts.push_back(Vertex(vert, norm, tex));
		}
		std::cout << "finished loading obj" << "\n";
		mesh.get()->setVerticies(finalVerts);

	}
	mesh.get()->genvertexarray();
	mesh.get()->genvertexbuffer();
	mesh.get()->setattrib();
}

void GraphicsNode::clearMemory()
{
	glDeleteVertexArrays(1, &mesh.get()->vertexarray);
	glDeleteBuffers(1, &mesh.get()->vertexbuffer);
	glDeleteBuffers(1, &mesh.get()->indexbuffer);
}
