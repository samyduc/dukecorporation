#include "component/gameplay/baseweapon.h"

#include "base/kernel.h"
#include "base/entity.h"
#include "base/component.h"
#include "component/transform.h"


#include "entity/bullet.h"

#include "base/timeplatform.h"

namespace Natorium
{

BaseWeapon::BaseWeapon()
{
}

BaseWeapon::~BaseWeapon()
{
}

void BaseWeapon::OnInit()
{
	m_acc = 0;
	m_rateShot = 200;
	m_cursor = 0;

	// preallocatebullet
	for(size_t i = 0; i < 200; ++i)
	{
		Bullet* bullet = new Bullet();
		// TODO : hardcore but must work
		GetEntity()->GetKernel()->AddEntity(Layer::Layer_4, bullet);
		bullet->SetEnabled(false);
		m_bullets.push_back(bullet);
	}
}

void BaseWeapon::OnTick(const natU64 _dt)
{
	if(m_acc && m_acc > _dt)
	{
		m_acc -= _dt;
	}
	else
	{
		m_acc = 0;
	}
}

void BaseWeapon::OnDeInit()
{

}

void BaseWeapon::ShootAt(glm::vec3 _pos)
{
	if(m_acc == 0)
	{
		m_acc += m_rateShot;

		Bullet* bullet = m_bullets[m_cursor];

		Transform* transform = GetEntity()->GetComponent<Transform>();
		Transform* bullet_transform = bullet->GetComponent<Transform>();
		bullet_transform->m_pos = transform->m_pos;
		bullet_transform->m_rad = transform->m_rad;

		bullet_transform->m_forward = _pos - transform->GetPos();
		bullet_transform->m_forward = glm::normalize(bullet_transform->m_forward);
		
		bullet->SetEnabled(true);

		if(m_cursor + 1 >= m_bullets.size())
		{
			m_cursor = 0;
		}
		else
		{
			++m_cursor;
		}
	}
}


}