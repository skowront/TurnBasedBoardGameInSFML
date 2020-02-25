#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include "PreDef.h"
#include "ClickableObject.h"
#include "ASI.h"
#include "debug_utilities.h"

class object;

//representation of a unit
class unit: public object
{
private:
	int posx=0;
	int posy=0;
	int sizex = UNIT_SIZE_DEF;
	int sizey = UNIT_SIZE_DEF;
public:
	std::string name;
	int owner;
	int power;
	sf::RectangleShape shape;
	unit();
	unit(std::string);
	unit(std::string,sf::Vector2f);
	unit(std::string, sf::Vector2f,int owner);
	unit(std::string, sf::Vector2f, int owner,AppStateInfo*&);
	~unit();
	void update(AppStateInfo*&);
	void qupdate();
	void setColor(sf::Color);
	void increment();
	void merge_unit_B_into_A(unit*&, unit*&);
	void draw(sf::RenderTarget &target, sf::RenderStates state) const override;
	void setColor_player();
};





