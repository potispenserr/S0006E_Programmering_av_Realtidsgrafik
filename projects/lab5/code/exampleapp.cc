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
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			
	
			/*
			// setup vertex shader
			this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
			GLint length = static_cast<GLint>(std::strlen(vs));
			glShaderSource(this->vertexShader, 1, &vs, &length);
			glCompileShader(this->vertexShader);

			// get error log
			GLint shaderLogSize;
			glGetShaderiv(this->vertexShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
			if (shaderLogSize > 0)
			{
				GLchar* buf = new GLchar[shaderLogSize];
				glGetShaderInfoLog(this->vertexShader, shaderLogSize, NULL, buf);
				printf("[SHADER COMPILE ERROR]: %s", buf);
				delete[] buf;
			}

			// setup pixel shader
			this->pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
			length = static_cast<GLint>(std::strlen(ps));
			glShaderSource(this->pixelShader, 1, &ps, &length);
			glCompileShader(this->pixelShader);

			// get error log
			shaderLogSize;
			glGetShaderiv(this->pixelShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
			if (shaderLogSize > 0)
			{
				GLchar* buf = new GLchar[shaderLogSize];
				glGetShaderInfoLog(this->pixelShader, shaderLogSize, NULL, buf);
				printf("[SHADER COMPILE ERROR]: %s", buf);
				delete[] buf;
			}

			// create a program object
			this->program = glCreateProgram();
			glAttachShader(this->program, this->vertexShader);
			glAttachShader(this->program, this->pixelShader);
			glLinkProgram(this->program);
			glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &shaderLogSize);
			if (shaderLogSize > 0)
			{
				GLchar* buf = new GLchar[shaderLogSize];
				glGetProgramInfoLog(this->program, shaderLogSize, NULL, buf);
				printf("[PROGRAM LINK ERROR]: %s", buf);
				delete[] buf;
			}

			//// setup vbo
			
			//glGenBuffers(1, &this->triangle);
			//glBindBuffer(GL_ARRAY_BUFFER, this->triangle);
			//glBufferData(GL_ARRAY_BUFFER, sizeof(buf), buf, GL_STATIC_DRAW);
			//glBindBuffer(GL_ARRAY_BUFFER, 0);
			return true;*/
		}
		return true;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		ExampleApp::Run()
	{
		//ShaderObject shader("./resources/vertexshader.vs", "./resources/fragmentshader.fs");
		
		/*mesh.genvertexarray();
		mesh.genvertexbuffer();
		mesh.genindexbuffer();
		mesh.setattrib();

		stbi_set_flip_vertically_on_load(true);
		
		tex.bindTex();
		tex.setTexParam();
		tex.texPictureData = stbi_load("./resources/container.jpg", &tex.width, &tex.height, &tex.nChannels, 0);
		if (tex.texPictureData) {
			tex.loadTex(tex.texPictureData);
			std::cout << "Hey you actually hit something" << "\n";
		}
		else {
			std::cout << stbi_failure_reason() << "\n";
			std::cout << "Nice shootin' Tex" << "\n";
		}
		stbi_image_free(tex.texPictureData);*/

		/*unsigned int texture2;
		int width, height, nrChannels;

		glGenTextures(1, &texture2);
		glBindTexture(GL_TEXTURE_2D, texture2);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load image, create texture and generate mipmaps
		unsigned char* data = stbi_load("./resources/face.png", &width, &height, &nrChannels, 0);
		if (data)
		{
			// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			std::cout << "maybe awesome?" << "\n";
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);*/

		/*tex2.bindTex();
		tex2.setTexParam();
		tex2.texPictureData = stbi_load("./resources/face.png", &tex2.width, &tex2.height, &tex2.nChannels, 0);
		if (tex2.texPictureData) {
			tex2.loadTex(tex2.texPictureData);
			std::cout << "Hey you actually hit something2" << "\n";
		}
		else {
			std::cout << stbi_failure_reason() << "\n";
			std::cout << "Nice shootin' Tex2" << "\n";
		}
		stbi_image_free(tex2.texPictureData);

		std::cout << tex.texID << "\n";
		std::cout << tex2.texID << "\n";*/
		
		//glUseProgram(this->program);
		//shader.use();

		/*glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 0);



		glUniform1i(glGetUniformLocation(shader.ID, "texture2"), 1);*/
		Matrix4D projection = projection.perspective(75.0f, 800.0f / 600.0f, 0.1f, 100.0f);
		//glm::mat4 projection = glm::perspective(glm::radians(75.0f), (float)800 / (float)600, 0.1f, 100.0f);
		//Camera cam(Vector4D(0.0f, 0.0f, 3.0f), Vector4D(0.0f, 0.0f, 0.0f), Vector4D(0.0f, 0.0f, -1.0f), Vector4D(0.0f, 1.0f, 0.0f));
		cam.camPos = Vector4D(0.0f, 0.0f, 3.0f);
		cam.camTarget = Vector4D(0.0f, 0.0f, 0.0f);
		cam.camFront = Vector4D(0.0f, 0.0f, -1.0f);
		cam.camUp = Vector4D(0.0f, 1.0f, 0.0f);

		gn.setMesh(MeshResource());
		gn.setShader(ShaderObject("./resources/vertexshader.vs", "./resources/fragmentshader.fs"));
		gn.setTexture(TextureResource());
		gn.setTransform(Matrix4D());
		gn.loadObj("./resources/CoronaFixed.obj");


		/*gn2.setMesh(MeshResource());
		gn2.setShader(ShaderObject("./resources/vertexshader.vs", "./resources/fragmentshader.fs"));
		gn2.setTexture(TextureResource());
		gn2.setTransform(Matrix4D());*/
		
		//gn2.setTransform(Vector4D(-1.3f, 1.0f, -1.5f));
		gn.bindGraphics();
		//gn2.bindGraphics();
		Matrix4D rot;
		gn.setTransform(gn.getTransform() * gn.getTransform().scale(Vector4D(0.05f, 0.05f, 0.05f)));
		gn.setTransform(gn.getTransform() * rot.rotz(90) * rot.rotx(130) * rot.roty(100));

		//glEnable(GL_DEPTH_TEST);
		//glDepthFunc(GL_LESS);

		int width;
		int height;

		this->window->GetSize(width, height);
		std::cout << "width: " << width << " height: " << height << "\n";

		float yaw = -90;
		float pitch = 0;

		float lastX = 512.0f;
		float lastY = 384.0f;
		bool firstRotation = true;

		//render loop
		while (this->window->IsOpen())
		{

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			this->window->Update();
			currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;	
			lastFrame = currentFrame;

			

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

			
				
				/*if (asciikey == GLFW_KEY_W && status == 1 || status == 2) {
					std::cout << "tering" << "\n";
					cam.camPos = cam.camPos + cam.camFront * camSpeed;
				}

				else if (asciikey == GLFW_KEY_S && status == 1 || status == 2) {
					std::cout << "kanker" << "\n";
					cam.camPos = cam.camPos - cam.camFront * camSpeed;
				}*/

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

					//std::cout << "mousex: " << mousex << " mousey: " << mousey << "\n";

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
			gn.draw(cam, projection);
			//gn2.draw(cam, projection);
			//std::cout << "x: " << cam.camFront.x() << "y: " << cam.camFront.y() << "z: " << cam.camFront.z() << "\n";
			//std::cout << "pitch: " << pitch << " yaw: " << yaw << "\n";


			///     _             _          __  __ 
			///    | |           | |        / _|/ _|
			///  __| | ___    ___| |_ _   _| |_| |_ 
			/// / _` |/ _ \  / __| __| | | |  _|  _|
			///| (_| | (_) | \__ \ |_| |_| | | | |  
			/// \__,_|\___/  |___/\__|\__,_|_| |_|  
			

			//glBindVertexArray(mesh.vertexarray);
			//mesh.genvertexarray();
			//glActiveTexture(GL_TEXTURE0);
			//glBindTexture(GL_TEXTURE_2D, tex.texID
		
			//Matrix4D model;
			////glm::mat4 model = glm::mat4(1.0f);
			//

			//

			/*float radius = 10;

			float camX = (float)(cos(glfwGetTime()) * radius);
			float camZ = (float)(sin(glfwGetTime()) * radius);*/
			//std::cout << camZ << "\n";


			//Matrix4D view = view.lookat(Vector4D(camX, 0.0f, camZ), Vector4D(0.0f, 0.0f, 0.0f), Vector4D(0.0f, 1.0f, 0.0f));
			//cam.setPosition(Vector4D(camX, 0.0f, camZ));
			
			//glm::mat4 view = glm::mat4(1.0f);
			//view = glm::lookAt(glm::vec3(0.0f, camX, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

			//unsigned int modelLoc = glGetUniformLocation(shader.ID, "model");
			//unsigned int viewLoc = glGetUniformLocation(shader.ID, "view");
			//unsigned int projectionLoc = glGetUniformLocation(shader.ID, "projection");



			//std::cout << "MODEL------------" << "\n";
			////model.print();
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


			//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
			//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &cam.getView()[0][0]);
			//glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);
			//glActiveTexture(GL_TEXTURE0);
			//glBindTexture(GL_TEXTURE_2D, tex.texID);
			//glActiveTexture(GL_TEXTURE1);
			//glBindTexture(GL_TEXTURE_2D, tex2.texID);
			//

			

			//glBindVertexArray(mesh.vertexarray);
			//glDrawArrays(GL_TRIANGLES, 0, 36);
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


			/*glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float32) * 7, NULL);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 7, (GLvoid*)(sizeof(float32) * 3));
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindBuffer(GL_ARRAY_BUFFER, 0);*/
			//glEnableVertexAttribArray(0);

			/*glBindVertexArray(mesh.vertexarray);
			glBindBuffer(GL_ARRAY_BUFFER, mesh.vertexbuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.indexbuffer);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			glUseProgram(this->program);*/
			
			
			/*glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindBuffer(GL_ARRAY_BUFFER, 0);*/
			//
			//glBindBuffer(GL_ARRAY_BUFFER, 0);
			this->window->SwapBuffers();
		}
		glDeleteVertexArrays(1, &mesh.vertexarray);
		glDeleteBuffers(1, &mesh.vertexbuffer);
		glDeleteBuffers(1, &mesh.indexbuffer);
		glfwTerminate();
	}
}// namespace Example