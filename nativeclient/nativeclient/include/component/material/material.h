#pragma once

#include "base/natdef.h"
#include "base/entity.h"
#include "base/component.h"
#include "base/hash.h"
#include "base/layer.h"
#include "base/kernel.h"

#include "component/glmanager.h"
#include "component/texturemanager.h"

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

static ref_t s_Material = Hash::Compute("Material");

class Shape;

class Material : public Component
{
public:
							Material();
	virtual					~Material();

	virtual void			OnInit();
	virtual void			OnTick(const natU64 _dt);
	virtual void			OnDeInit();
		
	static ref_t			GetType() { return s_Material; }

	virtual void			Clone(Entity* _entity, natU32 _type) const;
	void					WriteData(Serializer& _ser);
	void					ReadData(Serializer& _ser);

	GLuint					GetProgram() { return m_program; }
	ref_t					GetProgramType() { return m_shaderType; }

	virtual void			EnableAndSetVertexAttribute(size_t _colorOffset, size_t _uvOffset) {}
	virtual void			DisableVertexAttribute() {}
	virtual void			BindTexture() {}
	virtual void			UnBindTexture() {}

	virtual void			SetMainTexture(GLuint _texture) {}

public:

protected:

	Shape*					GetShapeFromRender();

protected:
	ref_t					m_shaderType;
	GLuint					m_program;


};




}