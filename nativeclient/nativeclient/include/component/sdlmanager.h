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
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_SDLManager; }

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

	void			PreRender();
	void			PostRender(natU64 _tick);
	SDL_Surface*	GetScreen() { return m_screen; }

	natU64			GetTick() { return SDL_GetTicks(); }

private:
	SDL_Surface*	m_screen;
};




}