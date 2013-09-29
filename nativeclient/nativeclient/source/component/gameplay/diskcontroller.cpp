#include "component/gameplay/diskcontroller.h"

#include "base/entity.h"
#include "base/component.h"

#include "component/transform.h"
#include "component/shape.h"
#include "component/rigidbody.h"

#include <assert.h>

namespace Natorium
{

DiskController::DiskController()
{
}

DiskController::~DiskController()
{
}

void DiskController::OnInit()
{
}

void DiskController::OnDeInit()
{

}

void DiskController::OnTick(const natU64 _dt)
{
	
}

void DiskController::OnEnterCollide(Contact* _contact)
{
	
}

void DiskController::ShootAt(glm::vec3 _pos)
{
	Transform* transform = GetEntity()->GetComponent<Transform>();
	RigidBody* rigidbody = GetEntity()->GetComponent<RigidBody>();
	
	transform->m_pos = transform->m_pos;
	transform->m_rot = transform->m_rot;

	glm::vec3 impulse = _pos - transform->m_pos;
	impulse *= 100.f;

	rigidbody->ApplyLinearImpulse(impulse);
	

}

}