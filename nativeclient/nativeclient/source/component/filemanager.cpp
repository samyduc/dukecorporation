#include "component/filemanager.h"

#include "base/entity.h"

#include <cassert>

#include <physfs.h>

#include <sstream>

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
		//printf("%s\n", PHYSFS_getLastError());
		assert(false);
	}
#else

#endif

	//FILE* file = fopen("data/idle-0.png", "r");
	//assert(file);

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
	PHYSFS_close(file);

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

void FileManager::EnumerateFiles(const natChar* _path, std::vector<std::string>& _files)
{
	natChar **rc = PHYSFS_enumerateFiles(_path);
	natChar **i;

	for(i = rc; *i != NULL; ++i)
	{
		std::ostringstream oss;
		oss << _path << '/' << *i;
		_files.push_back(oss.str());
	}

	PHYSFS_freeList(rc);
}

void FileManager::ConcatenatePath(const natChar* _pathLeft, const natChar* _pathRight, std::string& _path)
{
	size_t len = strnlen(_pathLeft, 1000);

	_path = _pathLeft;
	if(strncmp(_pathLeft+len-1, "/", 2) != 0)
	{
		_path += '/';
	}
	_path += _pathRight;
}

void FileManager::GetFileExtension(const natChar* _path, std::string& _extension)
{
	std::string path(_path);
	std::string::size_type idx;

	idx = path.rfind('.');

	if(idx != std::string::npos)
	{
		_extension = path.substr(idx+1);
	}
	else
	{
		_extension = "";
	}
}

}