#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include <Box2D/Box2D.h>

#include <glm/glm.hpp>
#include <assert.h>

namespace Natorium
{

class Transform;
class Shape;

static natU32 s_RigidBody = Hash::Compute("s_RigidBody");

static natF32 s_B2RatioPos = 10.f;


class RigidBody : public Component
{
public:
					RigidBody();
	virtual			~RigidBody();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	virtual void	OnEnable();
	virtual void	OnDisable();

	static natU32	GetType() { return s_RigidBody; }

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

	void			SetFriction(natF32 _friction) { assert(m_b2Fixture); m_b2Fixture->SetFriction(_friction); }

	void			ApplyLinearImpulse(glm::vec3& _impulse);

	void			SetDensity(natF32 _density) { assert(m_b2Fixture); m_density = _density; m_b2Fixture->SetDensity(_density); m_b2Body->ResetMassData(); }
	void			SetAngle(glm::vec3& _angle) { assert(m_b2Body); m_b2Body->SetTransform(m_b2Body->GetPosition(), _angle.z); }

	Shape*			GetShape() { return m_shape; }

public:
	natBool			m_isDynamic;
	natBool			m_isBullet;
	natF32			m_maxSpeed;
	natF32			m_density;
	natU32			m_shapeType;

protected:
	Transform*		m_transform;
	Shape*			m_shape;
	b2World*		m_b2World;
	b2BodyDef		m_b2BodyDef;
	b2PolygonShape	m_b2Shape;
	b2Fixture*		m_b2Fixture;
	b2Body*			m_b2Body;
};




}