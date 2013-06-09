#include "base/entity.h"
#include "base/component.h"

#include <assert.h>

namespace Natorium
{


Component::Component()
	: m_entity(nullptr)
	, m_isInit(false)
{

}

Component::~Component()
{

}


void Component::OnInit()
{
}

void Component::OnTick(const natU64 _dt)
{
}

void Component::OnDeInit()
{
}

void Component::_Init(Entity& _entity)
{
	assert(!m_isInit);
	m_entity = &_entity;

	OnInit();

	m_isInit = true;
}

void Component::_Tick(natU64 _dt)
{

	OnTick(_dt);
}

void Component::_DeInit()
{
	OnDeInit();

	m_entity = nullptr;
	m_isInit = false;
}

}