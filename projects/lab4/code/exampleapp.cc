//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2018 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "exampleapp.h"
#include <cstring>
#include "Matrix4D.h"
#include "Vector4D.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"

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
		window->SetKeyPressFunction([this](int32, int32, int32, int32)
		{
			this->window->Close();
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
			return true;
		}
		return false;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		ExampleApp::Run()
	{
		
		
		mesh.genvertexarray();
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
		stbi_image_free(tex.texPictureData);

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

		tex2.bindTex();
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
		std::cout << tex2.texID << "\n";
		
		glUseProgram(this->program);

		glUniform1i(glGetUniformLocation(this->program, "texture1"), 0);

		glUniform1i(glGetUniformLocation(this->program, "texture2"), 1);
		Matrix4D projection = projection.perspective(75.0f, 800.0f / 600.0f, 0.1f, 100.0f);
		//glm::mat4 projection = glm::perspective(glm::radians(75.0f), (float)800 / (float)600, 0.1f, 100.0f);
		Camera cam(Vector4D(0.0f, 0.0f, -3.0f), Vector4D(0.0f, 0.0f, 0.0f));

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);


		while (this->window->IsOpen())
		{

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			this->window->Update();

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
		
			Matrix4D model;
			//glm::mat4 model = glm::mat4(1.0f);
			

			

			float radius = 10;

			float camX = (float)(cos(glfwGetTime()) * radius);
			float camZ = (float)(sin(glfwGetTime()) * radius);
			std::cout << camZ << "\n";


			//Matrix4D view = view.lookat(Vector4D(camX, 0.0f, camZ), Vector4D(0.0f, 0.0f, 0.0f), Vector4D(0.0f, 1.0f, 0.0f));
			cam.setPosition(Vector4D(camX, 0.0f, camZ));
			cam.setView();
			//glm::mat4 view = glm::mat4(1.0f);
			//view = glm::lookAt(glm::vec3(0.0f, camX, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

			unsigned int modelLoc = glGetUniformLocation(this->program, "model");
			unsigned int viewLoc = glGetUniformLocation(this->program, "view");
			unsigned int projectionLoc = glGetUniformLocation(this->program, "projection");



			std::cout << "MODEL------------" << "\n";
			//model.print();
			std::cout << "----------------" << "\n";

			std::cout << "VIEW------------" << "\n";
			//view.print();

			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
				{
					std::cout << " " << cam.getView()[i][j];
					if (j == 3)
						std::cout << "\n" << "\n";
				}
			std::cout << "--------" << "\n";

			std::cout << "----------------" << "\n";

			std::cout << "PROJECTION------------" << "\n";
			//projection.print();
			std::cout << "----------------" << "\n";


			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &cam.getView()[0][0]);
			glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex.texID);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tex2.texID);
			

			glBindVertexArray(mesh.vertexarray);
			glDrawArrays(GL_TRIANGLES, 0, 36);
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