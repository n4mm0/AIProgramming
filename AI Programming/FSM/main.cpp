#include "Dwarf.h"

int main(void)
{
	Dwarf myDwarf;
	myDwarf.Init();

	int iter = 0;

	while (iter < 100)
	{
		++iter;
		myDwarf.Update(0.1f);
	}

	getchar();
	return 0;
}