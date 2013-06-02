#include "component/glrender.h"
#include "base/entity.h"
#include "base/layer.h"
#include "base/kernel.h"

#include "component/transform.h"

#include <assert.h>

namespace Natorium
{

GLRender::GLRender()
{

}

GLRender::~GLRender()
{
}

void GLRender::OnInit()
{

}

void GLRender::OnTick(natU64 _dt)
{
	Transform* transform = GetEntity()->GetComponent<Transform>();

	transform->m_pos.x = 400;
	transform->m_pos.y = 200;

	glPushMatrix();

	glTranslatef(transform->m_pos.x, transform->m_pos.y, transform->m_pos.z);

	glm::vec3 deg = transform->GetDeg();
	glRotatef(deg.x, 1, 0, 0);
	glRotatef(deg.y, 0, 1, 0);
	glRotatef(deg.z, 0, 0, 1);

	glScalef(transform->m_scale.x, transform->m_scale.y, transform->m_scale.z);

	glBegin(GL_QUADS);
		glColor4f(1.0, 0.0, 0.0, 1.0);
		glVertex3f(-100,-100,0);
		glVertex3f(100,-100,0);
		glVertex3f(100,100,0);
		glVertex3f(-100,100,0);
	glEnd();

	glPopMatrix();
}

void GLRender::OnDeInit()
{

}

}