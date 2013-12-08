// Generated file : do not edit manually 


#include "component/netdukemanager.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void NetDukeManager::Clone(Entity* _entity, ref_t _type) const
{
	NetDukeManager* component;
	ref_t base_type = NetDukeManager::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<NetDukeManager>();
	}
	else
	{
		component = static_cast<NetDukeManager*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

	component->m_isTCP = m_isTCP;
	component->m_listeningPort = m_listeningPort;
}


void NetDukeManager::WriteData(Serializer& _ser)
{
	_ser << m_isTCP;
	_ser << m_listeningPort;
}


void NetDukeManager::ReadData(Serializer& _ser)
{
	_ser >> m_isTCP;
	_ser >> m_listeningPort;
}



}
