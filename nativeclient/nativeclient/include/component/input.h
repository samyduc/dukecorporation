#pragma once
#include "base/natdef.h"
#include "base/component.h"

#include <glm/glm.hpp>

namespace Natorium
{

static natU32 s_Input = Hash::Compute("s_Input");

class Input : public Component
{
public:

	static natU32	GetType() { return s_Input; }

	enum eAction
	{
		none,
		forward,
		backward,
		left,
		right,
		jump,
		shoot1
	};

	virtual eAction	GetAction(natU32 _key) = 0;
	virtual natBool IsAction(eAction _action) = 0;
	virtual void GetMousePosition(glm::vec2& _pos) = 0;

protected:
	virtual void ChangeState(eAction _action, bool _state) = 0;
};


}