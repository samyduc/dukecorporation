#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include <glm/glm.hpp>


namespace Natorium
{

static natU32 s_DiskController = Hash::Compute("DiskController");

class DiskController : public Component
{
public:
					DiskController();
	virtual			~DiskController();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_DiskController; }

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

	void			ShootAt(glm::vec3 _pos);

	void			OnEnterCollide(Contact* _contact);

public:

protected:


};




}