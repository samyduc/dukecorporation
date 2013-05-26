#include "base/entity.h"
#include "base/kernel.h"
#include "base/component.h"

#include <assert.h>

namespace Natorium
{


Entity::Entity()
	: m_kernel(nullptr)
	, m_parent(nullptr)
	, m_id(0L)
	, m_isInit(false)
{

}

Entity::~Entity()
{
	_DeInit();

	for(components_t::iterator it = m_components.begin(); it != m_components.end(); ++it)
	{
		Component* component = (*it).m_component;
		delete component;
	}
	m_components.clear();

	for(childs_t::iterator it = m_childs.begin(); it != m_childs.end(); ++it)
	{
		Entity* child = (*it);
		delete child;
	}
}

Kernel* Entity::GetKernel() const
{
	return m_kernel; 
}

void Entity::OnInit()
{
}

void Entity::OnTick(natU64 _dt)
{
}

void Entity::OnDeInit()
{
}

void Entity::SetParent(Entity* _entity)
{
	if(m_parent != nullptr)
	{
		m_parent->RemoveChild(this);
	}

	m_parent = _entity;

	if(_entity != nullptr)
	{
		_entity->AddChild(this);
	}
}

void Entity::AddChild(Entity* _entity)
{
	assert(_entity);
	m_childs.push_back(_entity);
}

void Entity::RemoveChild(Entity* _entity)
{
	assert(_entity);
	for(childs_t::iterator it = m_childs.begin(); it != m_childs.end(); ++it)
	{
		Entity* entity = (*it);
		if(entity->GetId() == _entity->GetId())
		{
			m_childs.erase(it);
			break;
		}
	}
}

void Entity::_Init(Kernel& _kernel)
{
	assert(!m_isInit);

	m_kernel = &_kernel;
	m_id = _kernel.GetUniqueId();

	OnInit();

	for(components_t::iterator it = m_components.begin(); it != m_components.end(); ++it)
	{
		Component* component = (*it).m_component;
		component->_Init(*this);
	}

	for(childs_t::iterator it = m_childs.begin(); it != m_childs.end(); ++it)
	{
		Entity* child = (*it);
		child->_Init(_kernel);
	}

	m_isInit = true;
}

void Entity::_Tick(natU64 _dt)
{
	for(components_t::iterator it = m_components.begin(); it != m_components.end(); ++it)
	{
		Component* component = (*it).m_component;
		component->_Tick(_dt);
	}

	for(childs_t::iterator it = m_childs.begin(); it != m_childs.end(); ++it)
	{
		Entity* child = (*it);
		child->_Tick(_dt);
	}

	OnTick(_dt);
}

void Entity::_DeInit()
{
	for(components_t::iterator it = m_components.begin(); it != m_components.end(); ++it)
	{
		Component* component = (*it).m_component;
		component->_DeInit();
	}

	for(childs_t::iterator it = m_childs.begin(); it != m_childs.end(); ++it)
	{
		Entity* child = (*it);
		child->_DeInit();
	}

	OnDeInit();

	m_kernel = nullptr;
	m_isInit = false;
}

}