#pragma once
#include "Object.h"
#include "unit.h"
#include "Button.h"
class AppStateInfo;
class unit;
class object;

//class used in board to represent one single field that unit can exist on, contains pointer to unit, and can update'its state and pointed units's state(position etc.)
class field : public object
{
public:
	void update(AppStateInfo*&);
	field();
	field(std::string);
	~field();
	unit*units = nullptr;
	void draw(sf::RenderTarget &target, sf::RenderStates state) const override;
	void info();
	sf::FloatRect getGlobalBounds() const;
	std::string getName();
};