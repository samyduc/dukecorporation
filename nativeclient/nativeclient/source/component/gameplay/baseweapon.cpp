#include "component/gameplay/baseweapon.h"

#include "base/kernel.h"
#include "base/entity.h"
#include "base/component.h"
#include "component/transform.h"
#include "entity/bullet.h"

#include "component/gameplay/lifecontroller.h"

namespace Natorium
{

BaseWeapon::BaseWeapon()
	: m_rateShot(400)
{
}

BaseWeapon::~BaseWeapon()
{
}

void BaseWeapon::OnInit()
{
	m_acc = 0;

	if(m_refEntity == nullptr)
	{
		// default bullet
		m_refEntity = new Bullet();

		// TODO : this must be done as a public parameter
		BulletController* bullet_controller = m_refEntity->GetComponent<BulletController>();
		bullet_controller->m_damage = 3;

		RigidBody* bullet_rigidbody = m_refEntity->GetComponent<RigidBody>();
		bullet_rigidbody->m_isBullet = true;
		bullet_rigidbody->m_isDynamic = true;
		bullet_rigidbody->m_maxSpeed = 100.f;
		bullet_rigidbody->m_density = 0.f;
	}

	Spawner::OnInit();
}

void BaseWeapon::Clone(Entity* _entity) const
{
	BaseWeapon* component = _entity->AddComponent<BaseWeapon>();
	component->m_rateShot = m_rateShot;
	component->m_max = m_max;
	component->m_refEntity = m_refEntity;
}


void BaseWeapon::OnTick(const natU64 _dt)
{
	Spawner::OnTick(_dt);

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
	Spawner::OnDeInit();
}

void BaseWeapon::ShootAt(glm::vec3 _pos)
{
	if(m_acc == 0)
	{
		m_acc += m_rateShot;

		Entity* bullet = Spawn();

		Transform* transform = GetEntity()->GetComponent<Transform>();
		Shape* shape = GetEntity()->GetComponent<Shape>();
		Transform* bullet_transform = bullet->GetComponent<Transform>();
		bullet_transform->m_pos = transform->m_pos;
		bullet_transform->m_rad = transform->m_rad;

		bullet_transform->m_forward = _pos - transform->GetPos();
		bullet_transform->m_forward = glm::normalize(bullet_transform->m_forward);

		glm::vec2 size = shape->GetSize();
		bullet_transform->m_pos += bullet_transform->m_forward * glm::vec3(size, 0.f);

		bullet->Reset();
	}
}

void BaseWeapon::OnHit(Contact* _contact)
{
	Entity* A = static_cast<Entity*>(_contact->A->GetBody()->GetUserData());
	Entity* B = static_cast<Entity*>(_contact->B->GetBody()->GetUserData());

	Entity* bullet;
	Entity* hit;

	if(A->GetComponent<BulletController>())
	{
		bullet = A;
		hit = B;
	}
	else
	{
		bullet = B;
		hit = A;
	}

	LifeController* life_controller = hit->GetComponent<LifeController>();
	if(life_controller)
	{
		BulletController *bullet_controler = bullet->GetComponent<BulletController>();
		life_controller->TakeDamage(bullet_controler->m_damage);
	}

	OnKilled(bullet);
}

}