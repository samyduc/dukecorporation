#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include <SDL.h>


namespace Natorium
{

static natU32 s_SDLManager = Hash::Compute("s_SDLManager");

class SDLManager : public Component
{
public:
					SDLManager();
	virtual			~SDLManager();

	virtual void	OnInit();
	virtual void	OnTick(natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_SDLManager; }

	SDL_Surface*	GetScreen() { return m_screen; }

private:
	SDL_Surface*	m_screen;
};




}