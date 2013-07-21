#include "component/gameplay/shotgunweapon.h"

#include "base/entity.h"

#include "base/component.h"
#include "component/transform.h"
#include "entity/bullet.h"

namespace Natorium
{

ShotgunWeapon::ShotgunWeapon()
	: m_radius(0.8f)
	, m_bullets(6)
{

}

ShotgunWeapon::~ShotgunWeapon()
{

}

void ShotgunWeapon::OnInit()
{
	m_max = m_bullets*10;
	
	BaseWeapon::OnInit();

}

void ShotgunWeapon::OnTick(const natU64 _dt)
{
	BaseWeapon::OnTick(_dt);
}

void ShotgunWeapon::OnDeInit()
{
	BaseWeapon::OnDeInit();
}

void ShotgunWeapon::ShootAt(glm::vec3 _pos)
{
	if(m_acc == 0)
	{
		m_acc += m_rateShot;

		natF32 baseAngle = (m_radius * 2.f) /  m_bullets;
		natF32 startAngle = -1.f * m_radius;

		for(size_t i = 0; i < m_bullets; ++i)
		{
			Entity* bullet = Spawn();

			Transform* transform = GetEntity()->GetComponent<Transform>();
			Shape* shape = GetEntity()->GetComponent<RigidBody>()->GetShape();
			Transform* bullet_transform = bullet->GetComponent<Transform>();
			bullet_transform->m_pos = transform->m_pos;
			bullet_transform->m_rad = transform->m_rad;

			bullet_transform->m_forward = _pos - transform->GetPos();
			bullet_transform->m_forward = glm::normalize(bullet_transform->m_forward);

			glm::vec3 rot = transform->GetRad();
			glm::vec3 dirBullet(0.f);
			dirBullet.x = glm::cos(startAngle + rot.z);
			dirBullet.y = glm::sin(startAngle + rot.z);
			bullet_transform->m_forward -= dirBullet;

			glm::vec2 size = shape->GetSize();
			bullet_transform->m_pos += bullet_transform->m_forward * glm::vec3(size/1.5f, 0.f);

			bullet->Reset();


			startAngle += baseAngle;
		}

	}
}







}