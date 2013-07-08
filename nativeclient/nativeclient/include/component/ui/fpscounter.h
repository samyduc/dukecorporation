#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include <glm/glm.hpp>

namespace Natorium
{
class GLManager;

static natU32 s_FPSCounter = Hash::Compute("s_FPSCounter");

class FPSCounter : public Component
{
public:
					FPSCounter();
	virtual			~FPSCounter();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_FPSCounter; }

	void			Clone(Entity* _entity) const;

private:
	natU64			m_fps;
	GLManager*		m_glManager;



};




}