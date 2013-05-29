#pragma once
#include "base/natdef.h"
#include "base/component.h"

namespace Natorium
{

static natU32 s_Input = Hash::Compute("s_Input");

class Input : public Component
{
public:

	static natU32	GetType() { return s_Input; }

	enum eAction
	{
		forward,
		backward,
		left,
		right,
		jump,
		shoot1
	};

	virtual natBool IsAction(eAction _action) = 0;

	
};


}