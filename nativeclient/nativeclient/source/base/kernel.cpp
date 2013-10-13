#include "base/kernel.h"

#include "component/sdlmanager.h"
#include "component/glmanager.h"
#include "component/sdlinput.h"
#include "component/physicsmanager.h"
#include "component/scenemanager.h"
#include "component/playersmanager.h"
#include "component/filemanager.h"
#include "component/componentfactory.h"

#include "tinyxml/tinyxml2.h"

#include <cassert>

#include <cstdio>

namespace Natorium
{


Kernel::Kernel()
	: m_currentTime(0L)
	, m_currentId(0L)
	, m_acc(0)
	, m_isReady(false)
	, m_isShutdown(false)
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
	if(m_isReady)
	{
		DeInit();
	}

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

	// start boot loading
	BootLoader("/data/boot.cfg");
	m_isReady = true;
}

void Kernel::Tick()
{
	Layer* layer = m_layers[0];
	static Entity* entity = layer->GetRootEntity();
	static SDLManager* sdlmanager = entity->GetComponent<SDLManager>();
	static GLManager* glmanager = entity->GetComponent<GLManager>();

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
	sdlmanager->PostRender(dt);
}

void Kernel::DeInit()
{
	m_isReady = false;
	m_currentId = 0;

	for(layers_t::reverse_iterator it = m_layers.rbegin(); it != m_layers.rend(); ++it)
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

void Kernel::BootLoader(const natChar* _path)
{
	printf("BootLoader\n");
	// add manager on layer 0
	Layer* layer0 = m_layers[0];
	Entity* entity = layer0->GetRootEntity();

	// base component needed for everything else
	ComponentFactory* componenfactory = entity->AddComponent<ComponentFactory>();
	FileManager* filemanager = entity->AddComponent<FileManager>();
	assert(componenfactory);
	assert(filemanager);

	// hack because inheritance is bad, and it is not a valid component 
	entity->AddComponent<SDLInput>();

	layer0->Init(*this, Layer::Layer_0);

	size_t size;
	natU8 *buffer = filemanager->Read(_path, &size);

	tinyxml2::XMLDocument doc;
	doc.Parse(reinterpret_cast<natChar*>(buffer), size);

	tinyxml2::XMLElement* element = doc.FirstChildElement("boot");
	assert(element);

	tinyxml2::XMLElement* element_sequence = element->FirstChildElement("sequence");

	// iterate over all boot sequence
	while(element_sequence)
	{
		tinyxml2::XMLElement* element_component = element_sequence->FirstChildElement("component");
		printf("sequence \n");
		while(element_component)
		{
			printf("component %s\n", element_component->Attribute("class"));
			// hack to avoid premature init of global manager
			entity->m_isInit = false;

			Component * new_component = componenfactory->ParseComponent(entity, element_component);
			entity->m_isInit = true;
			new_component->_Init(*entity);

			element_component = element_component->NextSiblingElement();
		}

		element_sequence = element_sequence->NextSiblingElement();
	}

	for(size_t i = Layer::Layer_1; i < Layer::Layer_Max; ++i)
	{
		Layer* layer = m_layers[i];
		layer->Init(*this, static_cast<Layer::eLayer>(i));
	}

	delete buffer;
}

}