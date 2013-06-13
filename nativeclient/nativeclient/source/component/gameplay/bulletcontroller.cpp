#include "component/gameplay/bulletcontroller.h"

#include "base/entity.h"
#include "base/component.h"
#include "component/transform.h"

namespace Natorium
{

BulletController::BulletController()
{
}

BulletController::~BulletController()
{
}

void BulletController::OnInit()
{

}

void BulletController::OnDeInit()
{

}

void BulletController::OnTick(const natU64 _dt)
{
	Transform* transform = GetEntity()->GetComponent<Transform>();

	transform->m_pos += static_cast<natF32>(_dt) * transform->m_forward;
}


}