#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include <glm/glm.hpp>

namespace Natorium
{

static natU32 s_Camera = Hash::Compute("Camera");

class Camera : public Component
{
public:
					Camera();
	virtual			~Camera();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_Camera; }

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

	glm::vec3		GetPos();
	glm::vec3		GetDeg();
	glm::mat4		GetViewMatrix() { return m_viewMatrix; }
	glm::mat4		GetProjectionMatrix() { return m_projectionMatrix; }

	glm::vec2		GetPosWorldToScreen(const glm::vec3& _world);
	glm::vec3		GetPosScreenToWorld(const glm::vec2& _screen);

	void			ComputeMatrix();

	void			ApplyEffectFollowMouse();

public:
	natBool			m_effect_followMouse;
	natF32			m_efect_followMouseSmooth;

	glm::mat4		m_viewMatrix;
	glm::mat4		m_projectionMatrix;

	glm::vec2		m_resolution;

};




}