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

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

private:
	SDL_Surface*	m_surface;
};




}