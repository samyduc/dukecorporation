#include "base/kernel.h"

#include <assert.h>

namespace Natorium
{


Kernel::Kernel()
	: m_currentTime(0L)
	, m_currentId(0L)
{

}

Kernel::~Kernel()
{

}

void Kernel::Init()
{
	m_currentId = 0;
	m_currentTime = Time::GetMsTime();

	m_rootEntity._Init(*this);
}

void Kernel::Tick()
{
	timer_t now = Time::GetMsTime();
	natU64 dt = now - m_currentTime;
	m_currentTime = now;

	m_rootEntity._Tick(dt);
}

void Kernel::DeInit()
{
	m_currentId = 0;
	m_rootEntity._DeInit();
}

natU64 Kernel::GetUniqueId()
{
	++m_currentId;
	return m_currentId;
}

void Kernel::AddEntity(Entity* _entity, Entity* _parent)
{
	assert(_entity);

	_entity->_Init(*this);

	if(_parent != nullptr)
	{
		_entity->SetParent(_parent);
	}
	else
	{
		_entity->SetParent(&m_rootEntity);
	}
}

void Kernel::RemoveEntity(Entity* _entity)
{
	assert(_entity);

	_entity->SetParent(nullptr);
	_entity->_DeInit();

	delete _entity;
}


}