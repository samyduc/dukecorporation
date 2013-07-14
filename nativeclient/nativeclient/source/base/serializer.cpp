#include "base/serializer.h"
#include "base/hash.h"


// memcpy
#include <cstring>


#if defined(_MSC_VER)
	#include <stdlib.h> // _byteswap_XX
#endif

namespace Natorium
{

#ifdef _MSC_VER
	#define SWAP_16(x) _byteswap_ushort(x)
	#define SWAP_32(x) _byteswap_ulong(x)
	#define SWAP_64(x) _byteswap_uint64(x)
#else
	#define SWAP_16(x) ((x & 0xFF00) >> 8 | (x & 0x00FF) << 8)

	#define SWAP_32(x) (((x & 0xFF000000) >> 24)| \
					   ((x & 0x00FF0000) >>  8) | \
					   ((x & 0x0000FF00) <<  8) | \
					   ((x & 0x000000FF) << 24)) 

	#define SWAP_64(x)	(((x & 0x00000000000000FF) << 56) | \
						((x &  0x000000000000FF00) << 40) | \
						((x &  0x0000000000FF0000) << 24) | \
						((x &  0x00000000FF000000) << 8) | \
						((x &  0x000000FF00000000) >> 8) | \
						((x &  0x0000FF0000000000) >> 24)| \
						((x &  0x00FF000000000000) >> 40)| \
						((x &  0xFF00000000000000) >> 56))

#endif

// use only with inherited class
Serializer::Serializer()
	: m_cursor_pos(0)
	, m_buffer_size(0)
	, m_state(E_IDLE)
	, m_buffer(nullptr)
	, m_owner(false)
	, m_ref_nb(0)
{
}

Serializer::Serializer(size_t size)
	: m_cursor_pos(0)
	, m_buffer_size(size)
	, m_state(E_IDLE)
	, m_owner(true)
	, m_ref_nb(0)
{
	m_buffer = new natU8[size];
}

Serializer::Serializer(const Serializer& _serializer)
	: m_cursor_pos(0)
	, m_buffer_size(_serializer.GetSize())
	, m_state(E_IDLE)
	, m_owner(true)
	, m_ref_nb(0)
{
	m_buffer = new natU8[_serializer.GetSize()];

	Copy(_serializer.m_buffer, _serializer.GetSize());
}

Serializer::~Serializer()
{
	if(m_owner)
	{
		assert(m_ref_nb == 0);
		delete m_buffer;
	}
}

size_t Serializer::GetSize() const
{
	natU32 len;
	memcpy(&len, &m_buffer[s_header_pos_length], sizeof(natU32));

	if(s_IsBigEndian)
	{
		len = SWAP_32(len);
	}

	return static_cast<size_t>(len);
}

natU32 Serializer::GetType() const
{
	natU32 type;
	memcpy(&type, &m_buffer[s_header_pos_type], sizeof(natU32));

	if(s_IsBigEndian)
	{
		type = SWAP_32(type);
	}

	return type;
}

void Serializer::Copy(const natU8* const _copy, size_t _copy_size)
{
	assert(_copy_size <= m_buffer_size);

	ResetCursor();
	memcpy(m_buffer, _copy, _copy_size);
}

void Serializer::SetCursor(size_t _pos)
{
	m_cursor_pos = _pos;
}

void Serializer::ResetCursor()
{
	m_cursor_pos = 0;
}

natBool Serializer::Write(natU32 _type)
{
	assert(m_state == E_IDLE);

	ResetCursor();
	m_state = E_WRITE;

	*this << static_cast<natU32>(0);
	*this << _type;

	return m_state == E_WRITE;
}

natBool Serializer::Write(const natChar* _type)
{
	return Write(Hash::Compute(_type));
}

void Serializer::Close()
{
	assert(m_state == E_WRITE || m_state == E_READ);

	if(m_state == E_WRITE)
	{
		// compute csksum && length
		size_t save_cursor = GetCursor();
		ResetCursor();

		// cast size_t for x64
		*this << static_cast<natU32>(save_cursor);

		SetCursor(save_cursor);
	}

	m_state = E_IDLE;
}

natBool Serializer::Read(natU32 _type)
{
	assert(m_state == E_IDLE);

	ResetCursor();
	m_state = E_READ;

	natU32 length, type;

	*this >> length;
	*this >> type;

	if(type != _type || length > m_buffer_size)
	{
		Close();
	}
		
	return m_state == E_READ;
}

natBool Serializer::Read(const natChar* _type)
{
	return Read(Hash::Compute(_type));
}

Serializer&	Serializer::operator=(const Serializer &_copy)
{
	if(m_owner)
	{
		if(m_buffer != nullptr)
		{
			delete m_buffer;
		}

		m_buffer = new natU8[_copy.m_buffer_size];
		Copy(_copy.m_buffer, _copy.m_buffer_size);
	}

	return *this;
}

