#include "component/sdlrender.h"
#include "base/entity.h"
#include "base/layer.h"

#include "component/transform.h"

#include <assert.h>

namespace Natorium
{

SDLRender::SDLRender()
{

}

SDLRender::~SDLRender()
{
}

void SDLRender::OnInit()
{
	SDLManager* sdlmanager = GetEntity()->GetLayer()->GetRootEntity()->GetComponent<SDLManager>();

	m_surface = SDL_CreateRGBSurface(SDL_HWSURFACE, 50, 50, 32, 0, 0, 0, 0);

	assert(m_surface);
}

void SDLRender::OnTick(natU64 _dt)
{
	SDLManager* sdlmanager = GetEntity()->GetLayer()->GetRootEntity()->GetComponent<SDLManager>();
	Transform* transform = GetEntity()->GetComponent<Transform>();

	SDL_Rect position;
	position.x = static_cast<Sint16>(transform->m_pos_x);
	position.y = static_cast<Sint16>(transform->m_pos_y);
	position.w = m_surface->clip_rect.w;
	position.h = m_surface->clip_rect.h;

	SDL_LockSurface(m_surface);
	SDL_UnlockSurface(m_surface);

	SDL_FillRect(m_surface, NULL, SDL_MapRGB(sdlmanager->GetScreen()->format, 50, 50, 50));
	SDL_BlitSurface(m_surface, NULL, sdlmanager->GetScreen(), &position);
}

void SDLRender::OnDeInit()
{
	SDL_FreeSurface(m_surface);
}

}