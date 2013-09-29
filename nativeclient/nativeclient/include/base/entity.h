#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/contact.h"

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
	friend class Kernel;

						Entity();
	virtual				~Entity();

			natU64		GetId() const { return m_id; }
			Entity*		GetParent() { return m_parent; }
			childs_t&	GetChilds() { return m_childs; }

	virtual void		OnInit();
	virtual void		OnTick(const natU64 _dt);
	virtual void		OnDeInit();

	void				OnEnable();
	void				OnDisable();
	void				OnEnterCollide(Contact *_contact);
	void				OnExitCollide(Contact *_contact);

	natBool				IsInit() const { return m_isInit; }
	natBool				IsEnabled() const { return m_enabled; }

	Entity*				Clone(Entity* _entity=nullptr) const;

	Layer*				GetLayer() const;
	Kernel*				GetKernel() const;

	void				SetEnabled(natBool _enabled) { _OnSetEnable(_enabled); }

	void				Reset();

	template<class T>
	T* AddComponent()
	{
		T* component = GetComponent<T>();

		if(component == nullptr)
		{
			component = new T();

			if(m_isInit)
			{
				// already running : hot init
				component->_Init(*this);
			}
			PackComponent pack_component(T::GetType(), component);
			m_components.push_back(pack_component);
		}

		return component;
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

	Component* GetComponentByType(natU32 _type)
	{
		Component* ret = nullptr;

		for(components_t::iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			PackComponent& pack_component = (*it);

			if(pack_component.m_id == _type)
			{
				ret = pack_component.m_component;
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

protected:

	void				_Init(Kernel& _kernel, Layer& _layer);
	void				_Tick(natU64 _dt);
	void				_DeInit();

	void				_OnSetEnable(natBool _enabled);

private:
	Kernel*				m_kernel;
	Layer*				m_layer;
	Entity*				m_parent;

	natU64				m_id;

protected:
	natBool				m_isInit;

	natBool				m_enabled;

};




}