Serializer& Serializer::operator <<(const natBool _val)
{
	assert(m_state == E_WRITE);

	natU8 val;
	if(_val)
	{
		val = 0x01;
	}
	else
	{
		val = 0x00;
	}
	*this << val;

	return *this;
}

Serializer& Serializer::operator <<(const natU8 _val)
{
	assert(m_state == E_WRITE);

	m_buffer[m_cursor_pos] = _val;
	m_cursor_pos += sizeof(natU8);

	assert(m_cursor_pos <= m_buffer_size);

	return *this;
}

Serializer& Serializer::operator <<(natS8 _val)
{
	*this << static_cast<natU8>(_val);

	return *this;
}

Serializer& Serializer::operator <<(natChar _val)
{
	*this << static_cast<natU8>(_val);

	return *this;
}

Serializer& Serializer::operator <<(natU16 _val)
{
	assert(m_state == E_WRITE);

	if(s_IsBigEndian)
	{
		_val = SWAP_16(_val);
	}

	memcpy(&m_buffer[m_cursor_pos], &_val, sizeof(natU16));

	m_cursor_pos += sizeof(natU16);

	assert(m_cursor_pos <= m_buffer_size);

	return *this;
}

Serializer& Serializer::operator <<(natS16 _val)
{
	*this << static_cast<natU16>(_val);

	return *this;
}

Serializer& Serializer::operator <<(natU32 _val)
{
	assert(m_state == E_WRITE);

	if(s_IsBigEndian)
	{
		_val = SWAP_32(_val);
	}

	memcpy(&m_buffer[m_cursor_pos], &_val, sizeof(natU32));

	m_cursor_pos += sizeof(natU32);

	assert(m_cursor_pos <= m_buffer_size);

	return *this;
}

Serializer& Serializer::operator <<(natS32 _val)
{
	*this << static_cast<natU32>(_val);

	return *this;
}

Serializer& Serializer::operator <<(natU64 _val)
{
	assert(m_state == E_WRITE);

	if(s_IsBigEndian)
	{
		_val = SWAP_64(_val);
	}

	memcpy(&m_buffer[m_cursor_pos], &_val, sizeof(natU64));

	m_cursor_pos += sizeof(natU64);

	assert(m_cursor_pos <= m_buffer_size);

	return *this;
}

Serializer& Serializer::operator <<(natS64 _val)
{
	*this << static_cast<natU64>(_val);

	return *this;
}

Serializer& Serializer::operator <<(natF32 _val)
{
	// not implemented
	assert(false);

	(void)_val;

	return *this;
}

Serializer& Serializer::operator <<(natF64 _val)
{
	// not implemented
	assert(false);

	(void)_val;

	return *this;
}

Serializer& Serializer::operator <<(const Serializer& _copy)
{
	assert(m_state == E_WRITE);

	assert(m_cursor_pos + _copy.GetSize() <= m_buffer_size);
	
	memcpy(m_buffer + m_cursor_pos, _copy.GetBuffer(), _copy.GetSize());
	m_cursor_pos += _copy.GetSize();

	return *this;
}

Serializer& Serializer::operator >>(natBool& _val)
{
	assert(m_state == E_READ);

	natU8 val;
	*this >> val;

	if(val == 0x01)
	{
		_val = true;
	}
	else if (val == 0x00)
	{
		_val = false;
	}

	return *this;
}

Serializer& Serializer::operator >>(natU8& _val)
{
	assert(m_state == E_READ);

	_val = m_buffer[m_cursor_pos];
	m_cursor_pos += sizeof(natU8);

	return *this;
}

Serializer& Serializer::operator >>(natS8& _val)
{
	*this >> reinterpret_cast<natU8&>(_val);

	return *this;
}

Serializer& Serializer::operator >>(natChar& _val)
{
	*this >> reinterpret_cast<natU8&>(_val);

	return *this;
}

Serializer& Serializer::operator >>(natU16& _val)
{
	assert(m_state == E_READ);

	memcpy(&_val, &m_buffer[m_cursor_pos], sizeof(natU16));
	m_cursor_pos += sizeof(natU16);

	if(s_IsBigEndian)
	{
		_val = SWAP_16(_val);
	}

	return *this;
}

Serializer& Serializer::operator >>(natS16& _val)
{
	*this >> reinterpret_cast<natU16&>(_val);

	return *this;
}

Serializer& Serializer::operator >>(natU32& _val)
{
	assert(m_state == E_READ);

	memcpy(&_val, &m_buffer[m_cursor_pos], sizeof(natU32));
	m_cursor_pos += sizeof(natU32);

	if(s_IsBigEndian)
	{
		_val = SWAP_32(_val);
	}

	return *this;
}

