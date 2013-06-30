#include "base/kernel.h"

#include "component/sdlmanager.h"
#include "component/glmanager.h"
#include "component/sdlinput.h"
#include "component/physicsmanager.h"
#include "component/scenemanager.h"
#include "component/playersmanager.h"
#include "component/filemanager.h"
#include "component/texturemanager.h"

#include <assert.h>

namespace Natorium
{


Kernel::Kernel()
	: m_currentTime(0L)
	, m_currentId(0L)
	, m_acc(0)
{
	m_layers.reserve(Layer::Layer_Max);

	for(size_t i = Layer::Layer_0; i < Layer::Layer_Max; ++i)
	{
		Layer* layer = new Layer();
		m_layers.push_back(layer);
	}

	m_rateStep = static_cast<natU64>(1/60.f * 1000.f);
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
	m_acc = 0;

	// add manager on layer 0
	Layer* layer = m_layers[0];
	Entity* entity = layer->GetRootEntity();

	entity->AddComponent<FileManager>();
	SDLManager* sdlmanager = entity->AddComponent<SDLManager>();
	entity->AddComponent<SDLInput>();
	entity->AddComponent<GLManager>();
	entity->AddComponent<PhysicsManager>();
	entity->AddComponent<PlayersManager>();
	entity->AddComponent<TextureManager>();

	m_currentTime = sdlmanager->GetTick();

	for(size_t i = Layer::Layer_0; i < Layer::Layer_Max; ++i)
	{
		Layer* layer = m_layers[i];
		layer->Init(*this, static_cast<Layer::eLayer>(i));
	}

	entity->AddComponent<SceneManager>();

}

void Kernel::Tick()
{
	Layer* layer = m_layers[0];
	Entity* entity = layer->GetRootEntity();
	SDLManager* sdlmanager = entity->GetComponent<SDLManager>();
	GLManager* glmanager = entity->GetComponent<GLManager>();

	natU64 now = sdlmanager->GetTick();
	natU64 dt = now - m_currentTime;
	m_currentTime = now;

	m_acc += dt;

	if(m_acc >= 250)
	{
		m_acc = 250;
	}

	sdlmanager->PreRender();

	while(m_acc >= m_rateStep)
	{
		glmanager->ClearRender();
		m_acc -= m_rateStep;

		for(layers_t::iterator it = m_layers.begin(); it != m_layers.end(); ++it)
		{
			Layer* layer = (*it);
			//layer->Tick(dt);
			layer->Tick(m_rateStep);
		}
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