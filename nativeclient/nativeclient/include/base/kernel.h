#pragma once

#include "base/natdef.h"
#include "base/timeplatform.h"
#include "base/entity.h"
#include "base/layer.h"

#include "entity/root.h"

#include <vector>

namespace Natorium
{

typedef std::vector<Layer*> layers_t;

class Kernel
{
public:

					Kernel();
					~Kernel();

	void			Init();
	void			Tick();
	void			DeInit();

	natU64			GetUniqueId();

	void			AddEntity(Layer::eLayer _layer, Entity* _entity, Entity* _parent=nullptr);
	void			RemoveEntity(Entity* _entity);

	Layer*			GetLayer(Layer::eLayer _layer) { return m_layers[_layer]; }

	void			BootLoader(const natChar* _path);

	natBool			IsReady() const { return m_isReady; }
	natBool			IsRunning() const { return !m_isShutdown; }

	void			SetShutdown() { m_isShutdown = true;} 

private:
	natBool			m_isReady;
	natBool			m_isShutdown;
	natU64			m_acc;
	natU64			m_rateStep;
	
	layers_t		m_layers;

	timer_t			m_currentTime;
	natU64			m_currentId;


};




}