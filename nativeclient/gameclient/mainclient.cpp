

#include <chrono>
#include <thread>

#include "base/kernel.h"

Natorium::Kernel *kernel;

namespace Natorium
{
	char* s_exePath;
}

void one_iter()
{
	kernel->Tick();
}

int main(int argc, char *argv[]) 
{
	Natorium::s_exePath = argv[0];

	kernel = new Natorium::Kernel();
	kernel->Init();

#if defined(EMSCRIPTEN_TARGET)
	emscripten_set_main_loop(one_iter, 0, 0);
#else
	while(kernel->IsRunning())
	{
		one_iter();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
#endif

	kernel->DeInit();
	delete kernel;
 
	return 0;
}