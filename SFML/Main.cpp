#define _CRTDBG_MAP_ALLOC  

#include <stdlib.h>  
#include <crtdbg.h>  
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <windows.h>
#include "stdafx.h"
#include <string>




int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	{
		Game game;
		try
		{
			game.Play();
		}
		catch (const std::exception&)
		{

		}
	}
	return 0;
}