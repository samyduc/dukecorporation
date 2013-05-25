#include "component/sdlmanager.h"

#include <iostream>

namespace Natorium
{


SDLManager::SDLManager()
	: m_screen(nullptr)
{

}

SDLManager::~SDLManager()
{

}


void SDLManager::OnInit()
{
	SDL_Init(SDL_INIT_VIDEO);
	m_screen = SDL_SetVideoMode(640, 480, 16, SDL_HWSURFACE);
}

void SDLManager::OnTick(natU64 _dt)
{
	SDL_Event event;

	while ( SDL_PollEvent(&event) ) {
		switch (event.type) {
			case SDL_QUIT:
				exit(0);
		}
	}

	SDL_FillRect(m_screen, &m_screen->clip_rect, SDL_MapRGB( m_screen->format, 0x00, 0xB2, 0xEE ) );
	SDL_UpdateRect(m_screen, 0, 0, m_screen->clip_rect.w, m_screen->clip_rect.h); 

	SDL_LockSurface(m_screen);
	SDL_UnlockSurface(m_screen);

	SDL_Flip(m_screen);
}

void SDLManager::OnDeInit()
{
	SDL_FreeSurface(m_screen);
	m_screen = nullptr;

	SDL_Quit();
}









}