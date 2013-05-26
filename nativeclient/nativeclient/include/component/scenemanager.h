#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

namespace Natorium
{

static natU32 s_SceneManager = Hash::Compute("s_SceneManagerr");

class SceneManager : public Component
{
public:
					SceneManager();
	virtual			~SceneManager();

	virtual void	OnInit();
	virtual void	OnTick(natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_SceneManager; }


private:

};




}