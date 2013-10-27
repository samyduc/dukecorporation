#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"


#include <glm/glm.hpp>

namespace Natorium
{

class ClickController;

static natU32 s_ClickController = Hash::Compute("ClickController");


class ClickController : public Component
{
public:
					ClickController();
	virtual			~ClickController();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_ClickController; }

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);



public:
	glm::vec2		m_speed;

private:
	glm::vec3		m_worldTaget;

};




}