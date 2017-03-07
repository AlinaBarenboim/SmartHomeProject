#include "../hFiles/elevatorCreator.h"


extern "C"
void* GetCreator()
{
	return new ElevatorCreator();
}
