#include "../hFiles/liveLogCreator.h"

extern "C"
void* GetCreator()
{
	return new LiveLogCreator();
}
