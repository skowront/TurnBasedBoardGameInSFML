#pragma once

#include "stdafx.h"
#pragma region obj;


void object::info()
{

}

sf::FloatRect object::getGlobalBounds() const
{
	return shape.getGlobalBounds();
}

std::string object::getName()
{
	return name;
}


void object::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	target.draw(shape, state);
	if (/*!sftext.getString().isEmpty()*/true)
	{
		target.draw(sftext);
	}
}



sf::Color object::getColor()
{
	return shape.getFillColor();
}

sf::Vector2f object::getSize()
{
	return shape.getSize();
}

sf::Vector2f object::getPosition()
{
	return shape.getPosition();
}

sf::Vector2f object::getOrigin()
{

	return shape.getOrigin();
}

void object::setText(std::string,bool positioning)
{

}

void object::setColor(sf::Color newcolor)
{
	shape.setFillColor(newcolor);
}
void object::setSize(sf::Vector2f newsize)
{
	shape.setSize(newsize);
}
void object::setPosition(sf::Vector2f newpos)
{
	shape.setPosition(newpos);
}
void object::setOrigin(sf::Vector2f neworigin)
{
	shape.setOrigin(neworigin);
}

#pragma endregion





