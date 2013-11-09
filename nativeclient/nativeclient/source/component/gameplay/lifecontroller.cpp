#include "component/gameplay/lifecontroller.h"

#include "base/entity.h"
#include "base/kernel.h"

#include "component/shape.h"
#include "component/rigidbody.h"
#include "component/SquareShape.h"
#include "component/texturemanager.h"
#include "component/GLRender.h"

namespace Natorium
{

LifeController::LifeController()
	: m_life(10)
	, m_currentLife(0)
	, m_smallDamageTexture(0)
	, m_BigDamageTexture(0)
{
}

LifeController::~LifeController()
{
	
}

void LifeController::OnInit()
{
	m_currentLife = m_life;
}

void LifeController::OnTick(const natU64 _dt)
{
}

void LifeController::OnDeInit()
{
}

void LifeController::TakeDamage(natS32 _damage)
{
	m_currentLife -= _damage;

	if(m_currentLife < 2*m_life/3){
		ref_t textureRef = m_smallDamageTexture;
		if(m_currentLife < m_life/3){
			textureRef = m_BigDamageTexture;
		}

		//TextureManager* texturemanager = GetEntity()->GetKernel()->GetLayer(Layer::s_LayerManager)->GetRootEntity()->GetComponent<TextureManager>();
		//GLuint texture_id = texturemanager->Get(textureRef);

		//GLRender* glrender = GetEntity()->GetComponent<GLRender>();
		//glrender->SetTexture(texture_id);

	}

	
	
}



}