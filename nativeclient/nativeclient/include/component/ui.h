#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include <glm/glm.hpp>

namespace Natorium
{
class GLManager;
class Transform;

static natU32 s_UI = Hash::Compute("UI");

class UI : public Component
{
public:
					UI();
	virtual			~UI();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_UI; }

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

	glm::vec2		GetPos() { return m_pos; }
	natF32			GetRad() { return m_rad; }
	glm::vec2		GetScale() { return m_scale; }

public:
	glm::vec2		m_pos;
	natF32			m_rad;
	glm::vec2		m_scale;

private:
	Transform*		m_transform;
	GLManager*		m_glManager;

};




}