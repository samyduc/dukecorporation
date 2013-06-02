#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"


#if defined(WINDOWS_TARGET)
//#include <Windows.h>
//#include <gl\GL.h>
#include <GL\glew.h>
#endif

#if defined(EMSCRIPTEN_TARGET)
#include <GLES2/gl2.h>
#endif

#include <vector>



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
	virtual void	OnTick(natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_GLManager; }

	GLuint			GetShaderProgram() { return m_shaderProgram; }

private:
	GLuint			CreateShader(GLenum eShaderType, const std::string &strShaderData);
	GLuint			CreateShaderProgram(const shaders_t &shaderList);

private:
	shaders_t		m_shaders;
	GLuint			m_shaderProgram;


};




}