#pragma once

#include "natdef.h"


namespace Natorium
{

class Hash
{
public:
	static	natU32 Compute(const natChar* _string)
	{
		unsigned long hash = 5381;
		int c;

		while((c = *_string++))
		{
			hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
		}

		return hash;
	}

};


}
