#include "RandomNumber.h"

bool RandomNumber::bSeeded = false;

void RandomNumber::Seed()
{
	if (!bSeeded)
	{
		srand(clock());
		int x = RandRange(2, 10);
		for (int y = 0; y < x; y++)
			rand();
		bSeeded = true;
	}
}

int RandomNumber::GenerateInt()
{
	Seed();
	return rand();
}
