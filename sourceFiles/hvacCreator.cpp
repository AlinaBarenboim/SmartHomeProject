#include "../hFiles/hvacCreator.h"


extern "C"
void* GetCreator()
{
	return new HVACCreator();
}
