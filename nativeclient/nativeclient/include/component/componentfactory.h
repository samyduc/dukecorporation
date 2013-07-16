#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include <map>
#include <cassert>

namespace Natorium
{

class Entity;

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

	void			AttachComponent(Entity* _entity, natU32 _type);

public:


private:
	void			PopulateFactory();
	void			UnPopulateFactory();

private:
	typedef std::map<natU32, Component*> componentFactory_t;
	componentFactory_t	m_componentFactory;
};




}