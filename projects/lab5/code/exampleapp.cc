//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2018 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "exampleapp.h"
#include <cstring>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "LightNode.h"



const GLchar* vs =
"#version 430\n"
"layout(location=0) in vec3 pos;\n"
"layout(location=1) in vec2 texCoord;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"out vec2 TexCoord;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	gl_Position = projection * view *  model * vec4(pos, 1.0);\n"
"   TexCoord = texCoord;\n"
"}\n";

const GLchar* ps =
"#version 430\n"
"out vec4 FragColor;\n"
"in vec4 color;\n"
"in vec2 TexCoord;"
"uniform sampler2D texture1;\n"
"uniform sampler2D texture2;\n"
"void main()\n"
"{\n"
"	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5);\n"
"}\n";

using namespace Display;
namespace Example
{

	//------------------------------------------------------------------------------
	/**
	*/
	ExampleApp::ExampleApp()
	{
		// empty
	}

	//------------------------------------------------------------------------------
	/**
	*/
	ExampleApp::~ExampleApp()
	{
		// empty
	}

	//------------------------------------------------------------------------------
	/**
	*/
	bool
		ExampleApp::Open()
	{
		App::Open();
		this->window = new Display::Window;
		window->SetKeyPressFunction([this](int32 asciikey, int32 argb, int32 status, int32 mod)
		{
			
		});

		

		GLfloat buf[] =
		{
			-0.5f,	-0.5f,	-1,			// pos 0
			1,		0,		0,		1,	// color 0
			0,		0.5f,	-1,			// pos 1
			0,		1,		0,		1,	// color 0
			0.5f,	-0.5f,	-1,			// pos 2
			0,		0,		1,		1	// color 0
		};
		if (this->window->Open())
		{
			// set clear color to gray
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			
		}
		return true;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		ExampleApp::Run()
	{
		Matrix4D projection = projection.perspective(75.0f, 800.0f / 600.0f, 0.1f, 100.0f);
		//glm::mat4 projection = glm::perspective(glm::radians(75.0f), (float)800 / (float)600, 0.1f, 100.0f);
		//Camera cam(Vector4D(0.0f, 0.0f, 3.0f), Vector4D(0.0f, 0.0f, 0.0f), Vector4D(0.0f, 0.0f, -1.0f), Vector4D(0.0f, 1.0f, 0.0f));
		cam.camPos = Vector4D(0.0f, 0.0f, 3.0f);
		cam.camTarget = Vector4D(0.0f, 0.0f, 0.0f);
		cam.camFront = Vector4D(0.0f, 0.0f, -1.0f);
		cam.camUp = Vector4D(0.0f, 1.0f, 0.0f);

		LightNode light;
		light.lightColor = Vector4D(1.0f, 1.0f, 1.0f);
		light.lightPos = Vector4D(-5.0f, -2.0f, 0.0f);
		light.intensity = 0.1;
		
		light.bindLighting();

		gn.setMesh(MeshResource());
		gn.setShader(ShaderObject("./resources/vertexshader.vs", "./resources/fragmentshader.fs"));
		gn.setTexture(TextureResource());
		gn.setTransform(Matrix4D());
		gn.loadObj("./resources/CoronaFixed.obj");

		gn2.setMesh(MeshResource());
		gn2.setShader(ShaderObject("./resources/vertexshader.vs", "./resources/fragmentshader.fs"));
		gn2.setTexture(TextureResource());
		gn2.setTransform(Matrix4D());
		gn2.loadObj("./resources/cube.obj");


		
		gn.bindGraphics("./resources/BotellaText.jpg");
		gn2.bindGraphics("./resources/container2.jpg");
		Matrix4D rot;
		gn.setTransform(gn.getTransform() * gn.getTransform().scale(Vector4D(0.05f, 0.05f, 0.05f)));
		gn.setTransform(gn.getTransform() * rot.rotz(90) * rot.rotx(130) * rot.roty(100));

		gn2.setTransform(gn2.getTransform().scale(Vector4D(0.5f, 0.5f, 0.5f)));
		gn2.setTransform(gn2.getTransform() * gn2.getTransform().translation(Vector4D(1.0f, 0.0f, 0.0f)));


		int width;
		int height;

		this->window->GetSize(width, height);
		std::cout << "width: " << width << " height: " << height << "\n";

		float yaw = -90;
		float pitch = 0;

		float lastX = 512.0f;
		float lastY = 384.0f;
		bool firstRotation = true;

		Vector4D lightPosition(1.2f, 1.0f, 2.0f);

		//render loop
		while (this->window->IsOpen())
		{
			//light.lightColor = Vector4D(1.0f, 1.0f, 1.0f);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			this->window->Update();
			currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;	
			lastFrame = currentFrame;

			/*light.intensity = (float)cos(glfwGetTime());
			std::cout << light.intensity << "\n";
			*/

			window->SetKeyPressFunction([this](int32 asciikey, int32 argb, int32 status, int32 mod)
			{
				std::cout << "asciikey: " << asciikey << " argb: " << argb << " status: " << status << " mod: " << mod << "\n";

				const float camSpeed = 3.0f * deltaTime;

				if (status == 1) {
					switch (asciikey) {
					case GLFW_KEY_W:
						cam.camPos = cam.camPos + cam.camFront * camSpeed;
						break;
					case GLFW_KEY_A:
						cam.camPos = cam.camPos - Vector4D::cross(cam.camFront, cam.camUp).norm() * camSpeed;
						break;
					case GLFW_KEY_S:
						cam.camPos = cam.camPos - cam.camFront * camSpeed;
						break;
					case GLFW_KEY_D:
						cam.camPos = cam.camPos + Vector4D::cross(cam.camFront, cam.camUp).norm() * camSpeed;
						break;

					}
					
				}
				else if (status == 2) {
					switch (asciikey) {
					case GLFW_KEY_W:
						cam.camPos = cam.camPos + cam.camFront * camSpeed;
						break;
					case GLFW_KEY_A:
						cam.camPos = cam.camPos - Vector4D::cross(cam.camFront, cam.camUp).norm() * camSpeed;
						break;
					case GLFW_KEY_S:
						cam.camPos = cam.camPos - cam.camFront * camSpeed;
						break;

					case GLFW_KEY_D:
						cam.camPos = cam.camPos + Vector4D::cross(cam.camFront, cam.camUp).norm() * camSpeed;
						break;
					}

				}

				if (asciikey == 256 && status == 1) {
					this->window->Close();
				}
			});
			

			window->SetMousePressFunction([this](int32 mousekey, int32 status, int32 keyc) {
				std::cout << "mousekey: " << mousekey << " status: " << status << " keyc: " << keyc << "\n";
				mousepress = mousekey;
				mousestatus = status;
				});

			window->SetMouseMoveFunction([&](float64 mousex, float64 mousey) {

				if (mousepress == 0 && mousestatus == 1) {


					if (firstRotation) {
						lastX = mousex;
						lastY = mousey;
						firstRotation = false;
					}


					float xoffset = mousex - lastX;
					float yoffset = lastY - mousey; 
					lastX = mousex;
					lastY = mousey;
					const float speed = 0.1f;
					xoffset *= speed;
					yoffset *= speed;

					yaw += xoffset;
					pitch += yoffset;
					

					if (pitch > 89.0f) {
						pitch = 89.0f;
					}
					if (pitch < -89.0f) {
						pitch = -89.0f;
					}

					Vector4D direction;
					float degrad = PI / 180;
					direction.x() = cos(yaw * degrad) * cos(pitch * degrad);
					direction.y() = sin(pitch * degrad);
					direction.z() = sin(yaw * degrad) * cos(pitch * degrad);

					cam.camFront = direction.norm();

				}
				
				});
			cam.setView();
			//gn.draw(cam, projection);
			//gn2.draw(cam, projection);
			light.render(cam, projection);

			///     _             _          __  __ 
			///    | |           | |        / _|/ _|
			///  __| | ___    ___| |_ _   _| |_| |_ 
			/// / _` |/ _ \  / __| __| | | |  _|  _|
			///| (_| | (_) | \__ \ |_| |_| | | | |  
			/// \__,_|\___/  |___/\__|\__,_|_| |_|  
			


			this->window->SwapBuffers();
		}
		gn.clearMemory();
		gn2.clearMemory();
		glfwTerminate();
	}
}// namespace Example