#include "component/squareshape.h"

#include "component/texturemanager.h"
#include "component/glrender.h"

#include "base/entity.h"
#include "base/kernel.h"
#include "base/layer.h"


namespace Natorium
{

SquareShape::SquareShape()
	: m_size(50.f, 50.f)
	, m_color(1.f, 1.f, 1.f, 1.f)
	, m_repeat(1.f)
	, m_isDirty(true)
	, m_textureRef(0)
{

}

void SquareShape::OnInit()
{
	if(m_textureRef)
	{
		TextureManager* texturemanager = GetEntity()->GetKernel()->GetLayer(Layer::s_LayerManager)->GetRootEntity()->GetComponent<TextureManager>();
		GLuint texture_id = texturemanager->Get(m_textureRef);

		GLRender* glrender = GetEntity()->GetComponent<GLRender>();
		glrender->SetTexture(texture_id);
	}

	SetSize(m_size);
	SetColor(m_color);

	if(m_repeat != 0.0f)
	{
		SetTextureCoordinate(m_repeat);
	}
	else
	{
		SetTextureCoordinate(m_uv);
	}
	
	SetIndices();

	m_isDirty = true;
}

void SquareShape::OnTick(natU64 _tick)
{
}

void SquareShape::SetSize(glm::vec2& _size)
{
	m_size = _size;

	// compute new array
	m_vertex[0] = -1*_size.x / 2.0f;
	m_vertex[1] = -1*_size.y / 2.0f;
	m_vertex[2] = 0.0f, 
	m_vertex[3] = 1.0f;

	m_vertex[4] = _size.x / 2.0f;
	m_vertex[5] = -1*_size.y / 2.0f;
	m_vertex[6] = 0.0f, 
	m_vertex[7] = 1.0f;

	m_vertex[8] = -1*_size.x / 2.0f;
	m_vertex[9] = _size.y / 2.0f;
	m_vertex[10] = 0.0f, 
	m_vertex[11] = 1.0f;

	m_vertex[12] = _size.x / 2.0f;
	m_vertex[13] = _size.y / 2.0f;
	m_vertex[14] = 0.0f, 
	m_vertex[15] = 1.0f;

	m_isDirty = true;
}

void SquareShape::SetColor(glm::vec4& _color)
{
	m_color = _color;

	m_vertex[16] = _color.r;
	m_vertex[17] = _color.g;
	m_vertex[18] = _color.b;
	m_vertex[19] = _color.a;

	m_vertex[20] = _color.r;
	m_vertex[21] = _color.g;
	m_vertex[22] = _color.b;
	m_vertex[23] = _color.a;

	m_vertex[24] = _color.r;
	m_vertex[25] = _color.g;
	m_vertex[26] = _color.b;
	m_vertex[27] = _color.a;

	m_vertex[28] = _color.r;
	m_vertex[29] = _color.g;
	m_vertex[30] = _color.b; 
	m_vertex[31] = _color.a;

	m_isDirty = true;
}

void SquareShape::SetAlpha(natF32 _alpha)
{
	m_vertex[19] = _alpha;
	m_vertex[23] = _alpha;
	m_vertex[27] = _alpha;
	m_vertex[21] = _alpha;

	m_isDirty = true;
}

void SquareShape::SetTextureCoordinate(natF32 _repeat)
{
	m_vertex[32] = 0.f;
	m_vertex[33] = 1.f - 0.f;

	m_vertex[34] = _repeat;
	m_vertex[35] = 1.0f - 0.f;

	m_vertex[36] = 0.f;
	m_vertex[37] = 1.0f - _repeat;

	m_vertex[38] = _repeat;
	m_vertex[39] = 1.0f - _repeat;

	m_isDirty= true;
}

void SquareShape::SetTextureCoordinate(glm::mat4x2& _uv)
{
	m_vertex[32] = _uv[0].x;
	m_vertex[33] = _uv[0].y;

	m_vertex[34] = _uv[1].x;
	m_vertex[35] = _uv[1].y;

	m_vertex[36] = _uv[2].x;
	m_vertex[37] = _uv[2].y;

	m_vertex[38] = _uv[3].x;
	m_vertex[39] = _uv[3].y;

	m_isDirty= true;
}

void SquareShape::SetIndices()
{
	m_indices[0] = 0;
	m_indices[1] = 1;
	m_indices[2] = 2;
	m_indices[3] = 2;
	m_indices[4] = 1;
	m_indices[5] = 3;

	m_isDirty= true;
}

natF32* SquareShape::GetVertex(size_t &_size)
{
	_size = sizeof(m_vertex);
	return m_vertex;
}

natU16* SquareShape::GetIndices(size_t &_size)
{
	_size = sizeof(m_indices);
	return m_indices;
}

void SquareShape::GetOffset(size_t& _vertexNumber, size_t& _indicesNumber, size_t& _color, size_t& _uv)
{
	_vertexNumber = 4;
	_indicesNumber = 6;
	_color = 4*4;
	_uv = 4*4*2;
}



}