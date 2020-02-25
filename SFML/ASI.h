#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "PreDef.h"
#include "debug_utilities.h"
#include "Initialize.h"

class clickableObject;
class container;
class board;

//AppStateInfo contains pointers to important objects, and general states of application parameters, such as current score, turn, but also global params loaded from file
class AppStateInfo
{
public:
	//world
	container*world_root = nullptr;
	clickableObject* obj=nullptr;
	sf::Vector2f mouse_pos = sf::Vector2f(0, 0);
	sf::Vector2i mouse_pixel_pos = sf::Vector2i(0, 0);
	int turn = player1;
	void*other = nullptr;
	int scoreP1 = 0;
	int scoreP2 = 0;
	int moves_made= 0;
	container*turnbtn_container_ptr = nullptr;
	container*resultBtn = nullptr;

	//asi methods
	AppStateInfo()=default;
	~AppStateInfo();
	AppStateInfo(const AppStateInfo&);
	AppStateInfo(const AppStateInfo*);

	//ini
	initialize ini;
	std::string ini_path;

	//ini methods
	int content_str_to_bool(std::string content);
	void load_ini(std::string,AppStateInfo*&);
	void param_switch(std::string&,std::string&);
	
	
	typedef void (AppStateInfo::*ASIFunction)(void*&);
	ASIFunction function;
	bool clicked(container*root, sf::Vector2i mouse_vec, clickableObject*&ret_ptr, bool &found);
	//MAKES
	void make_background(container*&root, AppStateInfo*&);
	void make_menu(container*&root, AppStateInfo *&);
	std::string turnbtntext(AppStateInfo*&);
	void make_turn_btn(container*&root, int no, board*&brd, AppStateInfo*&ASI);
	void make_board(container*&root, int no, AppStateInfo*&);
	
};


