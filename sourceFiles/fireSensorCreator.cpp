#include "../hFiles/fireSensorCreator.h"


extern "C"
void* GetCreator()
{
	return new FireSensorCreator();
}
