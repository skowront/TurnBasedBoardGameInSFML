#include "stdafx.h"
void texture_data::load_texture(std::string path)
{
	if (!obj_texture.loadFromFile(path))
	{
		std::cout << "texture" + path + " not loaded" << std::endl;
	}

}

void texture_data::load_texture(std::string path, object &obj)
{
	if (!obj_texture.loadFromFile(path))
	{
		std::cout << "texture" + path + " not loaded" << std::endl;
	}
	else
	{
		obj.shape.setTexture(&obj_texture, false);
	}
}


void font_data::load_font(std::string path)
{
	if (!this->font.loadFromFile(path))
	{
		std::cout << "texture" + path + " not loaded" << std::endl;
	}
}

texture_data::~texture_data()
{

}

font_data::~font_data()
{

}

initialize::~initialize()
{

}