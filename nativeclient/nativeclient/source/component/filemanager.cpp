#include "component/filemanager.h"

#include "base/entity.h"

#include <cassert>

#include <physfs.h>

#include <stdio.h>

#include <iostream>
#include <fstream>

namespace Natorium
{

extern char* s_exePath;

FileManager::FileManager()
{

}

FileManager::~FileManager()
{

}

void FileManager::OnInit()
{
#if defined(WINDOWS_TARGET)
	int ret = PHYSFS_init(s_exePath);
#elif defined(EMSCRIPTEN_TARGET)
	int ret = PHYSFS_init("/");
#endif

	assert(ret);

#if defined(WINDOWS_TARGET)
	if(PHYSFS_mount(".\\data\\", "/data", 0) == 0)
	{
		assert(false);
	}
#elif defined(EMSCRIPTEN_TARGET)
	if(PHYSFS_mount("/data", "/data", 0) == 0)
	{
		printf("%s\n", PHYSFS_getLastError());
		assert(false);
	}
#else

#endif

	//FILE* file = fopen("data/idle-0.png", "r");
	//assert(file);

}

void FileManager::Clone(Entity* _entity) const
{
	FileManager* component = _entity->AddComponent<FileManager>();
}

void FileManager::OnTick(const natU64 _dt)
{

}

void FileManager::OnDeInit()
{
	PHYSFS_deinit();
}

natU8* FileManager::Read(const natChar* _filename, size_t* _size)
{
//#if defined(WINDOWS_TARGET)
	PHYSFS_file* file = PHYSFS_openRead(_filename);
	assert(file);

	*_size = PHYSFS_fileLength(file);
	assert(*_size != 0);

	natU8* buffer = new natU8[*_size];
	PHYSFS_read(file, buffer, 1, static_cast<PHYSFS_uint32>(*_size));

	return buffer;
/*#elif defined(EMSCRIPTEN_TARGET)
	std::ifstream file(_filename, std::ios::in|std::ios::binary|std::ios::ate);
	assert(file.is_open());

	*_size = file.tellg();
	assert(*_size != 0);

	natU8* buffer = new natU8[*_size];
	file.seekg (0, std::ios::beg);
	file.read ((char*)buffer, *_size);
	file.close();

	return buffer;
#else

#endif*/
}


}