
#include "component/ui.h"

#include "base/entity.h"
#include "base/layer.h"
#include "base/kernel.h"

#include "component/glmanager.h"


#include "component/transform.h"

#include <cassert>

namespace Natorium
{


UI::UI()
	: m_scale(1.0f)
	, m_pos(0.0f)
	, m_rad(0.0f)
{

}

UI::~UI()
{
}

void UI::OnInit()
{
	m_glManager = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<GLManager>();
	m_transform = GetEntity()->GetComponent<Transform>();

	assert(m_glManager);
	assert(m_transform);
}

void UI::Clone(Entity* _entity) const
{
	UI* component = _entity->AddComponent<UI>();
	component->m_pos = m_pos;
	component->m_rad = m_rad;
	component->m_scale = m_scale;
}

void UI::OnTick(const natU64 _dt)
{
	// patch transform
	Camera* camera = m_glManager->GetCamera();
	glm::vec2 resolution = m_glManager->GetScreenResolution();

	glm::vec2 screen_ratio = m_pos * resolution;

	m_transform->m_pos = camera->GetPosScreenToWorld(screen_ratio);
}

void UI::OnDeInit()
{
	m_glManager = nullptr;
	m_transform = nullptr;
}





}