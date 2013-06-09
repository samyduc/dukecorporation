#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include <SDL.h>


namespace Natorium
{

static natU32 s_SDLRender = Hash::Compute("s_SDLRender");

class SDLRender : public Component
{
public:
					SDLRender();
	virtual			~SDLRender();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_SDLRender; }

private:
	SDL_Surface*	m_surface;
};




}