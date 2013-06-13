#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#include <glm/glm.hpp>

namespace Natorium
{

static natU32 s_Camera = Hash::Compute("s_Camera");

class Camera : public Component
{
public:
					Camera();
	virtual			~Camera();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_Camera; }

	glm::vec3		GetPos();
	glm::vec3		GetDeg();
	glm::mat4		GetViewMatrix() { return m_viewMatrix; }
	glm::mat4		GetProjectionMatrix() { return m_projectionMatrix; }

	glm::vec2		GetPosWorldToScreen(const glm::vec3& _world);
	glm::vec3		GetPosScreenToWorld(const glm::vec2& _screen);

	void			ApplyEffectFollowMouse();

public:
	bool			m_effect_followMouse;
	natF32			m_efect_followMouseSmooth;

	glm::mat4		m_viewMatrix;
	glm::mat4		m_projectionMatrix;

	glm::vec2		m_resolution;

};




}