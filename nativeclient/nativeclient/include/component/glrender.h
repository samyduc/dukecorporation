#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include <glm/glm.hpp>

#if defined(WINDOWS_TARGET)
//#include <windows.h>
//#include <gl\GL.h>
#include <GL\glew.h>
#endif

#if defined(EMSCRIPTEN_TARGET)
#include <GLES2/gl2.h>
#endif


namespace Natorium
{

static natU32 s_GLRender = Hash::Compute("s_GLRender");

class GLRender : public Component
{
public:
					GLRender();
	virtual			~GLRender();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_GLRender; }

private:
	GLuint		m_shaderProgram;
	GLuint		m_bufferObject;
	GLuint		m_offsetPosition;

	glm::mat4	m_modelMatrix;
	GLuint		m_modelUnif;

	GLuint		m_globalUnifBlockIndex;


};




}