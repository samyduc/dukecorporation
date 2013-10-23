#pragma once

#include "base/natdef.h"
#include "entity/root.h"

namespace Natorium
{

class Kernel;

class Layer
{
public:

	static const size_t s_LayerManager = 0;

	explicit Layer();
	virtual ~Layer();

	void			Init(Kernel& _kernel, size_t _layerID);
	void			Tick(const natU64 _dt);
	void			DeInit();

	void			AddEntity(Entity* _entity, Entity* _parent=nullptr);
	void			RemoveEntity(Entity* _entity);

	Entity*			GetRootEntity() { return &m_rootEntity; }

	size_t			GetLayerID() const { return m_id; }

protected:
	size_t			m_id;
	Root			m_rootEntity;
	Kernel*			m_kernel;

};


}