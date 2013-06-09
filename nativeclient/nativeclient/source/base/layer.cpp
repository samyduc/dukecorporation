#include "base/layer.h"

#include "base/kernel.h"
#include <assert.h>

namespace Natorium
{

Layer::Layer()
{

}

Layer::~Layer()
{

}

void Layer::Init(Kernel& _kernel, eLayer _layer)
{
	m_kernel = &_kernel;
	m_id = _layer;
	m_rootEntity._Init(_kernel, *this);
}

void Layer::Tick(const natU64 _dt)
{
	m_rootEntity._Tick(_dt);
}

void Layer::DeInit()
{
	m_rootEntity._DeInit();
	m_id = Layer::Layer_Undefined;
}

void Layer::AddEntity(Entity* _entity, Entity* _parent)
{
	assert(_entity);

	if(_parent != nullptr)
	{
		_entity->SetParent(_parent);
	}
	else
	{
		_entity->SetParent(&m_rootEntity);
	}

	if(_entity->GetParent()->IsInit())
	{
		_entity->_Init(*m_kernel, *this);
	}
}

void Layer::RemoveEntity(Entity* _entity)
{
	assert(_entity);

	_entity->SetParent(nullptr);
	_entity->_DeInit();

	delete _entity;
}











}