#pragma once
#include "stdafx.h"

#pragma region ASI


AppStateInfo::~AppStateInfo()
{

}

AppStateInfo::AppStateInfo(const AppStateInfo &oldASI)
{
	world_root = oldASI.world_root;
	mouse_pos = oldASI.mouse_pos;
	obj = oldASI.obj;
	turn = oldASI.turn;
	other = oldASI.other;
}

AppStateInfo::AppStateInfo(const AppStateInfo *oldASI)
{
	world_root = oldASI->world_root;
	mouse_pos = oldASI->mouse_pos;
	obj = oldASI->obj;
	turn = oldASI->turn;
	other = oldASI->other;
}

int AppStateInfo::content_str_to_bool(std::string content)
{
	if (content=="FALSE"||content=="false")
	{
		return false;
	}
	if (content=="TRUE"||content=="true")
	{
		return true;
	}
	return -1;
}

void AppStateInfo::param_switch(std::string& word,std::string& content)
{
	void*param_ptr = nullptr;
	if (word == "WINDOW_TITLE")
	{
		this->ini.window_title = content;
		return;
	}
	if (word == "BACKGROUND")
	{
		param_ptr = &(this->ini.background);
		((texture_data*)param_ptr)->obj_texture_path = content;
		((texture_data*)param_ptr)->load_texture(((texture_data*)param_ptr)->obj_texture_path);
		return;
	}
	if (word == "BACKGROUND_CUT_BOOLEAN")
	{
		int res = content_str_to_bool(content);
		if (res >= 0)
		{
			ini.background_scaling = res;
			return;
		}
		this->ini.background_scaling = std::stoi(content);
		return;
	}
	if (word == "BACKGROUND_ORIGIN_X")
	{
		this->ini.background_origin_x = std::stoi(content);
		return;
	}
	if (word == "BACKGROUND_ORIGIN_Y")
	{
		this->ini.background_origin_y = std::stoi(content);
		return;
	}
	if (word == "BACKGROUND_X")
	{
		this->ini.background_x = std::stoi(content);
		return;
	}
	if (word == "BACKGROUND_Y")
	{
		this->ini.background_y = std::stoi(content);
		return;
	}
	if (word == "MENU_BUTTONS")
	{
		param_ptr = &(this->ini.menu_buttons);
		((texture_data*)param_ptr)->obj_texture_path = content;
		((texture_data*)param_ptr)->load_texture(((texture_data*)param_ptr)->obj_texture_path);
		return;
	}
	if (word == "TURN_BUTTON")
	{
		param_ptr = &(this->ini.turn_button);
		((texture_data*)param_ptr)->obj_texture_path = content;
		((texture_data*)param_ptr)->load_texture(((texture_data*)param_ptr)->obj_texture_path);
		return;
	}
	if (word == "SPAWN_BUTTONS")
	{
		param_ptr = &(this->ini.spawn_buttons);
		((texture_data*)param_ptr)->obj_texture_path = content;
		((texture_data*)param_ptr)->load_texture(((texture_data*)param_ptr)->obj_texture_path);
		return;
	}
	if (word == "PUSH_BUTTONS")
	{
		param_ptr = &(this->ini.push_buttons);
		((texture_data*)param_ptr)->obj_texture_path = content;
		((texture_data*)param_ptr)->load_texture(((texture_data*)param_ptr)->obj_texture_path);
		return;
	}
	if (word == "MERGE_BUTTONS")
	{
		param_ptr = &(this->ini.merge_buttons);
		((texture_data*)param_ptr)->obj_texture_path = content;
		((texture_data*)param_ptr)->load_texture(((texture_data*)param_ptr)->obj_texture_path);
		return;
	}
	if (word == "SPLIT_UP_BUTTONS")
	{
		param_ptr = &(this->ini.split_up_buttons);
		((texture_data*)param_ptr)->obj_texture_path = content;
		((texture_data*)param_ptr)->load_texture(((texture_data*)param_ptr)->obj_texture_path);
		return;
	}
	if (word == "SPLIT_DOWN_BUTTONS")
	{
		param_ptr = &(this->ini.split_down_buttons);
		((texture_data*)param_ptr)->obj_texture_path = content;
		((texture_data*)param_ptr)->load_texture(((texture_data*)param_ptr)->obj_texture_path);
		return;
	}
	if (word == "BATTLE_BUTTONS")
	{
		param_ptr = &(this->ini.battle_buttons);
		((texture_data*)param_ptr)->obj_texture_path = content;
		((texture_data*)param_ptr)->load_texture(((texture_data*)param_ptr)->obj_texture_path);
		return;
	}

	if (word == "FIELDS_BG")
	{
		param_ptr = &(this->ini.fields_bg);
		((texture_data*)param_ptr)->obj_texture_path = content;
		((texture_data*)param_ptr)->load_texture(((texture_data*)param_ptr)->obj_texture_path);
		return;
	}
	if (word == "UNITS_RED")
	{
		param_ptr = &(this->ini.units_red);
		((texture_data*)param_ptr)->obj_texture_path = content;
		((texture_data*)param_ptr)->load_texture(((texture_data*)param_ptr)->obj_texture_path);
		return;
	}
	if (word == "UNITS_BLUE")
	{
		param_ptr = &(this->ini.units_blue);
		((texture_data*)param_ptr)->obj_texture_path = content;
		((texture_data*)param_ptr)->load_texture(((texture_data*)param_ptr)->obj_texture_path);
		return;
	}
	//
	if (word == "MOVES_PER_TURN")
	{
		this->ini.moves_per_turn = std::stoi(content);
		return;
	}
	//
	if (word == "MAIN_FONT")
	{
		param_ptr = &(this->ini.mainfont);
		((font_data*)param_ptr)->font_path = content;
		((font_data*)param_ptr)->load_font(((font_data*)param_ptr)->font_path);
		return;
	}

	//
	if (word == "MANUAL")
	{
		ini.manual_path = content;
		return;
	}
	if (word == "DEBUG_MODE_PRINT")
	{
		int res = content_str_to_bool(content);
		if (res >= 0)
		{
			ini.printdebugs = res;
			return;
		}
		ini.printdebugs = stoi(content);
		return;
	}
	if (word == "RESULT_INSTANT_GAME_RESET")
	{
		int res = content_str_to_bool(content);
		if (res>=0)
		{
			ini.result_instant_reset = res;
			return;
		}
		ini.result_instant_reset = stoi(content);
		return;
	}
}

