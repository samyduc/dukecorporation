#include "component/gameplay/baseweapon.h"

#include "base/kernel.h"
#include "base/entity.h"
#include "base/component.h"
#include "component/transform.h"
#include "entity/bullet.h"

#include "component/prefabmanager.h"
#include "component/gameplay/lifecontroller.h"

#include <cassert>

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
	assert(m_prefabType);

	m_acc = 0;

	if(m_refEntity == nullptr)
	{
		// default bullet
		//PrefabManager* prefabmanager = GetEntity()->GetKernel()->GetLayer(Layer::s_LayerManager)->GetRootEntity()->GetComponent<PrefabManager>();
		//m_refEntity = prefabmanager->CreateFromType(m_prefabType);

		// TODO : this must be done as a public parameter
		/*BulletController* bullet_controller = m_refEntity->GetComponent<BulletController>();
		assert(bullet_controller);

		bullet_controller->m_damage = 3;

		RigidBody* bullet_rigidbody = m_refEntity->GetComponent<RigidBody>();
		bullet_rigidbody->m_isBullet = true;
		bullet_rigidbody->m_isDynamic = true;
		bullet_rigidbody->m_maxSpeed = 100.f;
		bullet_rigidbody->m_density = 0.f;*/
	}

	Spawner::OnInit();
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
	// TODO : Samy : refactor to not use m_forward
	if(m_acc == 0)
	{
		m_acc += m_rateShot;

		Entity* bullet = Spawn();

		Transform* transform = GetEntity()->GetComponent<Transform>();
		Shape* shape = GetEntity()->GetComponent<RigidBody>()->GetShape();
		Transform* bullet_transform = bullet->GetComponent<Transform>();
		bullet_transform->m_pos = transform->m_pos;
		bullet_transform->m_rot = transform->m_rot;

		glm::vec2 size = shape->GetSize();
		//bullet_transform->m_pos += bullet_transform->m_forward * glm::vec3(size, 0.f);

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