// Generated file : do not edit manually 


#include "component/charactercontroller.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void CharacterController::Clone(Entity* _entity, natU32 _type) const
{
	CharacterController* component;
	natU32 base_type = CharacterController::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<CharacterController>();
	}
	else
	{
		component = static_cast<CharacterController*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

}


void CharacterController::WriteData(Serializer& _ser)
{
}


void CharacterController::ReadData(Serializer& _ser)
{
}



}
