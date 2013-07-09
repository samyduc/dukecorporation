#include "component/glrender.h"
#include "base/entity.h"
#include "base/layer.h"
#include "base/kernel.h"


#include "component/transform.h"

#include "component/shape.h"

#include <assert.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Natorium
{

const natU32 programPosition = Hash::Compute("position");

GLRender::GLRender()
	: m_shape(nullptr)
	, m_type(programPosition)
	, m_vertexNumber(0)
{

}

GLRender::~GLRender()
{
}

void GLRender::OnInit()
{
	m_shape = GetEntity()->GetComponent<Shape>();
	assert(m_shape);

	GLManager* glmanager = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<GLManager>();
	//m_shaderProgram = glmanager->GetShaderProgram();
	m_renderList = glmanager->GetRenderList(m_type);

	//m_modelUnif = glGetUniformLocation(m_shaderProgram, "model");
	glGenBuffers(1, &m_bufferObject);
	glGenBuffers(1, &m_indicesBuffer);
	//m_globalUnifBlockIndex = glGetUniformBlockIndex(m_shaderProgram, "GlobalMatrices");

	//glUniformBlockBinding(m_shaderProgram, m_globalUnifBlockIndex, glmanager->GetGlobalBindingIndex());

	GLuint program = glmanager->GetProgram(m_type);
	m_modelUnif = glGetUniformLocation(program, "model");
}

void GLRender::Clone(Entity* _entity) const
{
	GLRender* component = _entity->AddComponent<GLRender>();
	component->m_type = m_type;
}

void GLRender::OnTick(const natU64 _dt)
{
	m_renderList->push_back(this);

	Transform* transform = GetEntity()->GetComponent<Transform>();

	glm::vec3 position = transform->GetPos();
	glm::mat4 transMat(1.f);
	transMat = glm::translate(transMat, position);

	glm::vec3 angle = transform->GetDeg();
	m_transMat = glm::rotate(transMat, angle.z, glm::vec3(0, 0, 1));

	if(m_shape->IsAndRemoveDirty())
	{
		size_t vectorLength;
		natF32 *vertexPositions = m_shape->GetVertex(vectorLength);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject);
		glBufferData(GL_ARRAY_BUFFER, vectorLength, vertexPositions, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		m_shape->GetOffset(m_vertexNumber, m_indicesNumber, m_colorOffset, m_uvOffset);

		size_t indicesLength;
		natU32 *indicesPositions = m_shape->GetIndices(indicesLength);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesLength, indicesPositions, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

void GLRender::PreRender(natU64 _tick)
{

}

void GLRender::Render(GLuint _program)
{
	glUniformMatrix4fv(m_modelUnif, 1, GL_FALSE, glm::value_ptr(m_transMat));
	
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesBuffer);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);


	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(natF32)*m_colorOffset));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(natF32)*m_uvOffset));
	////////

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D , m_texture);

	// call to draw
	//glDrawArrays(GL_TRIANGLES, 0, static_cast<natU32>(m_vertexNumber));
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, static_cast<natU32>(m_vertexNumber));
	glDrawElements(GL_TRIANGLES, static_cast<natU32>(m_indicesNumber), GL_UNSIGNED_INT, (void*)0);

	glBindTexture(GL_TEXTURE_2D , 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(3);
}

void GLRender::OnDeInit()
{
	glDeleteBuffers(1, &m_bufferObject);
}

}