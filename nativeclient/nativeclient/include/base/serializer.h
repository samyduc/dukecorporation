#pragma once

#include "base/natdef.h"

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

//#include <algorithm>
#include <assert.h>

namespace Natorium
{

enum eSerializerState
{
	E_IDLE,
	E_WRITE,
	E_READ
};

// we are little endian
static const natS32		s_OrderedInt		= 0x01020304;
static const natS8		*s_orderedChar		= reinterpret_cast<const natS8*>(&s_OrderedInt);
static const natBool	s_IsBigEndian		= s_orderedChar[0] == 0x01;

static const natU32		s_header_pos_length	= 0;
static const natU32		s_header_pos_type	= s_header_pos_length + sizeof(natU32);
static const natU32		s_header_pos		= s_header_pos_length + s_header_pos_type + sizeof(natU32);


class Serializer
{
public:

	explicit		Serializer(size_t);
	explicit		Serializer(const Serializer&);
	virtual			~Serializer();

	static size_t   GetHeaderSize() { return s_header_pos; }

	size_t			GetSize() const;
	natU32			GetType() const;
	size_t			GetBufferSize() const { return m_buffer_size; }
	const natU8*	GetBuffer() const { return m_buffer; }
	natU8*			GetRawBuffer() const { return m_buffer; }
	void			SetCursor(size_t _pos);
	size_t			GetCursor() const { return m_cursor_pos; }
	void			ResetCursor();

	void			Copy(const natU8* const _copy, size_t _copy_size);

	natBool			Write(natU32 _type);
	natBool			Write(const natChar* _type);

	natBool			Read(natU32 _type);
	natBool			Read(const natChar* _type);

	void			Close();

	virtual Serializer&	operator=(const Serializer &_copy);

	Serializer& operator <<(natBool);
	Serializer& operator <<(natU8);
	Serializer& operator <<(natS8);
	Serializer& operator <<(natChar);
	Serializer& operator <<(natU16);
	Serializer& operator <<(natS16);
	Serializer& operator <<(natU32);
	Serializer& operator <<(natS32);
	Serializer& operator <<(natU64);
	Serializer& operator <<(natS64);
	Serializer& operator <<(natF32);
	Serializer& operator <<(natF64);
	Serializer& operator <<(const Serializer&);

	Serializer& operator >>(natBool&);
	Serializer& operator >>(natU8&);
	Serializer& operator >>(natS8&);
	Serializer& operator >>(natChar&);
	Serializer& operator >>(natU16&);
	Serializer& operator >>(natS16&);
	Serializer& operator >>(natU32&);
	Serializer& operator >>(natS32&);
	Serializer& operator >>(natU64&);
	Serializer& operator >>(natS64&);
	Serializer& operator >>(natF32&);
	Serializer& operator >>(natF64&);
	Serializer& operator >>(Serializer&);

	// helpers
	Serializer& operator <<(const std::string&);
	Serializer& operator <<(const glm::vec2&);
	Serializer& operator <<(const glm::vec3&);
	Serializer& operator <<(const glm::vec4&);
	Serializer& operator <<(const glm::mat4&);
	Serializer& operator <<(const glm::quat&);

	Serializer& operator >>(std::string&);
	Serializer& operator >>(glm::vec2&);
	Serializer& operator >>(glm::vec3&);
	Serializer& operator >>(glm::vec4&);
	Serializer& operator >>(glm::mat4&);
	Serializer& operator >>(glm::quat&);

	// ref counting
	virtual void		IncRef() { ++m_ref_nb; }
	virtual void		DecRef() { assert(m_ref_nb > 0); --m_ref_nb; /*if(m_ref_nb == 0) delete this;*/}
	virtual size_t		GetRef() { return m_ref_nb; }

	virtual Serializer*	GetSerializer() { return this; }

public:
	const static size_t MTU = 1400;


protected:
			Serializer();
	void	SetRef(Serializer* _ref);

protected:

	eSerializerState	m_state;
	natU8*				m_buffer;
	natBool				m_owner;

	size_t				m_buffer_size;
	size_t				m_cursor_pos;

	size_t				m_ref_nb;

};

}