#pragma once
#include "ASI.h"

class AppStateInfo;
class board;
class object;
class clickableObject;

#define FUNCTIONCCOUNT 16
enum functionsEnum
{
	Eemptyfxno = 0,
	Enewgame = 1,
	Eprintmanual = 2,
	Equit = 3,
	Eturnbtn_update = 4,
	Eturnbtn_clicked = 5,
	Eboard_clicked = 6,
	Espawnbtn_hit = 7,
	Epush_units = 8,
	Epush_unit = 9,
	Emerge_units = 10,
	Esplit_units_up = 11,
	Esplit_units_down = 12,
	Ebattle = 13,
	Eresult_update = 14,
	Eplayerwon = 15
};


class clickable
{
public:
	clickable();
	~clickable();
	typedef void (clickable::*ClickedFunction)(void*&);
	ClickedFunction function;
	void SetClicked(int i);

	void empty_fx_no(void*&);
	void newgame(void*&);
	void printmanual(void*&);
	void quit(void*&);
	void turnbtn_update(void*&);
	void turnbtn_clicked(void*&);
	void board_clicked(void*&);
	void spawnbtn_hit(void*&);
	void push_units(void*&);
	void push_unit(void*&);
	void merge_units(void*&);
	void split_units_up(void*&);
	void split_units_down(void*&);
	void battle(void*&);
	void result_update(void*&);
	void playerwon(void*&);

	ClickedFunction tab[FUNCTIONCCOUNT] =
	{
	&clickable::empty_fx_no,
	&clickable::newgame,
	&clickable::printmanual,
	&clickable::quit,
	&clickable::turnbtn_update,
	&clickable::turnbtn_clicked,
	&clickable::board_clicked,
	&clickable::spawnbtn_hit,
	&clickable::push_units,
	&clickable::push_unit,
	&clickable::merge_units,
	&clickable::split_units_up,
	&clickable::split_units_down,
	&clickable::battle,
	&clickable::result_update,
	&clickable::playerwon, };
};


