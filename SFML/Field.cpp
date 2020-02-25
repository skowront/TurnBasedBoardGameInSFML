#include "stdafx.h"

//FIELD

void field::update(AppStateInfo*&ASI)
{

	if (units)
	{
		units->shape.setPosition(sf::Vector2f(this->getPosition().x + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2), this->getPosition().y + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2)));
		units->update(ASI);
	}
}

field::field()
{
	shape.setSize(sf::Vector2f(FIELD_SIZE_DEF, FIELD_SIZE_DEF));
	shape.setFillColor(sf::Color::Red);
}

field::field(std::string nam)
{
	name = nam;
	shape.setSize(sf::Vector2f(FIELD_SIZE_DEF, FIELD_SIZE_DEF));
	shape.setFillColor(sf::Color::Red);
	units = nullptr;
}

field::~field()
{
	if (units)
	{
		delete units;
		units = nullptr;
	}
	//std::cout << "field and units destroyed" << std::endl;
}

void field::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	target.draw(shape, state);
	if (units)
	{
		units->qupdate();
		units->draw(target, state);
	}

}

//USE
sf::FloatRect field::getGlobalBounds() const
{
	return shape.getGlobalBounds();
}

std::string field::getName()
{
	return name;
}

//DEBUG
void field::info()
{

}