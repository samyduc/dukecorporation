#include "component/sdlmanager.h"

#include "base/kernel.h"
#include <assert.h>
#include <iostream>

#if defined(WINDOWS_TARGET)
//#include <Windows.h>
//#include <gl\GL.h>
#include <GL\glew.h>
#endif

#if defined(EMSCRIPTEN_TARGET)
#include <GLES2/gl2.h>
#endif

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

	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	m_screen = SDL_SetVideoMode(640, 480, 32, SDL_OPENGL);

	assert(m_screen);
}

void SDLManager::OnTick(const natU64 _dt)
{
	//SDL_LockSurface(m_screen);

	//SDL_UnlockSurface(m_screen);

	//SDL_FillRect(m_screen, NULL, SDL_MapRGB( m_screen->format, 0x00, 0xB2, 0xEE ) );
	//SDL_UpdateRect(m_screen, 0, 0, m_screen->clip_rect.w, m_screen->clip_rect.h); 
	//SDL_UpdateRect(m_screen, 0, 0, 0, 0);

	//SDL_Flip(m_screen);
}

void SDLManager::PreRender()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void SDLManager::PostRender()
{
	glFinish();
	SDL_GL_SwapBuffers();
}

void SDLManager::OnDeInit()
{
	SDL_FreeSurface(m_screen);
	m_screen = nullptr;

	SDL_Quit();
}









}