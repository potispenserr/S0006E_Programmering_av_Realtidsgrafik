#pragma once
#include "core/app.h"
#include "render/window.h"
#include "config.h"
#include "mesh.h"
#include "TextureResource.h"
#include "ShaderObject.h"
#include "Matrix4D.h"
#include "stb_image.h"
#include "Camera.h"

class GraphicsNode
{
public:
	GraphicsNode();
	GraphicsNode(MeshResource newMesh, TextureResource newTexture, ShaderObject newShader, Matrix4D newTransform);
	GraphicsNode(GraphicsNode& gn);



	~GraphicsNode();

	std::shared_ptr<MeshResource>& getMesh();
	std::shared_ptr<TextureResource>& getTexture();
	std::shared_ptr<ShaderObject>& getShader();

	void setMesh(MeshResource newMesh);
	void setTexture(TextureResource newTexture);
	void setShader(ShaderObject newShader);

	void setTransform(Vector4D newTransform);

	void bindGraphics();

	void draw(Camera cam, Matrix4D projection);


	

private:
	std::shared_ptr<MeshResource> mesh;
	std::shared_ptr<TextureResource> texture;
	std::shared_ptr<ShaderObject> shader;
	Matrix4D transform;


};

