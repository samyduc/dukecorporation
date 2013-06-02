#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

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
	virtual void	OnTick(natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_GLRender; }

private:

};




}