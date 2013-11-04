#include "base/hash.h"

#include <string>

namespace Natorium
{

ref_t Hash::Compute(const natChar* _string)
{
{
		/*ref_t hash = 5381;
		int c;

		while((c = *_string++))
		{
			hash = ((hash << 5) + hash) + c;
		}

		return hash;*/

		const void* key = _string;
		unsigned int seed = 0;
		std::string temp_str = std::string(_string);
		unsigned int len = static_cast<unsigned int>(temp_str.size());

		//-----------------------------------------------------------------------------
		// MurmurHashNeutral2, by Austin Appleby

		// Same as MurmurHash2, but endian- and alignment-neutral.
		// Half the speed though, alas.

		const unsigned int m = 0x5bd1e995;
		const int r = 24;

		unsigned int h = seed ^ len;

		const unsigned char * data = (const unsigned char *)key;

		while(len >= 4)
		{
			unsigned int k;

			k  = data[0];
			k |= data[1] << 8;
			k |= data[2] << 16;
			k |= data[3] << 24;

			k *= m; 
			k ^= k >> r; 
			k *= m;

			h *= m;
			h ^= k;

			data += 4;
			len -= 4;
		}
	
		switch(len)
		{
		case 3: h ^= data[2] << 16;
		case 2: h ^= data[1] << 8;
		case 1: h ^= data[0];
				h *= m;
		};

		h ^= h >> 13;
		h *= m;
		h ^= h >> 15;

		return h;
	}
}



}