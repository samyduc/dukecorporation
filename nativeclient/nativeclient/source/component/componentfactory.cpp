#include "component/componentfactory.h"

#include "base/entity.h"

namespace Natorium
{

ComponentFactory::ComponentFactory()
{

}

ComponentFactory::~ComponentFactory()
{

}

void ComponentFactory::OnInit()
{
	// this is generated son
	PopulateFactory();
}

void ComponentFactory::OnTick(const natU64 _dt)
{

}

void ComponentFactory::AttachComponent(Entity* _entity, natU32 _type)
{
	componentFactory_t::iterator it = m_componentFactory.find(_type);
	assert(it != m_componentFactory.end());

	Component* component = it->second;

	// add component to type
	component->Clone(_entity, 0);
}

void ComponentFactory::UnPopulateFactory()
{
	for(componentFactory_t::iterator it = m_componentFactory.begin(); it != m_componentFactory.end(); ++it)
	{
		Component* component = it->second;
		delete component;
	}

	m_componentFactory.clear();
}

void ComponentFactory::OnDeInit()
{
	UnPopulateFactory();
}











}