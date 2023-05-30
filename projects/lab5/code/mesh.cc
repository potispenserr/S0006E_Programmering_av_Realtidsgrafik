#include "mesh.h"
#include "config.h"

/// generate vertex buffer object
void MeshResource::genvertexbuffer() {
	//generate buffer id
	glGenBuffers(1, &vertexbuffer);

	//bind buffer to id
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	// copy vertex array to vertex buffer object
	glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(float), &verticies[0], GL_STATIC_DRAW);

	//now with separate texture buffer
	glGenBuffers(1, &textureBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);

	glBufferData(GL_ARRAY_BUFFER, texels.size() * sizeof(float), &texels[0], GL_STATIC_DRAW);
}

/// set attributes
void MeshResource::setattrib(){
	//enable the vertex attribute
	glEnableVertexAttribArray(0);
	//set vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);

	//set color attribute
	/*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//enable color attribute
	glEnableVertexAttribArray(1);*/

	//enable the texture attribute
	glEnableVertexAttribArray(1);
	//set texture attributes
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
}

/// generate vertex array object
void MeshResource::genvertexarray() {

	//generate vertex array object id
	glGenVertexArrays(1, &vertexarray);

	//bind vertex array object
	glBindVertexArray(vertexarray);
}

/// generate index buffer
void MeshResource::genindexbuffer() {
	//generate index buffer id
	glGenBuffers(1, &indexbuffer);
	//bind index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);
}

void MeshResource::setMesh(std::vector<float> verticies, std::vector<float> texels)
{
	this->verticies = verticies;
	this->texels = texels;
}


