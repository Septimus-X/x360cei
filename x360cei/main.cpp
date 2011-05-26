#include "main.h"
#include "application.h"

EXTERN_C int WINAPI Main()
{
	Application();
	ExitProcess(0);
	return 0; // Won't be reached.
}
