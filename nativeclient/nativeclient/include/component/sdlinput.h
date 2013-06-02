#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"
#include "component/input.h"

#include <SDL.h>

#include <map>

namespace Natorium
{

extern natU32 s_Input;

typedef std::map<Input::eAction, Uint8> inputs_t;

class SDLInput : public Input
{
public:
					SDLInput();
	virtual			~SDLInput();

	virtual void	OnInit();
	virtual void	OnTick(natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_Input; }

	void			SetAction(Input::eAction _action, SDLKey _key);

	// Input
	natBool			IsAction(Input::eAction _action);
	void			GetMousePosition(glm::vec2& _pos);

private:
	Uint8*			m_keystates;
	inputs_t		m_inputs;

};




}