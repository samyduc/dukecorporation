#include "base/entity.h"
#include "base/component.h"


namespace Natorium
{


Component::Component()
	: m_entity(nullptr)
{

}

Component::~Component()
{

}


void Component::OnInit()
{
}

void Component::OnTick(natU64 _dt)
{
}

void Component::OnDeInit()
{
}

void Component::_Init(Entity& _entity)
{
	m_entity = &_entity;

	OnInit();
}

void Component::_Tick(natU64 _dt)
{

	OnTick(_dt);
}

void Component::_DeInit()
{

	OnDeInit();

	m_entity = nullptr;
}

}