#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include "ClickableObject.h"
//#include "ASI.h"

class AppStateInfo;
class clickableObject;
//background is a class representing application's background image
class background :public clickableObject
{
public:
	void background_core();
	background();
	~background();
	background(std::string);
	background(std::string nam, int sizex, int sizey,AppStateInfo*&);
	void draw(sf::RenderTarget &target, sf::RenderStates state) const override;
	void info();
	sf::FloatRect getGlobalBounds() const;
	std::string getName();
};
