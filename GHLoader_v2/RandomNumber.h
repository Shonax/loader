#pragma once
#include <stdafx.h>
#define RandRange(min, max) (double)rand() / RAND_MAX * (max - min) + min

class RandomNumber
{
	static bool bSeeded;
	int GenerateInt();
	static void Seed();
public:

	template<class T>
	static T Generate()
	{
		Seed();
		return rand();
	}

	template<class T>
	static T Generate(int min, int max)
	{
		Seed();
		return RandRange(min, max);
	}

};