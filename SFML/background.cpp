#include "stdafx.h"


void background::background_core()
{
	shape.setFillColor(sf::Color::White);
	shape.setSize(sf::Vector2f(100, 100));
	shape.setPosition(sf::Vector2f(0, 0));
	shape.setOrigin(0, 0);
}

//BACKGROUND
background::background()
{

	background_core();
}

background::background(std::string nam)
{
	name = nam;
	background_core();
}

background::background(std::string nam, int sizex, int sizey,AppStateInfo *&ASI)
{
	background_core();
	name = nam;
	shape.setSize(sf::Vector2f((float)sizex, (float)sizey));
	ASI->ini.background.obj_texture.setSmooth(true);
	shape.setTexture(&ASI->ini.background.obj_texture);
	if (ASI->ini.background_scaling)
	{
		shape.setTextureRect(sf::IntRect(ASI->ini.background_origin_x, ASI->ini.background_origin_y, ASI->ini.background_x, ASI->ini.background_y));
	}
}

background::~background()
{

}

void background::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	target.draw(shape, state);
}

void background::info()
{

}

sf::FloatRect background::getGlobalBounds() const
{
	return shape.getGlobalBounds();
}

std::string background::getName()
{
	return name;
}