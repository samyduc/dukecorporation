#include "component/sdlinput.h"

#include "base/entity.h"
#include "base/layer.h"
#include "base/kernel.h"

#include <assert.h>

namespace Natorium
{

SDLInput::SDLInput()
{
}

SDLInput::~SDLInput()
{
	
}

void SDLInput::OnInit()
{
	// default init
	SetAction(Input::forward, static_cast<natU32>(SDLK_UP));
	SetAction(Input::backward, static_cast<natU32>(SDLK_DOWN));
	SetAction(Input::left, static_cast<natU32>(SDLK_LEFT));
	SetAction(Input::right, static_cast<natU32>(SDLK_RIGHT));
	SetAction(Input::jump, static_cast<natU32>(SDLK_SPACE));
	SetAction(Input::shoot1, static_cast<natU8>(SDL_BUTTON_LEFT));
	SetAction(Input::exit, static_cast<natU8>(SDLK_ESCAPE));
}

void SDLInput::OnTick(const natU64 _dt)
{
	SDL_Event event;

	while ( SDL_PollEvent(&event) ) {
		switch (event.type) {
			case SDL_QUIT:
				GetEntity()->GetKernel()->SetShutdown();
				break;
			case SDL_KEYDOWN:
				{
					 SDLKey key = event.key.keysym.sym;
					 Input::eAction action = GetAction(static_cast<natU32>(key));
					 ChangeState(action, true);
				}
				break;
			case SDL_KEYUP:
				{
					 SDLKey key = event.key.keysym.sym;
					 Input::eAction action = GetAction(static_cast<natU32>(key));
					 ChangeState(action, false);
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				{
					natU8 button = event.button.button;
					Input::eAction action = GetAction(static_cast<natU8>(button));
					ChangeState(action, true);
				}
				break;
			case SDL_MOUSEBUTTONUP:
				{
					natU8 button = event.button.button;
					Input::eAction action = GetAction(static_cast<natU8>(button));
					ChangeState(action, false);
				}
				break;
			default:
				break;
		}
	}
}

void SDLInput::OnDeInit()
{

}

// Input
natBool SDLInput::IsAction(Input::eAction _action)
{
	natBool ret = false;
	actions_t::iterator it = m_actions.find(_action);

	if(it != m_actions.end())
	{
		ret = it->second;
	}
	return ret;
}

void SDLInput::SetAction(Input::eAction _action, natU32 _key)
{
	m_inputs_key[_key] = _action;
	m_actions[_action] = false;
}

void SDLInput::SetAction(Input::eAction _action, natU8 _mouse)
{
	m_inputs_mouse[_mouse] = _action;
	m_actions[_action] = false;
}

Input::eAction	SDLInput::GetAction(natU32 _key)
{
	eAction action = Input::none;
	inputs_key_t::iterator it = m_inputs_key.find(_key);

	if(it != m_inputs_key.end())
	{
		action = it->second;
	}

	return action;
}

Input::eAction	SDLInput::GetAction(natU8 _mouse)
{
	eAction action = Input::none;
	inputs_mouse_t::iterator it = m_inputs_mouse.find(_mouse);

	if(it != m_inputs_mouse.end())
	{
		action = it->second;
	}

	return action;
}

void SDLInput::ChangeState(Input::eAction _action, bool _state)
{
	actions_t::iterator it = m_actions.find(_action);

	if(it != m_actions.end())
	{
		it->second = _state;
	}
}

void SDLInput::GetMousePosition(glm::vec2& _pos)
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	_pos.x = static_cast<natF32>(x);
	_pos.y = static_cast<natF32>(y);
}

}