void AppStateInfo::load_ini(std::string ini_path,AppStateInfo*&ASI)
{
	std::ifstream iniF;
	iniF.open(CONFIG_PATH,std::ios::in);
	std::stringstream ss;
	std::string line;
	std::string temp;
	std::string temp_next;
	if (!iniF.is_open())
	{
		stdprint(CONFIG_PATH" not loaded",ASI);
		throw EXQUIT;
	}
	else
	{
		while (std::getline(iniF,line))
		{
			ss << line;
			if (line=="")
			{
				continue;
			}
			while (ss)
			{
				ss >> temp;
				if (temp=="#define")
				{
					ss >> temp;
					ss >> temp_next;
					this->param_switch(temp, temp_next);
					ss.str("");
					ss.clear();
					ss.clear();
					break;
				}
				else
				{
					ss.str("");
					ss.clear();
					break;
				}
			}
		}
	}
	return;
}

bool AppStateInfo::clicked(container*root, sf::Vector2i mouse_vec, clickableObject*&ret_ptr, bool &found)
{
	container*cptr = root;
	if (!root)
	{
		return false;
	}
	clickableObject*optr = root->obj;
	if (!cptr)
	{
		return false;
	}
	if (found)
	{
		return true;
	}
	else
	{
		while (cptr)
		{
			if (found)
			{
				return true;
			}
			if (cptr->plist)
			{
				clicked(cptr->plist, mouse_vec, ret_ptr, found);
			}
			if (found)
			{
				return true;
			}
			if (cptr->pnext)
			{
				clicked(cptr->pnext, mouse_vec, ret_ptr, found);
			}
			if (found)
			{
				return true;
			}
			if (cptr->obj)
			{
				if (cptr->obj->getGlobalBounds().contains(sf::Vector2f(mouse_vec)))
				{
					found = true;
					ret_ptr = cptr->obj;
				}
				break;
			}
			else
			{
				return false;
			}
		}
		return false;
	}
}

#pragma endregion

#pragma region MAKES

void AppStateInfo::make_background(container *& root, AppStateInfo*&ASI)
{
	if (root)
	{
		return;
	}
	else
	{
		root = new container(new background("BND", WINDOWSIZEX, WINDOWSIZEY, ASI), nullptr, nullptr);
	}
}

