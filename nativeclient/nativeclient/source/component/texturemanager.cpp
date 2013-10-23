#include "component/texturemanager.h"

#include "base/entity.h"
#include "base/kernel.h"
#include "base/layer.h"
#include "base/component.h"
#include "base/hash.h"

#include "component/filemanager.h"
#include "component/glmanager.h"

#include <SOIL.h>

#include <cassert>


namespace Natorium
{



TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{

}

void TextureManager::OnInit()
{
	InitFromDirectory("/data/texture");
}

void TextureManager::OnTick(const natU64 _dt)
{

}

void TextureManager::OnDeInit()
{
	for(textures_buf_t::iterator it = m_buffers.begin(); it != m_buffers.end(); ++it)
	{
		GLuint id = it->first;
		struct TextureSimple &texture = it->second;
		
		glDeleteTextures(1, &id);
		delete texture.m_buffer;
	}

	m_buffers.clear();
	m_preloads.clear();
	m_textures.clear();
}

void TextureManager::Preload(const natChar* _path, size_t _options)
{
	ref_t hash = Hash::Compute(_path);
	struct PreloadTextureSimple preload;
	preload.m_path = _path;
	preload.m_option = _options;
	m_preloads[hash] = preload;
}

GLuint TextureManager::Get(const natChar* _path)
{
	ref_t hash = Hash::Compute(_path);
	return Get(hash);
}

GLuint TextureManager::Get(ref_t _id)
{
	GLuint ret = 0;
	textures_ref_t::const_iterator it = m_textures.find(_id);

	if(it != m_textures.end())
	{
		ret = it->second;
	}
	else
	{
		// use preload
		textures_path_t::const_iterator it_path = m_preloads.find(_id);
		if(it_path != m_preloads.end())
		{
			const struct PreloadTextureSimple &preload = (it_path->second);
			ret = Load(preload.m_path.c_str(), preload.m_option, false);
		}
	}

	return ret;
}

void TextureManager::Add(ref_t _id, GLuint _texture)
{
	textures_ref_t::const_iterator it = m_textures.find(_id);

	if(it == m_textures.end())
	{
		m_textures[_id] = _texture;
	}
	else
	{
		// texture already present
		assert(false);
	}
}

GLuint TextureManager::Load(const natChar* _path, size_t _options, natBool _checkGet)
{
	ref_t hash = Hash::Compute(_path);
	// protect against multiple loading
	GLuint ret = 0;
	
	if(_checkGet)
	{
		ret = Get(hash);
	}

	if(ret == 0)
	{
		FileManager* filemanager = GetEntity()->GetKernel()->GetLayer(Layer::s_LayerManager)->GetRootEntity()->GetComponent<FileManager>();
		assert(filemanager);

		size_t size;
		natU8 *buffer = filemanager->Read(_path, &size);
		struct TextureSimple texture_simple;
		texture_simple.m_buffer = buffer;
		texture_simple.m_size = size;
		m_buffers[hash] = texture_simple;

		ret = Load(buffer, size, _options);
		m_textures[hash] = ret;
	}

	return ret;
}


GLuint TextureManager::Load(const natU8* _bytes, size_t _size, size_t _options)
{
	GLuint ret = SOIL_load_OGL_texture_from_memory(
		_bytes,
		static_cast<int>(_size),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		(unsigned int)_options
	);

	return ret;
}

glm::vec2 TextureManager::GetTextureSize(const natChar* _path)
{
	// overkill solution ...
	natS32 width, height, channels;

	FileManager* filemanager = GetEntity()->GetKernel()->GetLayer(Layer::s_LayerManager)->GetRootEntity()->GetComponent<FileManager>();
	assert(filemanager);

	size_t size;
	natU8 *buffer = filemanager->Read(_path, &size);

	natU8 *img = SOIL_load_image_from_memory(buffer, static_cast<natS32>(size), &width, &height, &channels, 0 );

	delete buffer;
	SOIL_free_image_data(img);

	return glm::vec2(width, height);
}

void TextureManager::InitFromDirectory(const natChar* _path)
{
	FileManager* filemanager = GetEntity()->GetKernel()->GetLayer(Layer::s_LayerManager)->GetRootEntity()->GetComponent<FileManager>();
	assert(filemanager);

	// load all prefab
	std::vector<std::string> files;
	filemanager->EnumerateFiles(_path, files);

	for(std::vector<std::string>::iterator it = files.begin(); it != files.end(); ++it)
	{
		const natChar* path = (*it).c_str();
		Load(path);
	}
}



}