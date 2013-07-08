
#include "component/ui.h"

#include "base/entity.h"

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

}

void UI::OnDeInit()
{
}





}