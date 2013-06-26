#include "component/glmanager.h"

#include "component/transform.h"
#include "base/entity.h"
#include "base/layer.h"
#include "base/kernel.h"

#if defined(WINDOWS_TARGET)
#include "shader/position.h"
#include "shader/monotexture.h"
#elif defined(EMSCRIPTEN_TARGET)
#include "shader/position_es.h"
#else
#error "no shader for this platform"
#endif

#include <iostream>
#include <assert.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Natorium
{

GLManager::GLManager()
	: m_globalBindingIndex(0)
	, m_projectionUnif(0)
	, m_viewUnif(0)
	, m_currentCamera(nullptr)
	, m_screenResolution(0, 0)
	, m_projectionMatrixCopy(1.f)
	, m_viewMatrixCorrected(1.f)
{

}

GLManager::~GLManager()
{
}

void GLManager::OnInit()
{
	// glew
#if defined(WINDOWS_TARGET)
	glewInit();
#endif

	// do not know what for
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CW);

	//glEnable(GL_DEPTH_TEST);
	//glDepthMask(GL_TRUE);
	//glDepthFunc(GL_LEQUAL);
	//glDepthRange(0.0f, 1.0f);

	//glEnable(GL_DEPTH_CLAMP);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glEnable (GL_LINE_SMOOTH);
	//glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

	// load shaders
	//CreateShaderProgram();
	OnInitShaders();
	OnInitCamera();

	// must happen when we have a valid opengl context opened (like with sdl)
	glClearColor(0x00, 0xB1, 0xEE, 1.0);

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(0, 640, 480, 0, 0.0f, 512.0f);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	GLint m_viewport[4];
	glGetIntegerv(GL_VIEWPORT, m_viewport);
	m_screenResolution.x = static_cast<natF32>(m_viewport[2]);
	m_screenResolution.y = static_cast<natF32>(m_viewport[3]);
}

void GLManager::OnInitShaders()
{
	//m_shaders.push_back(CreateShader(GL_VERTEX_SHADER, strPositionVertex));
	//m_shaders.push_back(CreateShader(GL_FRAGMENT_SHADER, strPositionFragment));

	m_shaders.push_back(CreateShader(GL_VERTEX_SHADER, strMonoTextureVertex));
	m_shaders.push_back(CreateShader(GL_FRAGMENT_SHADER, strMonoTextureFragment));


	m_shaderProgram = CreateShaderProgram(m_shaders);



	//glGenBuffers(1, &m_globalUnif);
	//glBindBuffer(GL_UNIFORM_BUFFER, m_globalUnif);
	//glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2, NULL, GL_STREAM_DRAW);
	//glBindBuffer(GL_UNIFORM_BUFFER, 0);

	//glBindBufferRange(GL_UNIFORM_BUFFER, m_globalBindingIndex, m_globalUnif, 0, sizeof(glm::mat4) * 2);

	m_viewUnif = glGetUniformLocation(m_shaderProgram, "view");
	m_projectionUnif = glGetUniformLocation(m_shaderProgram, "projection");


}

void GLManager::OnInitCamera()
{
	static float g_fzNear = 1.0f;
	static float g_fzFar = 1000.0f;

	//m_viewMatrix = glm::mat4(1.f);

	//m_cameraToClipMatrix = glm::perspective(0.f, (m_window->GetWidth() / static_cast<float>(m_window->GetHeight())), g_fzNear, g_fzFar);
	//m_cameraToClipMatrix = glm::mat4(1);
	//m_viewMatrix = glm::ortho<float>(0.f, static_cast<float>(640), static_cast<float>(480), 0.f, 0.f, 100.f);
	// usual axis : y to right, x to bottom
	//m_cameraToClipMatrix = glm::rotate<float>(m_cameraToClipMatrix, 90, glm::vec3(0.f, 0.f, 1.f));

	//m_cameraToClipMatrix = glm::mat4(1.f);

	//glBindBuffer(GL_UNIFORM_BUFFER, m_globalUnif);
	//glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(m_cameraToClipMatrix));
	//glBindBuffer(GL_UNIFORM_BUFFER, 0);

	// init projection !!!!
	

}

void GLManager::ComputeCamera()
{
	m_viewMatrixCorrected = m_currentCamera->GetViewMatrix();

	// correct camera
	glm::vec3 center(m_screenResolution.x / 2, m_screenResolution.y / 2, 0);
	m_viewMatrixCorrected = glm::translate(m_viewMatrixCorrected, center);
	m_projectionMatrixCopy = m_currentCamera->GetProjectionMatrix();
}

void GLManager::OnTick(const natU64 _dt)
{
	/*glBindBuffer(GL_UNIFORM_BUFFER, m_globalUnif);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(m_cameraToClipMatrix));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glm::mat4 camera(1.f);
	glBindBuffer(GL_UNIFORM_BUFFER, m_globalUnif);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(camera));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);*/

	if(m_currentCamera)
	{
		ComputeCamera();
	}

	glUseProgram(m_shaderProgram);

	glUniformMatrix4fv(m_viewUnif, 1, GL_FALSE, glm::value_ptr(m_viewMatrixCorrected));
	glUniformMatrix4fv(m_projectionUnif, 1, GL_FALSE, glm::value_ptr(m_projectionMatrixCopy));

	glUseProgram(0);


}

void GLManager::OnDeInit()
{

}

GLuint GLManager::CreateShader(GLenum eShaderType, const std::string &strShaderData)
{
	GLuint shader = glCreateShader(eShaderType);
	const char *strFileData = strShaderData.c_str();
	glShaderSource(shader, 1, &strFileData, NULL);
	
	glCompileShader(shader);
	
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
		
		const char *strShaderType = NULL;
		switch(eShaderType)
		{
		case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
			// Note: no geometry shader in opengl es 2.0
		//case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
		case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
		}
		
		std::cout << "CShaderLoader::CreateShader Compile failure in " << std::string(strShaderType).c_str() << "shader:" << std::string(strInfoLog).c_str() << std::endl;
		delete[] strInfoLog;
	}

	return shader;
}

GLuint GLManager::CreateShaderProgram(const shaders_t &shaderList)
{
	GLuint program = glCreateProgram();
	
	for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
		glAttachShader(program, shaderList[iLoop]);
	

	// TODO move it to something more dynamic
	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "color");
	glBindAttribLocation(program, 2, "textureCoord");
	glBindAttribLocation(program, 3, "baseTexture");

	glLinkProgram(program);
	
	GLint status;
	glGetProgramiv (program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
		std::cout <<  "CShaderLoader::CreateShaderProgram Linker failure: " <<  std::string(strInfoLog).c_str() << std::endl;
		delete[] strInfoLog;
	}

	return program;
}

}