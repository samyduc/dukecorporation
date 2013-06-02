#include "component/sdlinput.h"
#include <assert.h>

namespace Natorium
{

SDLInput::SDLInput()
	: m_keystates(nullptr)
{
}

SDLInput::~SDLInput()
{
	
}

void SDLInput::OnInit()
{
	assert(m_keystates == nullptr);
	/*m_keystates = SDL_GetKeyState(NULL);

	// default init
	SetAction(Input::forward, SDLK_UP);
	SetAction(Input::backward, SDLK_DOWN);
	SetAction(Input::left, SDLK_LEFT);
	SetAction(Input::right, SDLK_RIGHT);
	SetAction(Input::jump, SDLK_SPACE);
	SetAction(Input::shoot1, SDLK_RETURN);*/
}

void SDLInput::OnTick(natU64 _dt)
{
	//SDL_PumpEvents();
}

void SDLInput::OnDeInit()
{
	delete m_keystates;
	m_keystates = nullptr;
}

// Input
natBool SDLInput::IsAction(Input::eAction _action)
{
	natBool ret = false;
	inputs_t::iterator it = m_inputs.find(_action);

	if(it != m_inputs.end())
	{
		Uint8 key = it->second;

		if(m_keystates[key])
		{
			ret = true;
		}
	}
	return ret;
}

void SDLInput::SetAction(Input::eAction _action, SDLKey _key)
{
	m_inputs[_action] = _key;
}

void SDLInput::GetMousePosition(glm::vec2& _pos)
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	_pos.x = static_cast<natF32>(x);
	_pos.y = static_cast<natF32>(y);
}

}