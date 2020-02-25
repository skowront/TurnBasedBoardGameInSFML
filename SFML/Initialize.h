#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdlib>

class object;

//representation of key parameters of textures
struct texture_data
{
public:
	std::string obj_texture_path;
	sf::Texture obj_texture;
	void load_texture(std::string);
	void load_texture(std::string, object &obj);

	~texture_data();
};

//representation of key parameters of fonts
struct font_data
{
public:
	std::string font_path;
	sf::Font font;
	void load_font(std::string);

	~font_data();
};

//class contains parameters that are expected to be loaded from file
class initialize
{
public:
	//api
	std::string window_title;
	std::string manual_path;
	bool printdebugs = true;
	int result_instant_reset = true;
	//background
	texture_data background;
	int background_x = 1;
	int background_y = 1;
	int background_origin_x = 1;
	int background_origin_y = 1;
	int background_scaling = false;


	//buttons
	texture_data menu_buttons;
	texture_data turn_button;
	texture_data spawn_buttons;
	texture_data push_buttons;
	texture_data merge_buttons;
	texture_data split_up_buttons;
	texture_data split_down_buttons;
	texture_data battle_buttons;

	//units
	texture_data units_blue;
	texture_data units_red;

	texture_data fields_bg;
	//
	int moves_per_turn = 0;
	//
	font_data mainfont;

	~initialize();
};
