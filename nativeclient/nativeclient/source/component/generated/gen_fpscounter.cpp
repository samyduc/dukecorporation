// Generated file : do not edit manually 


#include "component/ui/fpscounter.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void FPSCounter::Clone(Entity* _entity, natU32 _type) const
{
	FPSCounter* component;
	natU32 base_type = FPSCounter::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<FPSCounter>();
	}
	else
	{
		component = static_cast<FPSCounter*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

}


void FPSCounter::WriteData(Serializer& _ser)
{
}


void FPSCounter::ReadData(Serializer& _ser)
{
}



}
