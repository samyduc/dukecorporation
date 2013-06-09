#pragma once

#include "base/natdef.h"
#include "entity/root.h"

namespace Natorium
{

class Kernel;

class Layer
{
public:

	enum eLayer
	{
		Layer_0,
		Layer_1,
		Layer_2,
		Layer_3,
		Layer_4,
		Layer_5,
		Layer_Max,
		Layer_Undefined
	};

	Layer();
	virtual ~Layer();

	void			Init(Kernel& _kernel, eLayer _layer);
	void			Tick(const natU64 _dt);
	void			DeInit();

	void			AddEntity(Entity* _entity, Entity* _parent=nullptr);
	void			RemoveEntity(Entity* _entity);

	Entity*			GetRootEntity() { return &m_rootEntity; }


protected:
	eLayer			m_id;
	Root			m_rootEntity;
	Kernel*			m_kernel;

};


}