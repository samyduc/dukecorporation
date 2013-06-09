#include "component/glrender.h"
#include "base/entity.h"
#include "base/layer.h"
#include "base/kernel.h"

#include "component/glmanager.h"
#include "component/transform.h"

#include <assert.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
	GLManager* glmanager = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<GLManager>();
	m_shaderProgram = glmanager->GetShaderProgram();

	m_modelUnif = glGetUniformLocation(m_shaderProgram, "model");
	glGenBuffers(1, &m_bufferObject);
	//m_globalUnifBlockIndex = glGetUniformBlockIndex(m_shaderProgram, "GlobalMatrices");

	//glUniformBlockBinding(m_shaderProgram, m_globalUnifBlockIndex, glmanager->GetGlobalBindingIndex());
}

void GLRender::OnTick(const natU64 _dt)
{
	Transform* transform = GetEntity()->GetComponent<Transform>();
	GLManager* glmanager = GetEntity()->GetComponent<GLManager>();

	transform->m_pos.x = 400;
	transform->m_pos.y = 200;

	/*glPushMatrix();

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

	glPopMatrix();*/

	// store positions
	GLfloat vertexPositions[] = {
		-100.0f, -100.0f, 0.0f, 1.0f,
		100.f, -100.f, 0.f, 1.f,
		-100.f, 100.f, 0.f, 1.f,
		100.f, 100.f, 0.f, 1.f,

		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f
	};

	size_t vectorLength = sizeof(vertexPositions);

	glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject);
	glBufferData(GL_ARRAY_BUFFER, vectorLength, vertexPositions, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// draw
	glUseProgram(m_shaderProgram);

	// to refactor translation
	glm::vec3 position = transform->GetPos();
	glm::mat4 transMat(1.f);
	transMat = glm::translate(transMat, position);

	glm::vec3 angle = transform->GetDeg();
	transMat = glm::rotate(transMat, angle.z, glm::vec3(0, 0, 1));

	glUniformMatrix4fv(m_modelUnif, 1, GL_FALSE, glm::value_ptr(transMat));
	
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);


	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float)*16));
	////////

	// call to draw
	//glDrawArrays(GL_QUADS, 0, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	//glDrawArrays(GL_POINTS, 0, 4);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glUseProgram(0);

}

void GLRender::OnDeInit()
{
	glDeleteBuffers(1, &m_bufferObject);
}

}