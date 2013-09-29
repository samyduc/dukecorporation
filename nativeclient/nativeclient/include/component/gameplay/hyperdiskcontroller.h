#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"


#include <glm/glm.hpp>

namespace Natorium
{

class DiskController;

static natU32 s_HyperdiskController = Hash::Compute("HyperdiskController");


class HyperdiskController : public Component
{
public:
					HyperdiskController();
	virtual			~HyperdiskController();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_HyperdiskController; }

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

	virtual void	LookAtScreen(glm::vec3& _look);

	void			OnEnterCollide(Contact* _contact);

	void			ShootDisk(glm::vec3& _pos);

private:
	DiskController* m_currentDisk;

};




}