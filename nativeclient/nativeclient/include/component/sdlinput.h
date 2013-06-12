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

typedef std::map<natU32, Input::eAction> inputs_t;
typedef std::map<Input::eAction, bool> actions_t;

class SDLInput : public Input
{
public:
					SDLInput();
	virtual			~SDLInput();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_Input; }

	void			SetAction(Input::eAction _action, natU32 _key);
	Input::eAction	GetAction(natU32 _key);
	// Input
	natBool			IsAction(Input::eAction _action);
	void			GetMousePosition(glm::vec2& _pos);

protected:
	virtual void	ChangeState(Input::eAction _action, bool _state);

private:
	inputs_t		m_inputs;
	actions_t		m_actions;

};




}