Serializer& Serializer::operator >>(natS32& _val)
{
	*this >> reinterpret_cast<natU32&>(_val);

	return *this;
}

Serializer& Serializer::operator >>(natU64& _val)
{
	assert(m_state == E_READ);

	memcpy(&_val, &m_buffer[m_cursor_pos], sizeof(natU64));
	m_cursor_pos += sizeof(natU64);

	if(s_IsBigEndian)
	{
		_val = SWAP_64(_val);
	}

	return *this;
}

Serializer& Serializer::operator >>(natS64& _val)
{
	*this >> reinterpret_cast<natU64&>(_val);

	return *this;
}

Serializer& Serializer::operator >>(natF32& _val)
{
	// not implemented
	assert(false);

	(void)_val;

	return *this;
}

Serializer& Serializer::operator >>(natF64& _val)
{
	// not implemented
	assert(false);

	(void)_val;

	return *this;
}

Serializer& Serializer::operator >>(Serializer& _copy)
{
	assert(m_state == E_READ);

	_copy.ResetCursor();

	// read type and length
	natU32 length;
	natU32 type;

	size_t old_cursor = GetCursor();

	*this >> length;
	*this >> type;

	SetCursor(old_cursor);

	assert(length < _copy.GetBufferSize());

	memcpy(_copy.m_buffer, m_buffer + m_cursor_pos, length);
	SetCursor(GetCursor() + length);

	return *this;
}

// helpers
Serializer& Serializer::operator <<(const std::string& _val)
{
	assert(m_state == E_WRITE);

	const natChar* buff = _val.c_str();

	natU32 length = static_cast<natU32>(_val.size());
	*this << length;

	memcpy(m_buffer + m_cursor_pos, buff, length);
	SetCursor(GetCursor() + length);

	return *this;
}

Serializer& Serializer::operator <<(const glm::vec2& _val)
{
	assert(m_state == E_WRITE);

	*this << _val.x;
	*this << _val.y;

	return *this;
}

Serializer& Serializer::operator <<(const glm::vec3& _val)
{
	assert(m_state == E_WRITE);

	*this << _val.x;
	*this << _val.y;
	*this << _val.z;

	return *this;
}

Serializer& Serializer::operator <<(const glm::vec4& _val)
{
	assert(m_state == E_WRITE);

	*this << _val.x;
	*this << _val.y;
	*this << _val.z;
	*this << _val.w;

	return *this;
}

Serializer& Serializer::operator <<(const glm::mat4& _val)
{
	assert(m_state == E_READ);

	for(size_t i=0; i < 4; ++i)
	{
		*this << _val[i].x;
		*this << _val[i].y;
		*this << _val[i].z;
		*this << _val[i].w;
	}

	return *this;
}

Serializer& Serializer::operator >>(std::string& _val)
{
	assert(m_state == E_READ);

	natU32 length;
	*this >> length;

	assert(length < GetBufferSize());
	
	natChar *temp = new natChar[length];

	memcpy(temp, m_buffer + m_cursor_pos, length);
	SetCursor(GetCursor() + length);

	// copy the temp string to the new one
	_val = temp;

	delete temp;
	return *this;
}

Serializer& Serializer::operator >>(glm::vec2& _val)
{
	assert(m_state == E_READ);

	*this >> _val.x;
	*this >> _val.y;

	return *this;
}

Serializer& Serializer::operator >>(glm::vec3& _val)
{
	assert(m_state == E_READ);

	*this << _val.x;
	*this << _val.y;
	*this << _val.z;

	return *this;
}

Serializer& Serializer::operator >>(glm::vec4& _val)
{
	assert(m_state == E_READ);

	*this >> _val.x;
	*this >> _val.y;
	*this >> _val.z;
	*this >> _val.w;

	return *this;
}

Serializer& Serializer::operator >>(glm::mat4& _val)
{
	assert(m_state == E_READ);

	for(size_t i=0; i < 4; ++i)
	{
		*this >> _val[i].x;
		*this >> _val[i].y;
		*this >> _val[i].z;
		*this >> _val[i].w;
	}

	return *this;
}

Serializer& Serializer::operator <<(const void** _val)
{
	// Woot!
	natU32 length = static_cast<natU32>(sizeof(void*));

	memcpy(m_buffer + m_cursor_pos, _val, length);
	SetCursor(GetCursor() + length);

	return *this;
}

Serializer& Serializer::operator >>(void** _val)
{
	natU32 length = static_cast<natU32>(sizeof(void*));

	memcpy(_val, m_buffer + m_cursor_pos, length);
	SetCursor(GetCursor() + length);

	return *this;
}


};
