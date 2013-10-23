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

void Layer::Init(Kernel& _kernel, size_t _layerID)
{
	m_kernel = &_kernel;
	m_id = _layerID;
	m_rootEntity._Init(_kernel, *this);
}

void Layer::Tick(const natU64 _dt)
{
	m_rootEntity._Tick(_dt);
}

void Layer::DeInit()
{
	m_rootEntity._DeInit();
	m_id = 0;
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
}











}