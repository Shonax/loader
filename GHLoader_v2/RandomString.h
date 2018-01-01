#pragma once
#include <stdafx.h>

class RandomString
{
public:
	RandomString(uint uLen);
	~RandomString();
	tstring Generate();

private:
	uint uLen;
	tstring szString;
};

