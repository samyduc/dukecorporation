
#include "component/ui/fpscounter.h"

#include "component/glmanager.h"
#include "component/textshape.h"

#include "base/entity.h"
#include "base/layer.h"
#include "base/kernel.h"

#include <glm/glm.hpp>

#include <string>
#include <sstream>

namespace Natorium
{


FPSCounter::FPSCounter()
{

}

FPSCounter::~FPSCounter()
{
}

void FPSCounter::OnInit()
{
	m_glManager = GetEntity()->GetKernel()->GetLayer(Layer::s_LayerManager)->GetRootEntity()->GetComponent<GLManager>();
	assert(m_glManager);
}

void FPSCounter::OnTick(const natU64 _dt)
{
	// get info
	natU64 tick = m_glManager->GetLastTick();
	m_fps = static_cast<natU64>(glm::round((1.f / tick)*1000));

	// display
	TextShape* shape = GetEntity()->GetComponent<TextShape>();

	if(shape)
	{
		std::ostringstream oss;
		oss << m_fps;

		std::string text = oss.str();
		shape->SetText(text);
	}
}

void FPSCounter::OnDeInit()
{
	m_glManager = nullptr;
}





}