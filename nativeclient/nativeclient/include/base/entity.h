#pragma once

#include "base/natdef.h"

#include <map>
#include <list>

namespace Natorium
{

class Component;
class Entity;
class Kernel;

typedef std::map<natU32, Component*>	components_t;
typedef std::list<Entity*>				childs_t;

class Entity
{
public:

	friend class Kernel;

						Entity();
	virtual				~Entity();

			natU64		GetId() const { return m_id; }
			Entity*		GetParent() { return m_parent; }
			childs_t&	GetChilds() { return m_childs; }

	virtual void		OnInit();
	virtual void		OnTick(natU64 _dt);
	virtual void		OnDeInit();

	Kernel*				GetKernel() const;

protected:
	template<class T>
	void AddComponent()
	{
		m_components[T::GetType()] = new T();
	}

	template<class T>
	void RemoveComponent()
	{
		components_t::iterator it = m_components.find(T::GetType());

		if(it != m_components.end())
		{
			m_components.erase(it);
		}
	}

	template<class T>
	T* GetComponent()
	{
		T* ret = nullptr;
		components_t::iterator it = m_components.find(T::GetType());

		if(it != m_components.end())
		{
			ret = it->second;
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

	void				_Init(Kernel& _kernel);
	void				_Tick(natU64 _dt);
	void				_DeInit();

private:
	Kernel*				m_kernel;
	Entity*				m_parent;

	natU64				m_id;

};




}