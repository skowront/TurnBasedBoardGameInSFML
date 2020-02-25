#include "stdafx.h"
//UNIT



unit::unit()
{
	owner = none_player;
	power = UNIT_POWER;
	shape.setSize(sf::Vector2f((float)sizex,(float) sizex));
	setColor_player();
}

unit::unit(std::string nam)
{
	owner = none_player;
	name = nam;
	power = UNIT_POWER;
	shape.setSize(sf::Vector2f((float)sizex,(float) sizex));
	setColor_player();
}

unit::unit(std::string nam,sf::Vector2f position)
{
	owner = none_player;
	name = nam;
	power = UNIT_POWER;
	shape.setSize(sf::Vector2f((float)sizex,(float) sizex));
	setColor_player();
	shape.setPosition(position);
}

unit::unit(std::string nam, sf::Vector2f position, int owned_by)
{
	owner = owned_by;
	name = nam;
	power = UNIT_POWER;
	shape.setSize(sf::Vector2f((float)sizex,(float) sizex));
	setColor_player();
	shape.setPosition(sf::Vector2f(position.x,position.y));
}

unit::unit(std::string nam, sf::Vector2f position, int owned_by,AppStateInfo*&ASI)
{
	owner = owned_by;
	name = nam;
	power = UNIT_POWER;
	shape.setSize(sf::Vector2f((float)sizex,(float)sizex));
	setColor_player();
	shape.setPosition(sf::Vector2f(position.x, position.y));
	if (owner == player1)
	{
		shape.setTexture(&ASI->ini.units_blue.obj_texture);
	}
	if (owner == player2)
	{
		shape.setTexture(&ASI->ini.units_red.obj_texture);
	}
	this->update(ASI);
}




unit::~unit()
{

}

void unit::update(AppStateInfo*&ASI)
{
	int margin = 2;
	int power_size = 10;
	sftext.setString(sf::String(std::to_string(power)));
	sftext.setFont(ASI->ini.mainfont.font);
	sftext.setPosition(sf::Vector2f(shape.getPosition().x + margin, (shape.getPosition().y + (shape.getSize().y / 2))));
	sftext.setCharacterSize(power_size);
	sftext.setFillColor(sf::Color::White);
	font = ASI->ini.mainfont.font;
}

void unit::qupdate()
{
	int margin = 2;
	int power_size = 10;
	sftext.setString(sf::String(std::to_string(power)));
	sftext.setFont(font);
	sftext.setPosition(sf::Vector2f(shape.getPosition().x + margin, (shape.getPosition().y + (shape.getSize().y / 2))));
	sftext.setCharacterSize(power_size);
	sftext.setFillColor(sf::Color::White);

}

void unit::setColor(sf::Color color)
{
	shape.setFillColor(color);
}

void unit::increment()
{
	power = power + UNIT_POWER;
}

void unit::merge_unit_B_into_A(unit *&a, unit *&b)
{
	a->power += b->power;
}

void unit::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	target.draw(shape, state);
	if (!sftext.getString().isEmpty())
	{
		if (this->sftext.getString().isEmpty())
		{
			return;
		}
		if (this->sftext.getFont()==NULL)
		{
			return;
		}
		target.draw(sftext);
	}
}

void unit::setColor_player()
{
	if (owner==player1)
	{
		setColor(sf::Color(0,0,200,255));
	}
	else
	{
		if (owner == player2)
		{
			setColor(sf::Color(200, 0, 0, 255));
		}
		else
		{
			setColor(sf::Color::Green);
		}
	}
}


