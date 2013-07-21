#pragma once

#include "base/natdef.h"
#include "base/component.h"
#include "base/hash.h"

#if defined(WINDOWS_TARGET)
//#include <Windows.h>
//#include <gl\GL.h>
#include <GL\glew.h>
#endif

#if defined(EMSCRIPTEN_TARGET)
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#endif

#include <map>

namespace Natorium
{

static natU32 s_TextureManager = Hash::Compute("TextureManager");


struct TextureSimple
{
	natU8*	m_buffer;
	size_t	m_size;
};

class TextureManager : public Component
{
public:
					TextureManager();
	virtual			~TextureManager();

	virtual void	OnInit();
	virtual void	OnTick(const natU64 _dt);
	virtual void	OnDeInit();

	static natU32	GetType() { return s_TextureManager; }

	virtual void	Clone(Entity* _entity, natU32 _type) const;
	void			WriteData(Serializer& _ser);
	void			ReadData(Serializer& _ser);

	void			Load(const natChar* _path);

	GLuint			Get(const natChar* _path) const;
	GLuint			Get(natU32 _id) const;

protected:
	GLuint			Load(const natU8* _bytes, size_t _size);

private:
	typedef std::map<natU32, GLuint> textures_ref_t;
	textures_ref_t	m_textures;

	typedef std::map<GLuint, struct TextureSimple> textures_buf_t;
	textures_buf_t	m_buffers;

};




}