#pragma once

#include "natdef.h"


namespace Natorium
{

class Hash
{
public:
	static ref_t Compute(const natChar* _string)
	{
		ref_t hash = 5381;
		int c;

		while((c = *_string++))
		{
			hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
		}

		return hash;
	}

};


}
