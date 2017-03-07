#include "../hFiles/tempSensorCreator.h"


extern "C"
void* GetCreator()
{
	return new TempSensorCreator();
}
