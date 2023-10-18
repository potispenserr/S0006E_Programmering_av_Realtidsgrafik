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
			
			
		}
		return true;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		ExampleApp::Run()
	{
		

		ShaderObject lightShader = ShaderObject("./resources/LightingVS.vs", "./resources/LightingFS.fs");
		ShaderObject screenShader = ShaderObject("./resources/quadVS.vs", "./resources/quadFS.fs");

		Matrix4D projection = projection.perspective(75.0f, 800.0f / 600.0f, 0.1f, 100.0f);



		cam.camPos = Vector4D(0.0f, 0.0f, 6.0f);
		cam.camTarget = Vector4D(0.0f, 0.0f, 0.0f);
		cam.camFront = Vector4D(0.0f, 0.0f, -1.0f);
		cam.camUp = Vector4D(0.0f, 1.0f, 0.0f);

		Vector4D lightPosition(-14.2f, 1.0f, 2.0f);

		float quadBuffer[] = {
		// pos		   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
		};

		unsigned int quadVertexArray;
		unsigned int quadVertexBuffer;
		glGenVertexArrays(1, &quadVertexArray);
		glGenBuffers(1, &quadVertexBuffer);
		glBindVertexArray(quadVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, quadVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadBuffer), &quadBuffer, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

		/*GraphicsNode lightCube;

		lightCube.setMesh(MeshResource());
		lightCube.setShader(ShaderObject("./resources/LightCubeVS.vs", "./resources/LightCubeFS.fs"));
		lightCube.setTexture(TextureResource());
		lightCube.setTransform(Matrix4D());
		lightCube.loadObj("./resources/cube2.obj");
		lightCube.bindGraphics("./resources/container2fixed.png");

		gn.setMesh(MeshResource());
		gn.setShader(lightShader);
		gn.setTexture(TextureResource());
		gn.setTransform(Matrix4D());
		gn.loadObj("./resources/cube2.obj");
		gn.bindGraphics("./resources/container2fixed.png");


		LightNode light = LightNode(lightShader);
		light.lightColor = Vector4D(1.0f, 1.0f, 1.0f);
		light.lightPos = lightPosition;
		light.intensity = 0.1;

		light.setupLighting();*/

		screenShader.use();
		screenShader.setInt(std::string("screenTex"), 0);


		unsigned int framebufferTest;
		glGenFramebuffers(1, &framebufferTest);
		glBindFramebuffer(GL_FRAMEBUFFER, framebufferTest);
		//int width;
		int height;

		this->window->GetSize(width, height);
		std::cout << "width: " << width << " height: " << height << "\n";

		raster.setupFramebuffer(width, height);

		unsigned int rasterTexture;
		glGenTextures(1, &rasterTexture);
		glBindTexture(GL_TEXTURE_2D, rasterTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, raster.getFramebufferData());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, rasterTexture, 0);

		/*unsigned int texColorBuffer;
		glGenTextures(1, &texColorBuffer);
		glBindTexture(GL_TEXTURE_2D, texColorBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);*/

		unsigned int renderBuffer;
		glGenRenderbuffers(1, &renderBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "FRAMEBUFFER ERROR: Fool, the framebuffer is not complete!" << std::endl;
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);

		

		float yaw = -90;
		float pitch = 0;

		float lastX = 512.0f;
		float lastY = 384.0f;
		bool firstRotation = true;

		

		//render loop
		while (this->window->IsOpen())
		{
			//light.lightColor = Vector4D(1.0f, 1.0f, 1.0f);
			glBindFramebuffer(GL_FRAMEBUFFER, framebufferTest);
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);


			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			this->window->Update();
			currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;	
			lastFrame = currentFrame;
			
			/*light.intensity = (float)cos(glfwGetTime());
			std::cout << light.intensity << "\n";*/
			
			

			//std::cout << "Lightpos X:" << light.lightPos.x() << " Y:" << light.lightPos.y() << " Z:" << light.lightPos.z() << "\n";

			window->SetKeyPressFunction([this](int32 asciikey, int32 argb, int32 status, int32 mod)
			{
					
			//	//std::cout << "asciikey: " << asciikey << " argb: " << argb << " status: " << status << " mod: " << mod << "\n";

			//	const float camSpeed = 5.0f * deltaTime;

				if (status == 1) {
					switch (asciikey) {
					case GLFW_KEY_R:
						for (int i = 0; i < raster.getFramebufferSize(); i++) {
							raster.setPixel(i, 0.486, 0.988, 0.000);
							/*std::cout << "setting shit to green" << "\n";
							std::cout << raster.getFramebuffer()[i].r << "\n";
							std::cout << raster.getFramebuffer()[i].g << "\n";
							std::cout << raster.getFramebuffer()[i].b << "\n";*/
						}
						break;
			//		case GLFW_KEY_W:
			//			cam.camPos = cam.camPos + cam.camFront * camSpeed;
			//			break;
			//		case GLFW_KEY_A:
			//			cam.camPos = cam.camPos - Vector4D::cross(cam.camFront, cam.camUp).norm() * camSpeed;
			//			break;
			//		case GLFW_KEY_S:
			//			cam.camPos = cam.camPos - cam.camFront * camSpeed;
			//			break;
			//		case GLFW_KEY_D:
			//			cam.camPos = cam.camPos + Vector4D::cross(cam.camFront, cam.camUp).norm() * camSpeed;
			//			break;
			//		case GLFW_KEY_J:
			//			light.lightPos = light.lightPos + Vector4D(0.5f, 0.0f, 0.0f);
			//			break;
			//		case GLFW_KEY_K:
			//			light.lightPos = light.lightPos + Vector4D(0.0f, 0.0f, 0.5f);
			//			break;
			//		case GLFW_KEY_L:
			//			light.lightPos = light.lightPos + Vector4D(-0.5f, 0.0f, 0.0f);
			//			break;
			//		case GLFW_KEY_I:
			//			light.lightPos = light.lightPos + Vector4D(0.0f, 0.0f, -0.5f);
			//			break;
			//		case GLFW_KEY_U:
			//			light.lightPos = light.lightPos + Vector4D(0.0f, -0.5f, 0.0f);
			//			break;
			//		case GLFW_KEY_O:
			//			light.lightPos = light.lightPos + Vector4D(0.0f, 0.5f, 0.0f);
			//			break;

			//		case GLFW_KEY_Q:
			//			cam.camPos = cam.camPos + Vector4D(0.0f, 1.0f, 0.0f) * camSpeed;
			//			break;
			//		case GLFW_KEY_E:
			//			cam.camPos = cam.camPos + Vector4D(0.0f, -1.0f, 0.0f) * camSpeed;
			//			break;

					}


			}
				else if (status == 2) {
					switch (asciikey) {
					case GLFW_KEY_F:
						for (int i = 0; i < 10; i++) {
							raster.setPixel(colorIndex, 0.486, 0.988, 0.000);
							raster.setPixel(colorIndex + width, 0.486, 0.988, 0.000);
							raster.setPixel(colorIndex + width * 2, 0.486, 0.988, 0.000);
							raster.setPixel(colorIndex + width * 3, 0.486, 0.988, 0.000);
							raster.setPixel(colorIndex + width * 4, 0.486, 0.988, 0.000);
							colorIndex++;
							if (columnCounter == width) {
								columnCounter = 0;
								row++;
								colorIndex = width * (row * 2);
							}
							else {
								columnCounter++;

							}

						}
						
						break;

			//		case GLFW_KEY_W:
			//			cam.camPos = cam.camPos + cam.camFront * camSpeed;
			//			break;
			//		case GLFW_KEY_A:
			//			cam.camPos = cam.camPos - Vector4D::cross(cam.camFront, cam.camUp).norm() * camSpeed;
			//			break;
			//		case GLFW_KEY_S:
			//			cam.camPos = cam.camPos - cam.camFront * camSpeed;
			//			break;

			//		case GLFW_KEY_D:
			//			cam.camPos = cam.camPos + Vector4D::cross(cam.camFront, cam.camUp).norm() * camSpeed;
			//			break;
			//		case GLFW_KEY_J:
			//			light.lightPos = light.lightPos + Vector4D(0.5f, 0.0f, 0.0f);
			//			break;
			//		case GLFW_KEY_K:
			//			light.lightPos = light.lightPos + Vector4D(0.0f, 0.0f, 0.5f);
			//			break;
			//		case GLFW_KEY_L:
			//			light.lightPos = light.lightPos + Vector4D(-0.5f, 0.0f, 0.0f);
			//			break;
			//		case GLFW_KEY_I:
			//			light.lightPos = light.lightPos + Vector4D(0.0f, 0.0f, -0.5f);
			//			break;
			//		case GLFW_KEY_U:
			//			light.lightPos = light.lightPos + Vector4D(0.0f, -0.5f, 0.0f);
			//			break;
			//		case GLFW_KEY_O:
			//			light.lightPos = light.lightPos + Vector4D(0.0f, 0.5f, 0.0f);
			//			break;

			//		case GLFW_KEY_Q:
			//			cam.camPos = cam.camPos + Vector4D(0.0f, 1.0f, 0.0f) * camSpeed;
			//			break;
			//		case GLFW_KEY_E:
			//			cam.camPos = cam.camPos + Vector4D(0.0f, -1.0f, 0.0f) * camSpeed;
			//			break;
			//		
					}


				}

			if (asciikey == 256 && status == 1) {
					this->window->Close();
				}
			});
			//

			//window->SetMousePressFunction([this](int32 mousekey, int32 status, int32 keyc) {
			//	std::cout << "mousekey: " << mousekey << " status: " << status << " keyc: " << keyc << "\n";
			//	mousepress = mousekey;
			//	mousestatus = status;
			//	});

			//window->SetMouseMoveFunction([&](float64 mousex, float64 mousey) {

			//	if (mousepress == 0 && mousestatus == 1) {


			//		if (firstRotation) {
			//			lastX = mousex;
			//			lastY = mousey;
			//			firstRotation = false;
			//		}


			//		float xoffset = mousex - lastX;
			//		float yoffset = lastY - mousey; 
			//		lastX = mousex;
			//		lastY = mousey;
			//		const float speed = 0.1f;
			//		xoffset *= speed;
			//		yoffset *= speed;

			//		yaw += xoffset;
			//		pitch += yoffset;
			//		

			//		if (pitch > 89.0f) {
			//			pitch = 89.0f;
			//		}
			//		if (pitch < -89.0f) {
			//			pitch = -89.0f;
			//		}

			//		Vector4D direction;
			//		float degrad = PI / 180;
			//		direction.x() = cos(yaw * degrad) * cos(pitch * degrad);
			//		direction.y() = sin(pitch * degrad);
			//		direction.z() = sin(yaw * degrad) * cos(pitch * degrad);

			//		cam.camFront = direction.norm();

			//	}
			//	
			//	});
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			cam.setView();
			//light.updateLighting(cam, projection, lightCube);
			//gn.draw(cam, projection, light.lightPos);
			//lightCube.draw(cam, projection, light.lightPos);
			glBindTexture(GL_TEXTURE_2D, rasterTexture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, raster.getFramebufferData());

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glDisable(GL_DEPTH_TEST);
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			screenShader.use();
			glBindVertexArray(quadVertexArray);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, rasterTexture);
			glDrawArrays(GL_TRIANGLES, 0, 6);


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
		glDeleteVertexArrays(1, &quadVertexArray);
		glDeleteBuffers(1, &quadVertexBuffer);
		glDeleteRenderbuffers(1, &renderBuffer);
		glDeleteFramebuffers(1, &framebufferTest);

		glfwTerminate();
	}
}// namespace Example