void AppStateInfo::make_menu(container*&root, AppStateInfo *&ASI)
{
	if (!root)
	{
		return;
	}
	int x = 150;
	int y = 100;
	int offset = 150;
	int margin = 10;
	int menu_font_size = 10;
	const int resbtn_id = 3;
	container* empty_cont = new container();
	root->add_container_behind(root, root->getLenght(root) + 1, root->getWidthAt(root, root->getLenght(root)), down, empty_cont);
	int tab[MAIN_BUTTONS_COUNT] = { Enewgame,Eprintmanual,Equit,Eemptyfxno };
	sf::String texts[MAIN_BUTTONS_COUNT] = { (sf::String)"NewGame",(sf::String)"Manual", (sf::String)"Exit", (sf::String)RESULT_TITLE + std::to_string(ASI->scoreP1) + "-" + std::to_string(ASI->scoreP2) };
	for (int i = 0; i < MAIN_BUTTONS_COUNT; i++)
	{
		button *btn = new button(std::to_string(i));
		btn->setPosition(sf::Vector2f((float)margin, (float)(margin + (offset *i))));
		btn->setColor(sf::Color::White);
		btn->sftext.setFont(ASI->ini.mainfont.font);
		btn->setText(texts[i], true);
		btn->SetClicked(tab[i]);
		btn->shape.setTexture(&(ASI->ini.menu_buttons.obj_texture));
		container* cont = new container(btn, nullptr, nullptr);
		root->add_container_behind(root, root->getLenght(root) + 1, root->getWidthAt(root, root->getLenght(root)), right, cont);
		if (i == resbtn_id)
		{
			ASI->resultBtn = cont;
		}
	}
}

std::string AppStateInfo::turnbtntext(AppStateInfo*&ASI)
{
	std::string playername = "";
	std::string _ret;
	if (ASI->turn == player1)
	{
		playername = "1-BLUE";
	}
	if (ASI->turn == player2)
	{
		playername = "1-RED";
	}
	_ret = TURNBTN_TITLE "\n Player " + playername + "\n Made " + std::to_string(ASI->moves_made) + " moves \n out of" + std::to_string(ASI->ini.moves_per_turn);
	return _ret;
}

void AppStateInfo::make_turn_btn(container*&root, int no, board*&brd, AppStateInfo*&ASI)
{
	int menu_font_size = 10;
	int turnbtnwidth = 200;
	container* empty_cont = new container();
	root->add_container_behind(root, root->getLenght(root) + 1, root->getWidthAt(root, root->getLenght(root)), down, empty_cont);
	button *btn = new button("BRD" + std::to_string(no) + "turnbtn");
	btn->setSize(sf::Vector2f((float)turnbtnwidth, (float)turnbtnwidth));
	btn->setColor(sf::Color::White);
	btn->setOrigin(sf::Vector2f(0, 0));
	btn->setPosition(sf::Vector2f((float)((brd->getPosition().x + (brd->getSize().x) / 2) - (turnbtnwidth / 2)), (float)((brd->getPosition().y + brd->getSize().y) + (BUTTON_SIZE_DEF / 2))));
	btn->SetClicked(Eturnbtn_clicked);
	btn->setText(turnbtntext(ASI), true);
	btn->sftext.setFont(ASI->ini.mainfont.font);
	btn->shape.setTexture(&(ASI->ini.turn_button.obj_texture));
	container* cont = new container(btn, nullptr, nullptr);
	root->add_container_behind(root, root->getLenght(root) + 1, root->getWidthAt(root, root->getLenght(root)), down, cont);
	ASI->turnbtn_container_ptr = cont;
}

void AppStateInfo::make_board(container*&root, int no, AppStateInfo*&ASI)
{
	const int marginL = 200;

	int a[BTNTYPESCOUNT] = { Espawnbtn_hit,Epush_units,Emerge_units,Esplit_units_up,Esplit_units_down,Ebattle };

	texture_data **temptextures = new texture_data*[BTNTYPESCOUNT];
	texture_data *b[BTNTYPESCOUNT] = { &(ASI->ini.spawn_buttons),&(ASI->ini.push_buttons),&(ASI->ini.merge_buttons),&(ASI->ini.split_up_buttons),&(ASI->ini.split_down_buttons),&(ASI->ini.battle_buttons) };

	for (int i = 0; i < BTNTYPESCOUNT; i++)
	{
		temptextures[i] = *&b[i];
	}
	board*brd = new board(std::to_string(no), root, Eboard_clicked, a, temptextures, &ASI->ini.fields_bg, &ASI->ini.units_blue, &ASI->ini.units_red);
	delete[]temptextures;
	temptextures = nullptr;
	brd->setPosition(sf::Vector2f(MENUX, marginL));
	container*cont = new container(brd, nullptr, nullptr);
	root->add_container_behind(root, root->getLenght(root) + 1, 0, down, cont);
	make_turn_btn(root, no, brd, ASI);
}

#pragma endregion
