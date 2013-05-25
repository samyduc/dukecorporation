#pragma once

#include "base/natdef.h"
#include "base/component.h"

#include <SDL.h>


namespace Natorium
{

class SDLManager : public Component
{
public:
					SDLManager();
	virtual			~SDLManager();

	virtual void	OnInit();
	virtual void	OnTick(natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return 1; }

private:
	SDL_Surface*	m_screen;
};




}