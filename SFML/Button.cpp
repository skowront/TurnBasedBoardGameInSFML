#include "stdafx.h"

button::button()
{

	shape.setFillColor(sf::Color::White);
	shape.setSize(sf::Vector2f(BUTTON_SIZE_DEF, BUTTON_SIZE_DEF));
	shape.setPosition(sf::Vector2f(0, 0));
	shape.setOrigin(0, 0);
}

button::button(std::string nam)
{
	name+= nam;
	shape.setFillColor(sf::Color::White);
	shape.setSize(sf::Vector2f(BUTTON_SIZE_DEF, BUTTON_SIZE_DEF));
	shape.setPosition(sf::Vector2f(0, 0));
	shape.setOrigin(0, 0);
}

button::button(std::string nam, int fx)
{
	name+= nam;
	this->SetClicked(fx);
	shape.setFillColor(sf::Color::White);
	shape.setSize(sf::Vector2f(BUTTON_SIZE_DEF, BUTTON_SIZE_DEF));
	shape.setPosition(sf::Vector2f(0, 0));
	shape.setOrigin(0, 0);
}

button::button(std::string nam, int fx, container * theworld)
{
	name+= nam;
	this->SetClicked(fx);
	world = theworld;
	shape.setFillColor(sf::Color::White);
	shape.setSize(sf::Vector2f(BUTTON_SIZE_DEF, BUTTON_SIZE_DEF));
	shape.setPosition(sf::Vector2f(0, 0));
	shape.setOrigin(0, 0);
}

button::~button()
{

}

void button::info()
{
}

void button::setText(std::string text,bool positioning)
{
	int font_size = 10;
	this->sftext.setCharacterSize(font_size);
	this->sfstr = text;
	this->sftext.setString(this->sfstr);
	
	if (positioning)
	{
		int len = (int)text.length();
		(int)(len*this->sftext.getCharacterSize()) > (int)(this->getSize().x) ? len /= 2 : false;
		int divisor = 1;
		len = 0;
		for (int i = 0; i < text.length(); i++)
		{
			if (text[i] == '\n')
			{
				divisor++;
			}
			len++;
		}
		int multipliery=divisor;
		divisor > 1 ? divisor /=1:divisor;
		divisor!=0?len /= divisor:len;
		int wid = len* this->sftext.getCharacterSize();
		this->setOrigin(sf::Vector2f(0, 0));
		this->sftext.setPosition(sf::Vector2f(this->getPosition().x + ((this->getSize().x - wid) / 2), (float)this->getPosition().y + (this->shape.getSize().y - font_size*multipliery*2) /2));
	}
	
	this->sftext.setFillColor(sf::Color::Black);
}

std::string button::getName()
{
	return name;
}

