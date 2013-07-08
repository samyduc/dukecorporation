#include "component/textshape.h"

#include "base/entity.h"

#include "component/fontmanager.h"
#include "component/glrender.h"

namespace Natorium
{

TextShape::TextShape()
	: m_color(1.f, 1.f, 1.f, 1.f)
	, m_vertex(nullptr)
	, m_indices(nullptr)
	, m_isDirty(true)
	, m_vertexNumber(0)
	, m_bufferAllocated(0){

}

void TextShape::OnInit()
{
	SetText(m_text, m_font);

	m_isDirty = true;
}

void TextShape::OnDeInit()
{
	if(m_vertex)
	{
		delete [] m_vertex;
		m_vertex = nullptr;
	}
	if(m_indices)
	{
		delete [] m_indices;
		m_indices = nullptr;
	}
	m_bufferAllocated = 0;
}

void TextShape::Clone(Entity* _entity) const
{
	TextShape* component = _entity->AddComponent<TextShape>();
	component->m_color = m_color;
	component->m_font = m_font;
	component->m_text = m_text;
}

void TextShape::SetText(std::string& _text, Font* _font)
{
	if(_font == nullptr)
	{
		assert(m_font);
		_font = m_font;
	}

	natBool doAllocate = false;

	if(_text.size() > m_bufferAllocated)
	{
		doAllocate = true;
	}

	m_text = _text;
	m_font = _font;

	size_t text_size = m_text.size();

	size_t vertex_size = text_size * 4 * 4;
	size_t color_size = text_size * 4 * 4;
	size_t uv_size = text_size * 4 * 2;

	m_colorOffset = vertex_size;
	m_uvOffset = vertex_size + color_size;

	m_vertexNumber = static_cast<natU32>(text_size * 4);
	m_indicesNumber = (m_vertexNumber / 4) * 6;
	m_length = vertex_size + color_size + uv_size;


	if(doAllocate)
	{
		if(m_vertex)
		{
			delete [] m_vertex;
			m_vertex = nullptr;
		}
		if(m_indices)
		{
			delete [] m_indices;
			m_indices = nullptr;
		}

		assert(m_vertex == nullptr);
		assert(m_indices == nullptr);
		m_vertex = new natF32[m_length];
		m_indices = new natU32[m_indicesNumber];

		m_bufferAllocated = m_text.size();
	}

	assert(m_vertex);
	assert(m_indices);
	
	//memset(m_vertex, 0, m_length);

	for(size_t index=0; index < m_length; ++index)
	{
		m_vertex[index] = 0.f;
	}

	natU32 advance = 0;
	natU32 i = 0;
	std::string::iterator c = m_text.begin();
	std::string::iterator const tmp_end = m_text.end();
 
	Font::char_info_t* ci;

	// Fill vertex data
	for(; c != tmp_end; ++c)
	{
		ci = &m_font->m_info.ch[*c];

		m_vertex[i+0] = ci->left+advance+ci->v[1].x;
		m_vertex[i+1] = ci->v[1].y + (m_font->m_info.max_height-ci->top);

		m_vertex[i+4] = ci->left+advance+ci->v[2].x;
		m_vertex[i+5] = ci->v[2].y + (m_font->m_info.max_height-ci->top);

		m_vertex[i+8] = ci->left+advance+ci->v[0].x;
		m_vertex[i+9] = ci->v[0].y + (m_font->m_info.max_height-ci->top);

		m_vertex[i+12] = ci->left+advance+ci->v[3].x;
		m_vertex[i+13] = ci->v[3].y + (m_font->m_info.max_height-ci->top);

		m_vertex[i+3] = 1.f;
		m_vertex[i+7] = 1.f;
		m_vertex[i+11] = 1.f;
		m_vertex[i+15] = 1.f;
 
		advance += ci->advance;
		i+=(4*4);

		m_size.x += static_cast<natF32>(ci->width);
		m_size.y = static_cast<natF32>(ci->height);
	}

	// Fill UV data
	natF32* uv = m_vertex + vertex_size + color_size;
	i = 0;
	c = m_text.begin();
	for(; c != tmp_end; ++c)
	{
		ci = &m_font->m_info.ch[*c];

		uv[i+0] = ci->uv[1].x;
		uv[i+1] = ci->uv[1].y;

		uv[i+2] = ci->uv[2].x;
		uv[i+3] = ci->uv[2].y;

		uv[i+4] = ci->uv[0].x;
		uv[i+5] = ci->uv[0].y;

		uv[i+6] = ci->uv[3].x;
		uv[i+7] = ci->uv[3].y;
 
		i+=(4*2);
	}

	SetColor(m_color);
	SetIndices();

	m_isDirty = true;
}

void TextShape::SetIndices()
{
	assert(m_indices);

	natU32 index = 0;
	for(size_t i = 0; i < m_indicesNumber/6; ++i)
	{
		m_indices[i*6 + 0] = index + 0;
		m_indices[i*6 + 1] = index + 1;
		m_indices[i*6 + 2] = index + 2;
		m_indices[i*6 + 3] = index + 2;
		m_indices[i*6 + 4] = index + 1;
		m_indices[i*6 + 5] = index + 3;

		index += 4;
	}
}

void TextShape::SetSize(glm::vec2& _size)
{
	// cannot change dynamically the size for the moment
	assert(false);
}

void TextShape::SetColor(glm::vec4& _color)
{
	m_color = _color;

	assert(m_vertex != nullptr);

	size_t text_size = m_text.size();

	size_t vertex_size = text_size * 4 * 4;
	size_t color_size = text_size * 4 * 4;
	
	natF32* color = m_vertex + vertex_size;

	natU32 i = 0;
	std::string::iterator c = m_text.begin();
	std::string::iterator const tmp_end = m_text.end();

	for(; c != tmp_end; ++c)
	{
		for(natU32 j = 0; j < 4*4; j=j+4)
		{
			color[i+j+0] = _color.r;
			color[i+j+1] = _color.g;
			color[i+j+2] = _color.b;
			color[i+j+3] = _color.a;
		}

		i+=(4*4);
	}

	m_isDirty = true;
}

void TextShape::SetAlpha(natF32 _alpha)
{
	// not implemented because of lazyness
	assert(false);
	/*m_vertex[19] = _alpha;
	m_vertex[23] = _alpha;
	m_vertex[27] = _alpha;
	m_vertex[21] = _alpha;*/

	m_isDirty = true;
}


natF32* TextShape::GetVertex(size_t &_size)
{
	assert(m_vertex != nullptr);
	_size = m_length*sizeof(natF32);
	return m_vertex;
}

natU32* TextShape::GetIndices(size_t &_size)
{
	assert(m_indices != nullptr);
	_size = m_indicesNumber * sizeof(natU32);
	return m_indices;
}

void TextShape::GetOffset(size_t& _vertexNumber, size_t& _indicesNumber, size_t& _color, size_t& _uv)
{
	_vertexNumber = m_vertexNumber;
	_indicesNumber = m_indicesNumber;
	_color = m_colorOffset;
	_uv = m_uvOffset;
}

}