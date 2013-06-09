
#if defined(EMSCRIPTEN_TARGET)
#include <emscripten/emscripten.h>
#endif

#include <chrono>
#include <thread>

#include "base/kernel.h"

Natorium::Kernel *kernel;


void one_iter()
{
	for(int i=0; i<1; ++i)
	{
		kernel->Tick();
	}
}

int main(int argc, char *argv[]) 
{
	kernel = new Natorium::Kernel();
	kernel->Init();

#if defined(EMSCRIPTEN_TARGET)
	emscripten_set_main_loop(one_iter, 1000000, true);
#else
	while(true)
	{
		one_iter();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
#endif
 
	return 0;
}