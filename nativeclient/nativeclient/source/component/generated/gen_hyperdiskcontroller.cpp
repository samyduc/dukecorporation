// Generated file : do not edit manually 


#include "component/gameplay/hyperdiskcontroller.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void HyperdiskController::Clone(Entity* _entity, ref_t _type) const
{
	HyperdiskController* component;
	ref_t base_type = HyperdiskController::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<HyperdiskController>();
	}
	else
	{
		component = static_cast<HyperdiskController*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

}


void HyperdiskController::WriteData(Serializer& _ser)
{
}


void HyperdiskController::ReadData(Serializer& _ser)
{
}



}
