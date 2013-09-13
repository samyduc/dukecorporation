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
#include <map>
#include <list>
#include <glm/glm.hpp>


namespace Natorium
{

static natU32 s_GLManager = Hash::Compute("GLManager");

class GLRender;

typedef std::map<natU32, GLuint> shaders_t;
typedef std::vector<GLuint> shaders_list_t;
typedef std::list<GLRender*> render_list_t;
typedef std::map<natU32, render_list_t> render_map_t;

class GLManager : public Component
{
public:
					GLManager();
	virtual			~GLManager();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_GLManager; }

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

	const int		GetGlobalBindingIndex() { return m_globalBindingIndex; }

	GLuint			GetProgram(natU32 _type);
	render_list_t*	GetRenderList(natU32 _type);

	Camera*			GetCamera() { return m_currentCamera; }
	void			SetCamera(Camera* _camera) { m_currentCamera = _camera; }

	glm::vec2		GetScreenResolution() { return m_screenResolution; }

	natU64			GetLastTick() const { return m_lastRenderTick; }

	void			Render(natU64 _tick);
	void			ClearRender();

private:
	void			OnInitShaders();
	void			OnInitCamera();

	void			RegisterProgram(const natChar *_name, const std::string &_strVertex, const std::string &_strFragment);
	GLuint			CreateShader(GLenum eShaderType, const std::string &strShaderData);
	GLuint			CreateShaderProgram(const shaders_list_t &shaderList);

	void			ComputeCamera();

public:
	glm::vec4		m_clearColor;

private:
	shaders_t		m_shaderPrograms;
	render_map_t	m_renderMap;

	Camera*			m_currentCamera;

	GLuint			m_viewUnif;
	GLuint			m_projectionUnif;

	glm::vec2		m_screenResolution;
	glm::mat4		m_viewMatrixCorrected;
	glm::mat4		m_projectionMatrixCopy;

	//GLuint m_globalUnif;
	const int		m_globalBindingIndex;

	natU64			m_lastRenderTick;
};




}