#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include <glm/glm.hpp>

namespace Natorium
{
class GLManager;

static natU32 s_FPSCounter = Hash::Compute("FPSCounter");

class FPSCounter : public Component
{
public:
					FPSCounter();
	virtual			~FPSCounter();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_FPSCounter; }

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

private:
	natU64			m_fps;
	GLManager*		m_glManager;



};




}