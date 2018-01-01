#include "RandomString.h"

RandomString::RandomString(uint uLen)
{
	this->uLen = uLen;
}

RandomString::~RandomString()
{
}

tstring RandomString::Generate()
{
	std::string buffer;
	//srand(clock());
	while (buffer.length() < uLen)
	{
		int c = (double)rand() / RAND_MAX * 127;
		if (isalnum(c))
		{
			buffer.append((char*)&c);
		}
	}
	szString.resize(uLen + 1);
#ifdef _UNICODE
	mbstowcs_s(nullptr, &szString[0], uLen + 1, &buffer[0], uLen);
#else
	szString = buffer;
#endif // _UNICODE

	return szString;
}
