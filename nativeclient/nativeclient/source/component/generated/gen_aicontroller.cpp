// Generated file : do not edit manually 


#include "component/gameplay/aicontroller.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void AiController::Clone(Entity* _entity, natU32 _type) const
{
	AiController* component;
	natU32 base_type = AiController::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<AiController>();
	}
	else
	{
		component = static_cast<AiController*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

}


void AiController::WriteData(Serializer& _ser)
{
}


void AiController::ReadData(Serializer& _ser)
{
}



}
