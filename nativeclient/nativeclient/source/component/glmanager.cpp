#include "component/glmanager.h"
#include "base/entity.h"
#include "base/layer.h"
#include "base/kernel.h"

#include "component/transform.h"

#include <iostream>
#include <assert.h>

namespace Natorium
{

GLManager::GLManager()
{

}

GLManager::~GLManager()
{
}

void GLManager::OnInit()
{
	// load shaders
	//CreateShaderProgram();

	// must happen when we have a valid opengl context opened (like with sdl)
	glClearColor(0x00, 0xB1, 0xEE, 1.0);

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	glOrtho(0, 640, 480, 0, 0.0f, 512.0f);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

}

void GLManager::OnTick(natU64 _dt)
{

}

void GLManager::OnDeInit()
{

}

GLuint GLManager::CreateShader(GLenum eShaderType, const std::string &strShaderData)
{

	return 0;
}

GLuint GLManager::CreateShaderProgram(const shaders_t &shaderList)
{
	GLuint program = glCreateProgram();
	
	for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
		glAttachShader(program, shaderList[iLoop]);
	
	glLinkProgram(program);
	
	GLint status;
	glGetProgramiv (program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
		std::cout <<  "CShaderLoader::CreateShaderProgram Linker failure: " <<  std::string(strInfoLog).c_str();
		delete[] strInfoLog;
	}

	return program;
}

}