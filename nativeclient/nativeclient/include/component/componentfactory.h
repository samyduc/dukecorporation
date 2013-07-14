#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include <list>
#include <cassert>

namespace Natorium
{

static natU32 s_ComponentFactory = Hash::Compute("s_ComponentFactory");

class ComponentFactory : public Component
{
public:
					ComponentFactory();
	virtual			~ComponentFactory();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_ComponentFactory; }

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

	Component*		GetComponent(natU32 _type);

public:


private:


};




}