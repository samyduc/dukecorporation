#include "base/timeplatform.h"

#include <Windows.h>


namespace Natorium
{

timer_t Time::GetMsTime()
{
	return GetTickCount64();
}


};