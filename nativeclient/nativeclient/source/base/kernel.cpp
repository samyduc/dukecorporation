#include "base/kernel.h"

#include "component/sdlmanager.h"
#include "component/glmanager.h"
#include "component/sdlinput.h"

#include <assert.h>

namespace Natorium
{


Kernel::Kernel()
	: m_currentTime(0L)
	, m_currentId(0L)
{
	m_layers.reserve(Layer::Layer_Max);

	for(size_t i = Layer::Layer_0; i < Layer::Layer_Max; ++i)
	{
		Layer* layer = new Layer();
		m_layers.push_back(layer);
	}
}

Kernel::~Kernel()
{
	for(layers_t::iterator it = m_layers.begin(); it != m_layers.end(); ++it)
	{
		Layer* layer = (*it);
		delete layer;
	}
	m_layers.clear();
}

void Kernel::Init()
{
	m_currentId = 0;
	m_currentTime = Time::GetMsTime();

	// add manager on layer 0
	Layer* layer = m_layers[0];
	Entity* entity = layer->GetRootEntity();

	entity->AddComponent<SDLManager>();
	entity->AddComponent<SDLInput>();
	entity->AddComponent<GLManager>();
	entity->AddComponent<SceneManager>();

	for(size_t i = Layer::Layer_0; i < Layer::Layer_Max; ++i)
	{
		Layer* layer = m_layers[i];
		layer->Init(*this, static_cast<Layer::eLayer>(i));
	}

}

void Kernel::Tick()
{
	timer_t now = Time::GetMsTime();
	natU64 dt = now - m_currentTime;
	m_currentTime = now;

	Layer* layer = m_layers[0];
	Entity* entity = layer->GetRootEntity();
	SDLManager* sdlmanager = entity->GetComponent<SDLManager>();
	sdlmanager->PreRender();

	for(layers_t::iterator it = m_layers.begin(); it != m_layers.end(); ++it)
	{
		Layer* layer = (*it);
		layer->Tick(dt);
	}

	sdlmanager->PostRender();
}

void Kernel::DeInit()
{
	m_currentId = 0;

	for(layers_t::iterator it = m_layers.begin(); it != m_layers.end(); ++it)
	{
		Layer* layer = (*it);
		layer->DeInit();
	}
}

natU64 Kernel::GetUniqueId()
{
	++m_currentId;
	return m_currentId;
}

void Kernel::AddEntity(Layer::eLayer _layer, Entity* _entity, Entity* _parent)
{
	Layer* layer = m_layers[_layer];
	layer->AddEntity(_entity, _parent);
}

void Kernel::RemoveEntity(Entity* _entity)
{
	Layer* layer = _entity->GetLayer();
	layer->RemoveEntity(_entity);
}

}