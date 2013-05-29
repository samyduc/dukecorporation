#pragma once

#include "base/natdef.h"
#include "base/component.h"

#include <list>

namespace Natorium
{

class Component;
class Entity;
class Kernel;
class Layer;
struct PackComponent;

typedef std::list<PackComponent>		components_t;
typedef std::list<Entity*>				childs_t;

struct PackComponent
{
	PackComponent(natU32 _id, Component* _component) : m_id(_id), m_component(_component)
	{}

	natU32 m_id;
	Component* m_component;
};

class Entity
{
public:

	friend class Layer;

						Entity();
	virtual				~Entity();

			natU64		GetId() const { return m_id; }
			Entity*		GetParent() { return m_parent; }
			childs_t&	GetChilds() { return m_childs; }

	virtual void		OnInit();
	virtual void		OnTick(natU64 _dt);
	virtual void		OnDeInit();

	natBool				IsInit() { return m_isInit; }

	Layer*				GetLayer() const;
	Kernel*				GetKernel() const;

	template<class T>
	void AddComponent()
	{
		T* component = new T();
		if(m_isInit)
		{
			// already running : hot init
			component->_Init(*this);
		}
		PackComponent pack_component(T::GetType(), component);
		m_components.push_back(pack_component);
	}

	template<class T>
	void RemoveComponent()
	{
		for(components_t::iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			PackComponent& pack_component = (*it);

			if(pack_component.m_id == T::GetType())
			{
				Component* component = pack_component.m_component;
				if(component->IsInit())
				{
					component->_DeInit();
				}
				m_components.erase(it);
				delete component;
				break;
			}
		}
	}

	template<class T>
	T* GetComponent()
	{
		T* ret = nullptr;
		for(components_t::iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			PackComponent& pack_component = (*it);

			if(pack_component.m_id == T::GetType())
			{
				ret = static_cast<T*>(pack_component.m_component);
				break;
			}
		}
		return ret;
	}


	void				SetParent(Entity* _entity);
	void				AddChild(Entity* _entity);
	void				RemoveChild(Entity* _entity);

protected:
	components_t		m_components;
	childs_t			m_childs;

private:

	void				_Init(Kernel& _kernel, Layer& _layer);
	void				_Tick(natU64 _dt);
	void				_DeInit();

private:
	Kernel*				m_kernel;
	Layer*				m_layer;
	Entity*				m_parent;

	natU64				m_id;
	natBool				m_isInit;

};




}