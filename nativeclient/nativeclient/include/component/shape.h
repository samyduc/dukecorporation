#pragma once
#include "base/natdef.h"
#include "base/component.h"

#include "base/hash.h"

#include <glm/glm.hpp>

namespace Natorium
{

static natU32 s_Shape = Hash::Compute("s_Shape");

class Shape : public Component
{
public:

	static natU32		GetType() { return s_Shape; }


	virtual natF32*		GetVertex(size_t &_size) = 0;
	virtual glm::vec2	GetSize() = 0;
};


}