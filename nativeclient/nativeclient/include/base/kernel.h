#pragma once

#include "base/natdef.h"
#include "base/timeplatform.h"
#include "base/entity.h"

#include "entity/root.h"

#include <map>

namespace Natorium
{

class Kernel
{
public:

			Kernel();
			~Kernel();

	void	Init();
	void	Tick();
	void	DeInit();

	void	AddEntity(Entity* _entity, Entity* _parent=nullptr);
	void	RemoveEntity(Entity* _entity);

	natU64	GetUniqueId();

private:
	Root	m_rootEntity;
	timer_t m_currentTime;

	natU64	m_currentId;


};




}