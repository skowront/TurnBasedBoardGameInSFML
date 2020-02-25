#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>

class container;
class clickable;
class clickableObject;
//represents any object that may be drawn on the screen, is abstract
class object : public sf::Drawable
{
public:
	container*world;
	sf::RectangleShape shape;
	std::string name;
	sf::Texture texture;
	std::string texture_path;
	sf::String sfstr;
	sf::Text sftext;
	sf::Font font;
	//void(*clicked)(void*&)=&null_click;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates state)const;
	virtual void info();
	virtual sf::FloatRect getGlobalBounds() const;
	virtual std::string getName();
	//GETTERS
	virtual sf::Color getColor();
	virtual sf::Vector2f getSize();
	virtual sf::Vector2f getPosition();
	virtual sf::Vector2f getOrigin();

	//SETTERS
	virtual void setText(std::string,bool positioning);
	virtual void setColor(sf::Color);
	virtual void setSize(sf::Vector2f);
	virtual void setPosition(sf::Vector2f);
	virtual void setOrigin(sf::Vector2f);
};

//represents container for an object, so it could be to sort and queue order of drawing






