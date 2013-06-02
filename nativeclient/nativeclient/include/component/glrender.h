#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#if defined(WINDOWS_TARGET)
#include <windows.h>
#endif

#include <GL/GL.h>


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