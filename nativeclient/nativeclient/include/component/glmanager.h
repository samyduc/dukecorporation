#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include "component/camera.h"


#if defined(WINDOWS_TARGET)
//#include <Windows.h>
//#include <gl\GL.h>
#include <GL\glew.h>
#endif

#if defined(EMSCRIPTEN_TARGET)
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#endif

#include <vector>
#include <glm/glm.hpp>


namespace Natorium
{

static natU32 s_GLManager = Hash::Compute("s_GLManager");

typedef std::vector<GLuint> shaders_t;

class GLManager : public Component
{
public:
					GLManager();
	virtual			~GLManager();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_GLManager; }

	GLuint			GetShaderProgram() { return m_shaderProgram; }
	const int		GetGlobalBindingIndex() { return m_globalBindingIndex; }

	Camera*			GetCamera() { return m_currentCamera; }
	void			SetCamera(Camera* _camera) { m_currentCamera = _camera; }

	glm::vec2		GetScreenResolution() { return m_screenResolution; }

private:
	void			OnInitShaders();
	void			OnInitCamera();

	GLuint			CreateShader(GLenum eShaderType, const std::string &strShaderData);
	GLuint			CreateShaderProgram(const shaders_t &shaderList);

	void			ComputeCamera();

private:
	shaders_t		m_shaders;
	GLuint			m_shaderProgram;

	Camera*			m_currentCamera;

	GLuint			m_viewUnif;
	GLuint			m_projectionUnif;

	glm::vec2		m_screenResolution;
	glm::mat4		m_viewMatrixCorrected;
	glm::mat4		m_projectionMatrixCopy;

	//GLuint m_globalUnif;
	const int m_globalBindingIndex;
};




}