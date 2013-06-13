#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"


#include <glm/glm.hpp>


namespace Natorium
{

class Bullet;

static natU32 s_BulletController = Hash::Compute("s_BulletController");

class BulletController : public Component
{
public:
					BulletController();
	virtual			~BulletController();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_BulletController; }

private:


};




}