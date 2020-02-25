#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include "PreDef.h"
//#include "ASI.h"
#include "Button.h"
#include "Field.h"
#include "unit.h"

class unit;
class field;
class button;
class clickableObject;



//class prepared to act as 10x10 playing board, it might act as bigger one, however the size would need to be recalculated manually
class board : public clickableObject
{
	
public:
	int sizex=825;
	int sizey=455;
	int btncount = BTNTYPESCOUNT;
	int xD = 10;
	int yD = 10;
	std::string name = "BRD";
	field** tab=nullptr;
	button** player1btns=nullptr;
	button** player2btns=nullptr;
	board();
	board(std::string);
	board(std::string,container*&);
	board(std::string, container*&, int fx);
	board(std::string, container*&,int fx,int*fxtab,texture_data**&,texture_data*fields_bg, texture_data*units_blue, texture_data*units_red);
	~board();
	void board_core();
	void draw(sf::RenderTarget &target, sf::RenderStates state) const override;
	void board_clicked(sf::Vector2f);
	sf::FloatRect getGlobalBounds() const;
	std::string getName();
	void info();
	void setPosition(sf::Vector2f);
};
