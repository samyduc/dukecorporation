#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Natorium
{


static natU32 s_Transform = Hash::Compute("Transform");

static const natF32 s_PI = 3.14159265358979f; 

class Transform : public Component
{
public:
					Transform();
	virtual			~Transform();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_Transform; }

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

public:
	glm::vec3		m_pos;
	glm::quat		m_rot;
	glm::vec3		m_scale;

	glm::vec3		m_forward;
public:

	glm::vec3		GetPos();
	glm::quat		GetRot();
	glm::vec3		GetScale() { return m_scale; }


protected:
	natF32			RadToDeg(natF32 _rad);

};




}