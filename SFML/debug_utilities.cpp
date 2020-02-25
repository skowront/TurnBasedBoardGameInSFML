#include "stdafx.h"


void stdprint(std::string s,AppStateInfo*&ASI)
{
	if (ASI->ini.printdebugs)
	{
		std::cout << s << std::endl;
	}
	else
	{
		return;
	}
}