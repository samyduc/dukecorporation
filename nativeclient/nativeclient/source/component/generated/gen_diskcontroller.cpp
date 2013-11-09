// Generated file : do not edit manually 


#include "component/gameplay/diskcontroller.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"



namespace Natorium
{


void DiskController::Clone(Entity* _entity, ref_t _type) const
{
	DiskController* component;
	ref_t base_type = DiskController::GetType();
	if(_type == 0)
	{
		component = _entity->AddComponent<DiskController>();
	}
	else
	{
		component = static_cast<DiskController*>(_entity->GetComponentByType(_type));
		base_type = _type;
	}

}


void DiskController::WriteData(Serializer& _ser)
{
}


void DiskController::ReadData(Serializer& _ser)
{
}



}
