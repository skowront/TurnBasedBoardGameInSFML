#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include "ClickableObject.h"

class container;
class clickableObject;

//class represenging button, is clickable
class button : public clickableObject
{
private:
	std::string name = "BTN";
public:
	button();
	button(std::string);
	button(std::string nam, int fx);
	button(std::string nam, int fx, container*theworld);
	~button();
	void info();
	virtual void setText(std::string,bool positioning);
	std::string getName();
};

