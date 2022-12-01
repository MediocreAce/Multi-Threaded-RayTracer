///Include ability to use Smart Pointers which automatically delete
#include <memory>
///Include ability to create a class object of Core
#include "Classes/Core.h"


///Code start
int main(int argc, char* argv[])
{
	///Create a smart pointer Core class object
	std::unique_ptr<Core> core = std::make_unique<Core>();
	
	///Initialize the object's values
	///If an error, stop the program
	if (!core->init())
		return -1;

	///If no error, run the program
	core->programLoop();

	///End the code
	return 0;
}