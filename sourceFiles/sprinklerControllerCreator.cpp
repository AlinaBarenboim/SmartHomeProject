#include "../hFiles/sprinklerControllerCreator.h"


extern "C"
void* GetCreator()
{
	return new SprinklerControllerCreator();
}
