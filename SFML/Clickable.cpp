
#include "stdafx.h"

clickable::clickable()
{
}

clickable::~clickable()
{
}

void clickable::SetClicked(int i)
{
	function = tab[i];
}

#pragma region clickables





void clickable::empty_fx_no(void*&)
{
	return;
}

void clickable::newgame(void*&ASI)
{
	bool temp = false;
	AppStateInfo*asi = (AppStateInfo*)ASI;
	asi->world_root->StructuralRemove(asi->world_root, ASI);
	asi->world_root = nullptr;
	asi->moves_made = 0;
	asi->turn = player1;
	asi->make_background(asi->world_root, (AppStateInfo*&)ASI);
	asi->make_menu(asi->world_root, asi);
	asi->make_board(asi->world_root, 1, (AppStateInfo*&)ASI);
	asi->clicked(asi->world_root, asi->mouse_pixel_pos, asi->obj, temp = false);
	stdprint("newgame", (AppStateInfo*&)ASI);
}

void clickable::printmanual(void*&ASI)
{
	std::ifstream file;
	file.open(((AppStateInfo*&)ASI)->ini.manual_path, std::ios::in);
	if (file.is_open())
	{
		int temp = ((AppStateInfo*&)ASI)->ini.printdebugs;
		((AppStateInfo*&)ASI)->ini.printdebugs = true;
		std::string line;
		while (std::getline(file, line))
		{
			stdprint(line, (AppStateInfo*&)ASI);
		}
		((AppStateInfo*&)ASI)->ini.printdebugs = temp;
	}
}

void clickable::quit(void*&)
{
	throw  EXQUIT;
}

void clickable::turnbtn_update(void*&ASI)
{
	if (!(((AppStateInfo*&)(ASI))->turnbtn_container_ptr))
	{
		return;
	}
	(((AppStateInfo*&)(ASI))->turnbtn_container_ptr->obj)->sfstr = sf::String(((AppStateInfo*&)ASI)->turnbtntext((AppStateInfo*&)ASI));
	(((AppStateInfo*&)(ASI))->turnbtn_container_ptr->obj)->sftext.setString(((button*)(((AppStateInfo*&)(ASI))->turnbtn_container_ptr->obj))->sfstr);
}

void clickable::turnbtn_clicked(void*&ASI)
{
	stdprint("TURN WAS " + std::to_string(((AppStateInfo*)ASI)->turn), (AppStateInfo*&)ASI);
	((AppStateInfo*)ASI)->turn == player1 ? ((AppStateInfo*)ASI)->turn = player2, true : ((AppStateInfo*)ASI)->turn = player1, false;
	stdprint("TURN IS " + std::to_string(((AppStateInfo*)ASI)->turn), (AppStateInfo*&)ASI);
	((AppStateInfo*)ASI)->moves_made = 0;
	turnbtn_update(ASI);
}

void clickable::board_clicked(void*& ASI)
{
	if (!ASI)
	{
		return;
	}
	int x = 0;
	int y = 0;

	for (int i = 0; i < BTNTYPESCOUNT; i++)
	{
		for (int j = 0; j < ((board*)(((AppStateInfo*)ASI)->obj))->xD; j++)
		{
			if (((AppStateInfo*)ASI)->turn == player1)
			{
				ASI ? (((board*)(((AppStateInfo*)ASI)->obj)) ? (((board*)(((AppStateInfo*)ASI)->obj))->player1btns
					? (((board*)(((AppStateInfo*)ASI)->obj))->player1btns[i][j].getGlobalBounds().contains(sf::Vector2f(((AppStateInfo*)ASI)->mouse_pos))
						? x = i, y = j, ((AppStateInfo*)ASI)->other = (int*)malloc(2 * sizeof(int)), ((int*)(((AppStateInfo*)ASI)->other))[row_index] = y, ((int*)(((AppStateInfo*)ASI)->other))[column_index] = x,
						((board*)(((AppStateInfo*)ASI)->obj))->player1btns[i][j].clicked((void*&)ASI),
						((((AppStateInfo*)ASI)->other) ? delete ((AppStateInfo*)ASI)->other, ((AppStateInfo*)ASI)->other = nullptr, true : false), true : false) : false) : false) : false;
			}
		}
	}
	for (int i = 0; i < BTNTYPESCOUNT; i++)
	{
		if (((AppStateInfo*)ASI)->turn == player2)
		{
			for (int j = 0; j < ((board*)(((AppStateInfo*)ASI)->obj))->xD; j++)
			{
				ASI ? (((board*)(((AppStateInfo*)ASI)->obj)) ? (((board*)(((AppStateInfo*)ASI)->obj))->player2btns
					? (((board*)(((AppStateInfo*)ASI)->obj))->player2btns[i][j].getGlobalBounds().contains(sf::Vector2f(((AppStateInfo*)ASI)->mouse_pos))
						? x = i, y = j, ((AppStateInfo*)ASI)->other = (int*)malloc(2 * sizeof(int)), ((int*)(((AppStateInfo*)ASI)->other))[row_index] = y, ((int*)(((AppStateInfo*)ASI)->other))[column_index] = x,
						((board*)(((AppStateInfo*)ASI)->obj))->player2btns[i][j].clicked((void*&)ASI),
						((((AppStateInfo*)ASI)->other) ? delete ((AppStateInfo*)ASI)->other, ((AppStateInfo*)ASI)->other = nullptr, true : false), true : false) : false) : false) : false;
			}
		}
	}

	stdprint("BRD clicked", (AppStateInfo*&)ASI);
}

void clickable::spawnbtn_hit(void*& ASI)
{
	int row = ((int*)(((AppStateInfo*)ASI)->other))[row_index];
	board* brd = ((board*)((AppStateInfo*)ASI)->obj);
	switch (((AppStateInfo*)ASI)->turn)
	{
	case player1:
		if (brd->tab[FIELDCOUNT - FIELDCOUNT][row].units != nullptr)
		{
			if (brd->tab[FIELDCOUNT - FIELDCOUNT][row].units->owner == player1)
			{
				brd->tab[FIELDCOUNT - FIELDCOUNT][row].units->increment();
				((AppStateInfo*)ASI)->moves_made++;
			}
			else
			{
				return;
			}
		}
		else
		{
			brd->tab[FIELDCOUNT - FIELDCOUNT][row].units = new unit("n-th-unit", sf::Vector2f(brd->tab[FIELDCOUNT - FIELDCOUNT][row].getPosition().x + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2), brd->tab[FIELDCOUNT - FIELDCOUNT][row].getPosition().y + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2)), player1, (AppStateInfo*&)ASI);
			((AppStateInfo*)ASI)->moves_made++;
		}
		break;
	case player2:
		if (brd->tab[FIELDCOUNT - 1][row].units != nullptr)
		{
			if (brd->tab[FIELDCOUNT - 1][row].units->owner == player2)
			{
				brd->tab[FIELDCOUNT - 1][row].units->increment();
				((AppStateInfo*)ASI)->moves_made++;
			}
			else
			{
				return;
			}
		}
		else
		{
			brd->tab[FIELDCOUNT - 1][row].units = new unit("n-th-unit", sf::Vector2f(brd->tab[FIELDCOUNT - 1][row].getPosition().x + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2), brd->tab[FIELDCOUNT - 1][row].getPosition().y + (FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2), player2, (AppStateInfo*&)ASI);
			((AppStateInfo*)ASI)->moves_made++;
		}
		break;
	default:
		break;
	}
}

void clickable::battle(void*& ASI)
{
	//PLAYER 1
	//i/r+1 | i+1/r+1 | i+2/r+1
	//i/r   | i+1/r   | i+2/r  |i->attacking unit
	//i/r-1 | i+1/r-1 | i+2/r-1

	//PLAYER 2
	//i-2/r+1 | i-1/r+1 | i.r+1
	//i-2/r   | i-1/r   | i  |
	//i-2/r-1 | i-1/r-1 | i/r-1
	int row = ((int*)(((AppStateInfo*)ASI)->other))[row_index];
	board* brd = ((board*)((AppStateInfo*)ASI)->obj);
	unit*unit_ptr = nullptr;
	int totalAttackerPower = NULL;
	int totalDefenderPower = NULL;
	bool sth_done = false;
	switch (((AppStateInfo*)ASI)->turn)
	{
	case player1:
		for (int i = FIELDCOUNT - FIELDCOUNT; i < FIELDCOUNT - 1; i++)
		{
			//special for row fieldcount-2, where there is no sufficient number of fields to calculate
			if (i == FIELDCOUNT - 2)
			{
				if (brd->tab[i][row].units)
				{
					if (brd->tab[i][row].units->owner == player1)
					{
						if (brd->tab[i + 1][row].units)
						{
							if (brd->tab[i + 1][row].units->owner == player2)
							{
								sth_done = true;
								//case right top corner
								if (row == FIELDCOUNT - FIELDCOUNT)
								{
									brd->tab[i][row].units ? (brd->tab[i][row].units->owner == player1 ? totalAttackerPower += brd->tab[i][row].units->power : false) : false;//sum attackers
									brd->tab[i][row + 1].units ? (brd->tab[i][row + 1].units->owner == player1 ? totalAttackerPower += brd->tab[i][row + 1].units->power : false) : false;
									brd->tab[i + 1][row + 1].units ? (brd->tab[i + 1][row + 1].units->owner == player1 ? totalAttackerPower += brd->tab[i + 1][row + 1].units->power : false) : false;

									brd->tab[i + 1][row].units ? (brd->tab[i + 1][row].units->owner == player2 ? totalDefenderPower += brd->tab[i + 1][row].units->power : false) : false;//sum defenders
									brd->tab[i + 1][row + 1].units ? (brd->tab[i + 1][row + 1].units->owner == player2 ? totalDefenderPower += brd->tab[i + 1][row + 1].units->power : false) : false;
									brd->tab[i][row + 1].units ? (brd->tab[i][row + 1].units->owner == player2 ? totalDefenderPower += brd->tab[i][row + 1].units->power : false) : false;
									stdprint("Battle at x: " + std::to_string(i) + " y: " + std::to_string(row) + " Attacker: " + std::to_string(totalAttackerPower) + " Defender: " + std::to_string(totalDefenderPower), (AppStateInfo*&)ASI);
									int totalValue = abs(totalAttackerPower - totalDefenderPower);
									brd->tab[i][row].units->power -= totalDefenderPower;
									if (brd->tab[i][row].units->power <= 0)//kill?power=<0
									{
										delete brd->tab[i][row].units;
										brd->tab[i][row].units = nullptr;
									}
									brd->tab[i + 1][row].units->power -= totalAttackerPower;
									if (brd->tab[i + 1][row].units->power <= 0)//kill?power=<0
									{
										delete brd->tab[i + 1][row].units;
										brd->tab[i + 1][row].units = nullptr;
										if (brd->tab[i][row].units)//if attacker not killed, defender killed, new versor unit in defender's place, attacker's power -1
										{
											//new unit
											brd->tab[i + 1][row].units = new unit("n-th-unit", sf::Vector2f(brd->tab[i + 1][row].getPosition().x + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2), brd->tab[i + 1][row].getPosition().y + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2)), player1, (AppStateInfo*&)ASI);
											//decrement attacker
											brd->tab[i][row].units->power -= 1;
											if (brd->tab[i][row].units->power <= 0)//kill?power=<0
											{
												delete brd->tab[i][row].units;
												brd->tab[i][row].units = nullptr;
											}
										}
									}
									brd->tab[i][row].update((AppStateInfo*&)ASI);
									brd->tab[i + 1][row].update((AppStateInfo*&)ASI);
									continue;
								}
								//case right bottom corner
								if (row == FIELDCOUNT - 1)
								{
									brd->tab[i][row].units ? (brd->tab[i][row].units->owner == player1 ? totalAttackerPower += brd->tab[i][row].units->power : false) : false;//sum attackers
									brd->tab[i][row - 1].units ? (brd->tab[i][row - 1].units->owner == player1 ? totalAttackerPower += brd->tab[i][row - 1].units->power : false) : false;
									brd->tab[i + 1][row - 1].units ? (brd->tab[i + 1][row - 1].units->owner == player1 ? totalAttackerPower += brd->tab[i + 1][row - 1].units->power : false) : false;

									brd->tab[i + 1][row].units ? (brd->tab[i + 1][row].units->owner == player2 ? totalDefenderPower += brd->tab[i + 1][row].units->power : false) : false;//sum defenders
									brd->tab[i + 1][row - 1].units ? (brd->tab[i + 1][row - 1].units->owner == player2 ? totalDefenderPower += brd->tab[i + 1][row - 1].units->power : false) : false;
									brd->tab[i][row - 1].units ? (brd->tab[i][row - 1].units->owner == player2 ? totalDefenderPower += brd->tab[i][row - 1].units->power : false) : false;
									stdprint("Battle at x: " + std::to_string(i) + " y: " + std::to_string(row) + " Attacker: " + std::to_string(totalAttackerPower) + " Defender: " + std::to_string(totalDefenderPower), (AppStateInfo*&)ASI);
									int totalValue = abs(totalAttackerPower - totalDefenderPower);
									brd->tab[i][row].units->power -= totalDefenderPower;
									if (brd->tab[i][row].units->power <= 0)//kill?power=<0
									{
										delete brd->tab[i][row].units;
										brd->tab[i][row].units = nullptr;
									}
									brd->tab[i + 1][row].units->power -= totalAttackerPower;
									if (brd->tab[i + 1][row].units->power <= 0)//kill?power=<0
									{
										delete brd->tab[i + 1][row].units;
										brd->tab[i + 1][row].units = nullptr;
										if (brd->tab[i][row].units)//if attacker not killed, defender killed, new versor unit in defender's place, attacker's power -1
										{
											//new unit
											brd->tab[i + 1][row].units = new unit("n-th-unit", sf::Vector2f(brd->tab[i + 1][row].getPosition().x + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2), brd->tab[i + 1][row].getPosition().y + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2)), player1, (AppStateInfo*&)ASI);
											//decrement attacker
											brd->tab[i][row].units->power -= 1;
											if (brd->tab[i][row].units->power <= 0)//kill?power=<0
											{
												delete brd->tab[i][row].units;
												brd->tab[i][row].units = nullptr;
											}
										}
									}
									brd->tab[i][row].update((AppStateInfo*&)ASI);
									brd->tab[i + 1][row].update((AppStateInfo*&)ASI);
									continue;
								}
								//case any other in last row
								else
								{
									brd->tab[i][row].units ? (brd->tab[i][row].units->owner == player1 ? totalAttackerPower += brd->tab[i][row].units->power : false) : false;//sum attackers
									brd->tab[i][row + 1].units ? (brd->tab[i][row + 1].units->owner == player1 ? totalAttackerPower += brd->tab[i][row + 1].units->power : false) : false;
									brd->tab[i + 1][row + 1].units ? (brd->tab[i + 1][row + 1].units->owner == player1 ? totalAttackerPower += brd->tab[i + 1][row + 1].units->power : false) : false;
									brd->tab[i][row - 1].units ? (brd->tab[i][row - 1].units->owner == player1 ? totalAttackerPower += brd->tab[i][row - 1].units->power : false) : false;
									brd->tab[i + 1][row - 1].units ? (brd->tab[i + 1][row - 1].units->owner == player1 ? totalAttackerPower += brd->tab[i + 1][row - 1].units->power : false) : false;


									brd->tab[i + 1][row].units ? (brd->tab[i + 1][row].units->owner == player2 ? totalDefenderPower += brd->tab[i + 1][row].units->power : false) : false;//sum defenders
									brd->tab[i + 1][row + 1].units ? (brd->tab[i + 1][row + 1].units->owner == player2 ? totalDefenderPower += brd->tab[i + 1][row + 1].units->power : false) : false;
									brd->tab[i][row + 1].units ? (brd->tab[i][row + 1].units->owner == player2 ? totalDefenderPower += brd->tab[i][row + 1].units->power : false) : false;
									brd->tab[i][row - 1].units ? (brd->tab[i][row - 1].units->owner == player2 ? totalDefenderPower += brd->tab[i][row - 1].units->power : false) : false;
									brd->tab[i + 1][row - 1].units ? (brd->tab[i + 1][row - 1].units->owner == player2 ? totalDefenderPower += brd->tab[i + 1][row - 1].units->power : false) : false;
									stdprint("Battle at x: " + std::to_string(i) + " y: " + std::to_string(row) + " Attacker: " + std::to_string(totalAttackerPower) + " Defender: " + std::to_string(totalDefenderPower), (AppStateInfo*&)ASI);
									int totalValue = abs(totalAttackerPower - totalDefenderPower);
									brd->tab[i][row].units->power -= totalDefenderPower;
									if (brd->tab[i][row].units->power <= 0)//kill?power=<0
									{
										delete brd->tab[i][row].units;
										brd->tab[i][row].units = nullptr;
									}
									brd->tab[i + 1][row].units->power -= totalAttackerPower;
									if (brd->tab[i + 1][row].units->power <= 0)//kill?power=<0
									{
										delete brd->tab[i + 1][row].units;
										brd->tab[i + 1][row].units = nullptr;
										if (brd->tab[i][row].units)//if attacker not killed, defender killed, new versor unit in defender's place, attacker's power -1
										{
											//new unit
											brd->tab[i + 1][row].units = new unit("n-th-unit", sf::Vector2f(brd->tab[i + 1][row].getPosition().x + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2), brd->tab[i + 1][row].getPosition().y + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2)), player1, (AppStateInfo*&)ASI);
											//decrement attacker
											brd->tab[i][row].units->power -= 1;
											if (brd->tab[i][row].units->power <= 0)//kill?power=<0
											{
												delete brd->tab[i][row].units;
												brd->tab[i][row].units = nullptr;
											}
										}
									}
									brd->tab[i][row].update((AppStateInfo*&)ASI);
									brd->tab[i + 1][row].update((AppStateInfo*&)ASI);
									continue;
								}
							}
						}
					}
				}
				continue;
			}
			//case any i=[0,...,7] (interior)
			else
			{
				if (brd->tab[i][row].units)
				{
					if (brd->tab[i][row].units->owner == player1)
					{
						if (brd->tab[i + 1][row].units)
						{
							if (brd->tab[i + 1][row].units->owner == player2)
							{
								sth_done = true;
								//case top
								if (row == FIELDCOUNT - FIELDCOUNT)
								{
									brd->tab[i][row].units ? (brd->tab[i][row].units->owner == player1 ? totalAttackerPower += brd->tab[i][row].units->power : false) : false;//sum attackers
									brd->tab[i][row + 1].units ? (brd->tab[i][row + 1].units->owner == player1 ? totalAttackerPower += brd->tab[i][row + 1].units->power : false) : false;
									brd->tab[i + 1][row + 1].units ? (brd->tab[i + 1][row + 1].units->owner == player1 ? totalAttackerPower += brd->tab[i + 1][row + 1].units->power : false) : false;
									brd->tab[i + 2][row].units ? (brd->tab[i + 2][row].units->owner == player1 ? totalAttackerPower += brd->tab[i + 2][row].units->power : false) : false;
									brd->tab[i + 2][row + 1].units ? (brd->tab[i + 2][row + 1].units->owner == player1 ? totalAttackerPower += brd->tab[i + 2][row + 1].units->power : false) : false;

									brd->tab[i + 1][row].units ? (brd->tab[i + 1][row].units->owner == player2 ? totalDefenderPower += brd->tab[i + 1][row].units->power : false) : false;//sum defenders
									brd->tab[i + 1][row + 1].units ? (brd->tab[i + 1][row + 1].units->owner == player2 ? totalDefenderPower += brd->tab[i + 1][row + 1].units->power : false) : false;
									brd->tab[i][row + 1].units ? (brd->tab[i][row + 1].units->owner == player2 ? totalDefenderPower += brd->tab[i][row + 1].units->power : false) : false;
									brd->tab[i + 2][row].units ? (brd->tab[i + 2][row].units->owner == player2 ? totalDefenderPower += brd->tab[i + 2][row].units->power : false) : false;//sum defenders
									brd->tab[i + 2][row + 1].units ? (brd->tab[i + 2][row + 1].units->owner == player2 ? totalDefenderPower += brd->tab[i + 2][row + 1].units->power : false) : false;
									stdprint("Battle at x: " + std::to_string(i) + " y: " + std::to_string(row) + " Attacker: " + std::to_string(totalAttackerPower) + " Defender: " + std::to_string(totalDefenderPower), (AppStateInfo*&)ASI);
									int totalValue = abs(totalAttackerPower - totalDefenderPower);
									brd->tab[i][row].units->power -= totalDefenderPower;
									if (brd->tab[i][row].units->power <= 0)//kill?power=<0
									{
										delete brd->tab[i][row].units;
										brd->tab[i][row].units = nullptr;
									}
									brd->tab[i + 1][row].units->power -= totalAttackerPower;
									if (brd->tab[i + 1][row].units->power <= 0)//kill?power=<0
									{
										delete brd->tab[i + 1][row].units;
										brd->tab[i + 1][row].units = nullptr;
										if (brd->tab[i][row].units)//if attacker not killed, defender killed, new versor unit in defender's place, attacker's power -1
										{
											//new unit
											brd->tab[i + 1][row].units = new unit("n-th-unit", sf::Vector2f(brd->tab[i + 1][row].getPosition().x + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2), brd->tab[i + 1][row].getPosition().y + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2)), player1, (AppStateInfo*&)ASI);
											//decrement attacker
											brd->tab[i][row].units->power -= 1;
											if (brd->tab[i][row].units->power <= 0)//kill?power=<0
											{
												delete brd->tab[i][row].units;
												brd->tab[i][row].units = nullptr;
											}
										}
									}
									brd->tab[i][row].update((AppStateInfo*&)ASI);
									brd->tab[i + 1][row].update((AppStateInfo*&)ASI);
									continue;
								}
								//case bottom
								if (row == FIELDCOUNT - 1)
								{
									brd->tab[i][row].units ? (brd->tab[i][row].units->owner == player1 ? totalAttackerPower += brd->tab[i][row].units->power : false) : false;//sum attackers
									brd->tab[i][row - 1].units ? (brd->tab[i][row - 1].units->owner == player1 ? totalAttackerPower += brd->tab[i][row - 1].units->power : false) : false;
									brd->tab[i + 1][row - 1].units ? (brd->tab[i + 1][row - 1].units->owner == player1 ? totalAttackerPower += brd->tab[i + 1][row - 1].units->power : false) : false;
									brd->tab[i + 2][row].units ? (brd->tab[i + 2][row].units->owner == player1 ? totalAttackerPower += brd->tab[i + 2][row].units->power : false) : false;
									brd->tab[i + 2][row - 1].units ? (brd->tab[i + 2][row - 1].units->owner == player1 ? totalAttackerPower += brd->tab[i + 2][row - 1].units->power : false) : false;

									brd->tab[i + 1][row].units ? (brd->tab[i + 1][row].units->owner == player2 ? totalDefenderPower += brd->tab[i + 1][row].units->power : false) : false;//sum defenders
									brd->tab[i + 1][row - 1].units ? (brd->tab[i + 1][row - 1].units->owner == player2 ? totalDefenderPower += brd->tab[i + 1][row - 1].units->power : false) : false;
									brd->tab[i][row - 1].units ? (brd->tab[i][row - 1].units->owner == player2 ? totalDefenderPower += brd->tab[i][row - 1].units->power : false) : false;
									brd->tab[i + 2][row].units ? (brd->tab[i + 2][row].units->owner == player2 ? totalDefenderPower += brd->tab[i + 2][row].units->power : false) : false;
									brd->tab[i + 2][row - 1].units ? (brd->tab[i + 2][row - 1].units->owner == player2 ? totalDefenderPower += brd->tab[i + 2][row - 1].units->power : false) : false;
									stdprint("Battle at x: " + std::to_string(i) + " y: " + std::to_string(row) + " Attacker: " + std::to_string(totalAttackerPower) + " Defender: " + std::to_string(totalDefenderPower), (AppStateInfo*&)ASI);
									int totalValue = abs(totalAttackerPower - totalDefenderPower);
									brd->tab[i][row].units->power -= totalDefenderPower;
									if (brd->tab[i][row].units->power <= 0)//kill?power=<0
									{
										delete brd->tab[i][row].units;
										brd->tab[i][row].units = nullptr;
									}
									brd->tab[i + 1][row].units->power -= totalAttackerPower;
									if (brd->tab[i + 1][row].units->power <= 0)//kill?power=<0
									{
										delete brd->tab[i + 1][row].units;
										brd->tab[i + 1][row].units = nullptr;
										if (brd->tab[i][row].units)//if attacker not killed, defender killed, new versor unit in defender's place, attacker's power -1
										{
											//new unit
											brd->tab[i + 1][row].units = new unit("n-th-unit", sf::Vector2f(brd->tab[i + 1][row].getPosition().x + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2), brd->tab[i + 1][row].getPosition().y + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2)), player1, (AppStateInfo*&)ASI);
											//decrement attacker
											brd->tab[i][row].units->power -= 1;
											if (brd->tab[i][row].units->power <= 0)//kill?power=<0
											{
												delete brd->tab[i][row].units;
												brd->tab[i][row].units = nullptr;
											}
										}
									}
									brd->tab[i][row].update((AppStateInfo*&)ASI);
									brd->tab[i + 1][row].update((AppStateInfo*&)ASI);
									continue;
								}
								//case any row=[0,...,7]
								else
								{
									brd->tab[i][row].units ? (brd->tab[i][row].units->owner == player1 ? totalAttackerPower += brd->tab[i][row].units->power : false) : false;//sum attackers
									brd->tab[i][row + 1].units ? (brd->tab[i][row + 1].units->owner == player1 ? totalAttackerPower += brd->tab[i][row + 1].units->power : false) : false;
									brd->tab[i + 1][row + 1].units ? (brd->tab[i + 1][row + 1].units->owner == player1 ? totalAttackerPower += brd->tab[i + 1][row + 1].units->power : false) : false;
									brd->tab[i][row - 1].units ? (brd->tab[i][row - 1].units->owner == player1 ? totalAttackerPower += brd->tab[i][row - 1].units->power : false) : false;
									brd->tab[i + 1][row - 1].units ? (brd->tab[i + 1][row - 1].units->owner == player1 ? totalAttackerPower += brd->tab[i + 1][row - 1].units->power : false) : false;
									brd->tab[i + 2][row].units ? (brd->tab[i + 2][row].units->owner == player1 ? totalAttackerPower += brd->tab[i + 2][row].units->power : false) : false;
									brd->tab[i + 2][row + 1].units ? (brd->tab[i + 2][row + 1].units->owner == player1 ? totalAttackerPower += brd->tab[i + 2][row + 1].units->power : false) : false;
									brd->tab[i + 2][row - 1].units ? (brd->tab[i + 2][row - 1].units->owner == player1 ? totalAttackerPower += brd->tab[i + 2][row - 1].units->power : false) : false;

									brd->tab[i + 1][row].units ? (brd->tab[i + 1][row].units->owner == player2 ? totalDefenderPower += brd->tab[i + 1][row].units->power : false) : false;//sum defenders
									brd->tab[i + 1][row + 1].units ? (brd->tab[i + 1][row + 1].units->owner == player2 ? totalDefenderPower += brd->tab[i + 1][row + 1].units->power : false) : false;
									brd->tab[i][row + 1].units ? (brd->tab[i][row + 1].units->owner == player2 ? totalDefenderPower += brd->tab[i][row + 1].units->power : false) : false;
									brd->tab[i][row - 1].units ? (brd->tab[i][row - 1].units->owner == player2 ? totalDefenderPower += brd->tab[i][row - 1].units->power : false) : false;
									brd->tab[i + 1][row - 1].units ? (brd->tab[i + 1][row - 1].units->owner == player2 ? totalDefenderPower += brd->tab[i + 1][row - 1].units->power : false) : false;
									brd->tab[i + 2][row].units ? (brd->tab[i + 2][row].units->owner == player2 ? totalDefenderPower += brd->tab[i + 2][row].units->power : false) : false;//sum defenders
									brd->tab[i + 2][row + 1].units ? (brd->tab[i + 2][row + 1].units->owner == player2 ? totalDefenderPower += brd->tab[i + 2][row + 1].units->power : false) : false;
									brd->tab[i + 2][row - 1].units ? (brd->tab[i + 2][row - 1].units->owner == player2 ? totalDefenderPower += brd->tab[i + 2][row - 1].units->power : false) : false;
									int totalValue = abs(totalAttackerPower - totalDefenderPower);
									stdprint("Battle at x: " + std::to_string(i) + " y: " + std::to_string(row) + " Attacker: " + std::to_string(totalAttackerPower) + " Defender: " + std::to_string(totalDefenderPower), (AppStateInfo*&)ASI);
									brd->tab[i][row].units->power -= totalDefenderPower;
									if (brd->tab[i][row].units->power <= 0)//kill?power=<0
									{
										delete brd->tab[i][row].units;
										brd->tab[i][row].units = nullptr;
									}
									brd->tab[i + 1][row].units->power -= totalAttackerPower;
									if (brd->tab[i + 1][row].units->power <= 0)//kill?power=<0
									{
										delete brd->tab[i + 1][row].units;
										brd->tab[i + 1][row].units = nullptr;
										if (brd->tab[i][row].units)//if attacker not killed, defender killed, new versor unit in defender's place, attacker's power -1
										{
											//new unit
											brd->tab[i + 1][row].units = new unit("n-th-unit", sf::Vector2f(brd->tab[i + 1][row].getPosition().x + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2), brd->tab[i + 1][row].getPosition().y + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2)), player1, (AppStateInfo*&)ASI);
											//decrement attacker
											brd->tab[i][row].units->power -= 1;
											if (brd->tab[i][row].units->power <= 0)//kill?power=<0
											{
												delete brd->tab[i][row].units;
												brd->tab[i][row].units = nullptr;
											}
										}
									}
									brd->tab[i][row].update((AppStateInfo*&)ASI);
									brd->tab[i + 1][row].update((AppStateInfo*&)ASI);
									continue;
								}

							}
						}
					}
				}
				continue;
			}
		}
		break;
	case player2:
		for (int i = FIELDCOUNT - 1; i > 0; i--)
		{
			//special for row 1, where there is no sufficient number of fields to calculate
			if (i == FIELDCOUNT - FIELDCOUNT + 1)
			{
				if (brd->tab[i][row].units)
				{
					if (brd->tab[i][row].units->owner == player2)
					{
						if (brd->tab[i - 1][row].units)
						{
							if (brd->tab[i - 1][row].units->owner == player1)
							{
								sth_done = true;
								//case left top corner
								if (row == FIELDCOUNT - FIELDCOUNT)
								{
									brd->tab[i][row].units ? (brd->tab[i][row].units->owner == player2 ? totalAttackerPower += brd->tab[i][row].units->power : false) : false;//sum attackers
									brd->tab[i][row + 1].units ? (brd->tab[i][row + 1].units->owner == player2 ? totalAttackerPower += brd->tab[i][row + 1].units->power : false) : false;
									brd->tab[i - 1][row + 1].units ? (brd->tab[i - 1][row + 1].units->owner == player2 ? totalAttackerPower += brd->tab[i - 1][row + 1].units->power : false) : false;

									brd->tab[i - 1][row].units ? (brd->tab[i - 1][row].units->owner == player1 ? totalDefenderPower += brd->tab[i - 1][row].units->power : false) : false;//sum defenders
									brd->tab[i - 1][row + 1].units ? (brd->tab[i - 1][row + 1].units->owner == player1 ? totalDefenderPower += brd->tab[i - 1][row + 1].units->power : false) : false;
									brd->tab[i][row + 1].units ? (brd->tab[i][row + 1].units->owner == player1 ? totalDefenderPower += brd->tab[i][row + 1].units->power : false) : false;
									stdprint("Battle at x: " + std::to_string(i) + " y: " + std::to_string(row) + " Attacker: " + std::to_string(totalAttackerPower) + " Defender: " + std::to_string(totalDefenderPower), (AppStateInfo*&)ASI);
									int totalValue = abs(totalAttackerPower - totalDefenderPower);
									brd->tab[i][row].units->power -= totalDefenderPower;
									if (brd->tab[i][row].units->power <= 0)//kill?power=<0
									{
										delete brd->tab[i][row].units;
										brd->tab[i][row].units = nullptr;
									}
									brd->tab[i - 1][row].units->power -= totalAttackerPower;
									if (brd->tab[i - 1][row].units->power <= 0)//kill?power=<0
									{
										delete brd->tab[i - 1][row].units;
										brd->tab[i - 1][row].units = nullptr;
										if (brd->tab[i][row].units)//if attacker not killed, defender killed, new versor unit in defender's place, attacker's power -1
										{
											//new unit
											brd->tab[i - 1][row].units = new unit("n-th-unit", sf::Vector2f(brd->tab[i - 1][row].getPosition().x + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2), brd->tab[i - 1][row].getPosition().y + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2)), player2, (AppStateInfo*&)ASI);
											//decrement attacker
											brd->tab[i][row].units->power -= 1;
											if (brd->tab[i][row].units->power <= 0)//kill?power=<0
											{
												delete brd->tab[i][row].units;
												brd->tab[i][row].units = nullptr;
											}
										}
									}
									brd->tab[i][row].update((AppStateInfo*&)ASI);
									brd->tab[i - 1][row].update((AppStateInfo*&)ASI);
									continue;
								}
								//case left bottom corner
								if (row == FIELDCOUNT - 1)
								{
									brd->tab[i][row].units ? (brd->tab[i][row].units->owner == player2 ? totalAttackerPower += brd->tab[i][row].units->power : false) : false;//sum attackers
									brd->tab[i][row - 1].units ? (brd->tab[i][row - 1].units->owner == player2 ? totalAttackerPower += brd->tab[i][row - 1].units->power : false) : false;
									brd->tab[i - 1][row - 1].units ? (brd->tab[i - 1][row - 1].units->owner == player2 ? totalAttackerPower += brd->tab[i - 1][row - 1].units->power : false) : false;

									brd->tab[i - 1][row].units ? (brd->tab[i - 1][row].units->owner == player1 ? totalDefenderPower += brd->tab[i - 1][row].units->power : false) : false;//sum defenders
									brd->tab[i - 1][row - 1].units ? (brd->tab[i - 1][row - 1].units->owner == player1 ? totalDefenderPower += brd->tab[i - 1][row - 1].units->power : false) : false;
									brd->tab[i][row - 1].units ? (brd->tab[i][row - 1].units->owner == player1 ? totalDefenderPower += brd->tab[i][row - 1].units->power : false) : false;
									stdprint("Battle at x: " + std::to_string(i) + " y: " + std::to_string(row) + " Attacker: " + std::to_string(totalAttackerPower) + " Defender: " + std::to_string(totalDefenderPower), (AppStateInfo*&)ASI);
									int totalValue = abs(totalAttackerPower - totalDefenderPower);
									brd->tab[i][row].units->power -= totalDefenderPower;
									if (brd->tab[i][row].units->power <= 0)//kill?power=<0
									{
										delete brd->tab[i][row].units;
										brd->tab[i][row].units = nullptr;
									}
									brd->tab[i - 1][row].units->power -= totalAttackerPower;
									if (brd->tab[i - 1][row].units->power <= 0)//kill?power=<0
									{
										delete brd->tab[i - 1][row].units;
										brd->tab[i - 1][row].units = nullptr;
										if (brd->tab[i][row].units)//if attacker not killed, defender killed, new versor unit in defender's place, attacker's power -1
										{
											//new unit
											brd->tab[i - 1][row].units = new unit("n-th-unit", sf::Vector2f(brd->tab[i - 1][row].getPosition().x + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2), brd->tab[i - 1][row].getPosition().y + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2)), player2, (AppStateInfo*&)ASI);
											//decrement attacker
											brd->tab[i][row].units->power -= 1;
											if (brd->tab[i][row].units->power <= 0)//kill?power=<0
											{
												delete brd->tab[i][row].units;
												brd->tab[i][row].units = nullptr;
											}
										}
									}
									brd->tab[i][row].update((AppStateInfo*&)ASI);
									brd->tab[i - 1][row].update((AppStateInfo*&)ASI);
									continue;
								}
								//case any other in last row
								else
								{
									brd->tab[i][row].units ? (brd->tab[i][row].units->owner == player2 ? totalAttackerPower += brd->tab[i][row].units->power : false) : false;//sum attackers
									brd->tab[i][row + 1].units ? (brd->tab[i][row + 1].units->owner == player2 ? totalAttackerPower += brd->tab[i][row + 1].units->power : false) : false;
									brd->tab[i - 1][row + 1].units ? (brd->tab[i - 1][row + 1].units->owner == player2 ? totalAttackerPower += brd->tab[i - 1][row + 1].units->power : false) : false;
									brd->tab[i][row - 1].units ? (brd->tab[i][row - 1].units->owner == player2 ? totalAttackerPower += brd->tab[i][row - 1].units->power : false) : false;
									brd->tab[i - 1][row - 1].units ? (brd->tab[i - 1][row - 1].units->owner == player2 ? totalAttackerPower += brd->tab[i - 1][row - 1].units->power : false) : false;


									brd->tab[i - 1][row].units ? (brd->tab[i - 1][row].units->owner == player1 ? totalDefenderPower += brd->tab[i - 1][row].units->power : false) : false;//sum defenders
									brd->tab[i - 1][row + 1].units ? (brd->tab[i - 1][row + 1].units->owner == player1 ? totalDefenderPower += brd->tab[i - 1][row + 1].units->power : false) : false;
									brd->tab[i][row + 1].units ? (brd->tab[i][row + 1].units->owner == player1 ? totalDefenderPower += brd->tab[i][row + 1].units->power : false) : false;
									brd->tab[i][row - 1].units ? (brd->tab[i][row - 1].units->owner == player1 ? totalDefenderPower += brd->tab[i][row - 1].units->power : false) : false;
									brd->tab[i - 1][row - 1].units ? (brd->tab[i - 1][row - 1].units->owner == player1 ? totalDefenderPower += brd->tab[i - 1][row - 1].units->power : false) : false;
									stdprint("Battle at x: " + std::to_string(i) + " y: " + std::to_string(row) + " Attacker: " + std::to_string(totalAttackerPower) + " Defender: " + std::to_string(totalDefenderPower), (AppStateInfo*&)ASI);
									int totalValue = abs(totalAttackerPower - totalDefenderPower);
									brd->tab[i][row].units->power -= totalDefenderPower;
									if (brd->tab[i][row].units->power <= 0)//kill?power=<0
									{
										delete brd->tab[i][row].units;
										brd->tab[i][row].units = nullptr;
									}
									brd->tab[i - 1][row].units->power -= totalAttackerPower;
									if (brd->tab[i - 1][row].units->power <= 0)//kill?power=<0
									{
										delete brd->tab[i - 1][row].units;
										brd->tab[i - 1][row].units = nullptr;
										if (brd->tab[i][row].units)//if attacker not killed, defender killed, new versor unit in defender's place, attacker's power -1
										{
											//new unit
											brd->tab[i - 1][row].units = new unit("n-th-unit", sf::Vector2f(brd->tab[i - 1][row].getPosition().x + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2), brd->tab[i - 1][row].getPosition().y + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2)), player2, (AppStateInfo*&)ASI);
											//decrement attacker
											brd->tab[i][row].units->power -= 1;
											if (brd->tab[i][row].units->power <= 0)//kill?power=<0
											{
												delete brd->tab[i][row].units;
												brd->tab[i][row].units = nullptr;
											}
										}
									}
									brd->tab[i][row].update((AppStateInfo*&)ASI);
									brd->tab[i - 1][row].update((AppStateInfo*&)ASI);
									continue;
								}
							}
						}
					}
				}
				continue;
			}
			//case any i=[0,...,7] (interior)
			else
			{
				if (brd->tab[i][row].units)
				{
					if (brd->tab[i][row].units->owner == player2)
					{
						if (brd->tab[i - 1][row].units)
						{
							if (brd->tab[i - 1][row].units->owner == player1)
							{
								sth_done = true;
								//case top
								if (row == FIELDCOUNT - FIELDCOUNT)
								{
									brd->tab[i][row].units ? (brd->tab[i][row].units->owner == player2 ? totalAttackerPower += brd->tab[i][row].units->power : false) : false;//sum attackers
									brd->tab[i][row + 1].units ? (brd->tab[i][row + 1].units->owner == player2 ? totalAttackerPower += brd->tab[i][row + 1].units->power : false) : false;
									brd->tab[i - 1][row + 1].units ? (brd->tab[i - 1][row + 1].units->owner == player2 ? totalAttackerPower += brd->tab[i - 1][row + 1].units->power : false) : false;
									brd->tab[i - 2][row].units ? (brd->tab[i - 2][row].units->owner == player2 ? totalAttackerPower += brd->tab[i - 2][row].units->power : false) : false;
									brd->tab[i - 2][row + 1].units ? (brd->tab[i - 2][row + 1].units->owner == player2 ? totalAttackerPower += brd->tab[i - 2][row + 1].units->power : false) : false;

									brd->tab[i - 1][row].units ? (brd->tab[i - 1][row].units->owner == player1 ? totalDefenderPower += brd->tab[i - 1][row].units->power : false) : false;//sum defenders
									brd->tab[i - 1][row + 1].units ? (brd->tab[i - 1][row + 1].units->owner == player1 ? totalDefenderPower += brd->tab[i - 1][row + 1].units->power : false) : false;
									brd->tab[i][row + 1].units ? (brd->tab[i][row + 1].units->owner == player1 ? totalDefenderPower += brd->tab[i][row + 1].units->power : false) : false;
									brd->tab[i - 2][row].units ? (brd->tab[i - 2][row].units->owner == player1 ? totalDefenderPower += brd->tab[i - 2][row].units->power : false) : false;//sum defenders
									brd->tab[i - 2][row + 1].units ? (brd->tab[i - 2][row + 1].units->owner == player1 ? totalDefenderPower += brd->tab[i - 2][row + 1].units->power : false) : false;
									stdprint("Battle at x: " + std::to_string(i) + " y: " + std::to_string(row) + " Attacker: " + std::to_string(totalAttackerPower) + " Defender: " + std::to_string(totalDefenderPower), (AppStateInfo*&)ASI);
									int totalValue = abs(totalAttackerPower - totalDefenderPower);
									brd->tab[i][row].units->power -= totalDefenderPower;
									if (brd->tab[i][row].units->power <= 0)//kill?power=<0
									{
										delete brd->tab[i][row].units;
										brd->tab[i][row].units = nullptr;
									}
									brd->tab[i - 1][row].units->power -= totalAttackerPower;
									if (brd->tab[i - 1][row].units->power <= 0)//kill?power=<0
									{
										delete brd->tab[i - 1][row].units;
										brd->tab[i - 1][row].units = nullptr;
										if (brd->tab[i][row].units)//if attacker not killed, defender killed, new versor unit in defender's place, attacker's power -1
										{
											//new unit
											brd->tab[i - 1][row].units = new unit("n-th-unit", sf::Vector2f(brd->tab[i - 1][row].getPosition().x + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2), brd->tab[i - 1][row].getPosition().y + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2)), player2, (AppStateInfo*&)ASI);
											//decrement attacker
											brd->tab[i][row].units->power -= 1;
											if (brd->tab[i][row].units->power <= 0)//kill?power=<0
											{
												delete brd->tab[i][row].units;
												brd->tab[i][row].units = nullptr;
											}
										}
									}
									brd->tab[i][row].update((AppStateInfo*&)ASI);
									brd->tab[i - 1][row].update((AppStateInfo*&)ASI);
									continue;
								}
								//case bottom
								if (row == FIELDCOUNT - 1)
								{
									brd->tab[i][row].units ? (brd->tab[i][row].units->owner == player2 ? totalAttackerPower += brd->tab[i][row].units->power : false) : false;//sum attackers
									brd->tab[i][row - 1].units ? (brd->tab[i][row - 1].units->owner == player2 ? totalAttackerPower += brd->tab[i][row - 1].units->power : false) : false;
									brd->tab[i - 1][row - 1].units ? (brd->tab[i - 1][row - 1].units->owner == player2 ? totalAttackerPower += brd->tab[i - 1][row - 1].units->power : false) : false;
									brd->tab[i - 2][row].units ? (brd->tab[i - 2][row].units->owner == player2 ? totalAttackerPower += brd->tab[i - 2][row].units->power : false) : false;
									brd->tab[i - 2][row - 1].units ? (brd->tab[i - 2][row - 1].units->owner == player2 ? totalAttackerPower += brd->tab[i - 2][row - 1].units->power : false) : false;

									brd->tab[i - 1][row].units ? (brd->tab[i - 1][row].units->owner == player1 ? totalDefenderPower += brd->tab[i - 1][row].units->power : false) : false;//sum defenders
									brd->tab[i - 1][row - 1].units ? (brd->tab[i - 1][row - 1].units->owner == player1 ? totalDefenderPower += brd->tab[i - 1][row - 1].units->power : false) : false;
									brd->tab[i][row - 1].units ? (brd->tab[i][row - 1].units->owner == player1 ? totalDefenderPower += brd->tab[i][row - 1].units->power : false) : false;
									brd->tab[i - 2][row].units ? (brd->tab[i - 2][row].units->owner == player1 ? totalDefenderPower += brd->tab[i - 2][row].units->power : false) : false;
									brd->tab[i - 2][row - 1].units ? (brd->tab[i - 2][row - 1].units->owner == player1 ? totalDefenderPower += brd->tab[i - 2][row - 1].units->power : false) : false;
									stdprint("Battle at x: " + std::to_string(i) + " y: " + std::to_string(row) + " Attacker: " + std::to_string(totalAttackerPower) + " Defender: " + std::to_string(totalDefenderPower), (AppStateInfo*&)ASI);
									int totalValue = abs(totalAttackerPower - totalDefenderPower);
									brd->tab[i][row].units->power -= totalDefenderPower;
									if (brd->tab[i][row].units->power <= 0)//kill?power=<0
									{
										delete brd->tab[i][row].units;
										brd->tab[i][row].units = nullptr;
									}
									brd->tab[i - 1][row].units->power -= totalAttackerPower;
									if (brd->tab[i - 1][row].units->power <= 0)//kill?power=<0
									{
										delete brd->tab[i - 1][row].units;
										brd->tab[i - 1][row].units = nullptr;
										if (brd->tab[i][row].units)//if attacker not killed, defender killed, new versor unit in defender's place, attacker's power -1
										{
											//new unit
											brd->tab[i - 1][row].units = new unit("n-th-unit", sf::Vector2f(brd->tab[i - 1][row].getPosition().x + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2), brd->tab[i - 1][row].getPosition().y + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2)), player2, (AppStateInfo*&)ASI);
											//decrement attacker
											brd->tab[i][row].units->power -= 1;
											if (brd->tab[i][row].units->power <= 0)//kill?power=<0
											{
												delete brd->tab[i][row].units;
												brd->tab[i][row].units = nullptr;
											}
										}
									}
									brd->tab[i][row].update((AppStateInfo*&)ASI);
									brd->tab[i - 1][row].update((AppStateInfo*&)ASI);
									continue;
								}
								//case any row=[0,...,7]
								else
								{
									brd->tab[i][row].units ? (brd->tab[i][row].units->owner == player2 ? totalAttackerPower += brd->tab[i][row].units->power : false) : false;//sum attackers
									brd->tab[i][row + 1].units ? (brd->tab[i][row + 1].units->owner == player2 ? totalAttackerPower += brd->tab[i][row + 1].units->power : false) : false;
									brd->tab[i - 1][row + 1].units ? (brd->tab[i - 1][row + 1].units->owner == player2 ? totalAttackerPower += brd->tab[i - 1][row + 1].units->power : false) : false;
									brd->tab[i][row - 1].units ? (brd->tab[i][row - 1].units->owner == player2 ? totalAttackerPower += brd->tab[i][row - 1].units->power : false) : false;
									brd->tab[i - 1][row - 1].units ? (brd->tab[i - 1][row - 1].units->owner == player2 ? totalAttackerPower += brd->tab[i - 1][row - 1].units->power : false) : false;
									brd->tab[i - 2][row].units ? (brd->tab[i - 2][row].units->owner == player2 ? totalAttackerPower += brd->tab[i - 2][row].units->power : false) : false;
									brd->tab[i - 2][row + 1].units ? (brd->tab[i - 2][row + 1].units->owner == player2 ? totalAttackerPower += brd->tab[i - 2][row + 1].units->power : false) : false;
									brd->tab[i - 2][row - 1].units ? (brd->tab[i - 2][row - 1].units->owner == player2 ? totalAttackerPower += brd->tab[i - 2][row - 1].units->power : false) : false;

									brd->tab[i - 1][row].units ? (brd->tab[i - 1][row].units->owner == player1 ? totalDefenderPower += brd->tab[i - 1][row].units->power : false) : false;//sum defenders
									brd->tab[i - 1][row + 1].units ? (brd->tab[i - 1][row + 1].units->owner == player1 ? totalDefenderPower += brd->tab[i - 1][row + 1].units->power : false) : false;
									brd->tab[i][row + 1].units ? (brd->tab[i][row + 1].units->owner == player1 ? totalDefenderPower += brd->tab[i][row + 1].units->power : false) : false;
									brd->tab[i][row - 1].units ? (brd->tab[i][row - 1].units->owner == player1 ? totalDefenderPower += brd->tab[i][row - 1].units->power : false) : false;
									brd->tab[i - 1][row - 1].units ? (brd->tab[i - 1][row - 1].units->owner == player1 ? totalDefenderPower += brd->tab[i - 1][row - 1].units->power : false) : false;
									brd->tab[i - 2][row].units ? (brd->tab[i - 2][row].units->owner == player1 ? totalDefenderPower += brd->tab[i - 2][row].units->power : false) : false;//sum defenders
									brd->tab[i - 2][row + 1].units ? (brd->tab[i - 2][row + 1].units->owner == player1 ? totalDefenderPower += brd->tab[i - 2][row + 1].units->power : false) : false;
									brd->tab[i - 2][row - 1].units ? (brd->tab[i - 2][row - 1].units->owner == player1 ? totalDefenderPower += brd->tab[i - 2][row - 1].units->power : false) : false;
									stdprint("Battle at x: " + std::to_string(i) + " y: " + std::to_string(row) + " Attacker: " + std::to_string(totalAttackerPower) + " Defender: " + std::to_string(totalDefenderPower), (AppStateInfo*&)ASI);
									int totalValue = abs(totalAttackerPower - totalDefenderPower);
									brd->tab[i][row].units->power -= totalDefenderPower;
									if (brd->tab[i][row].units->power <= 0)//kill?power=<0
									{
										delete brd->tab[i][row].units;
										brd->tab[i][row].units = nullptr;
									}
									brd->tab[i - 1][row].units->power -= totalAttackerPower;
									if (brd->tab[i - 1][row].units->power <= 0)//kill?power=<0
									{
										delete brd->tab[i - 1][row].units;
										brd->tab[i - 1][row].units = nullptr;
										if (brd->tab[i][row].units)//if attacker not killed, defender killed, new versor unit in defender's place, attacker's power -1
										{
											//new unit
											brd->tab[i - 1][row].units = new unit("n-th-unit", sf::Vector2f(brd->tab[i - 1][row].getPosition().x + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2), brd->tab[i - 1][row].getPosition().y + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2)), player2, (AppStateInfo*&)ASI);
											//decrement attacker
											brd->tab[i][row].units->power -= 1;
											if (brd->tab[i][row].units->power <= 0)//kill?power=<0
											{
												delete brd->tab[i][row].units;
												brd->tab[i][row].units = nullptr;
											}
										}
									}
									brd->tab[i][row].update((AppStateInfo*&)ASI);
									brd->tab[i - 1][row].update((AppStateInfo*&)ASI);
									continue;
								}
							}
						}
					}
				}
				continue;
			}
		}
		break;
	default:
		break;
	}
	sth_done ? ((AppStateInfo*)ASI)->moves_made++ : false;
}

void clickable::push_units(void*&ASI)
{
	bool sth_done = false;
	int row = ((int*)(((AppStateInfo*)ASI)->other))[row_index];
	board* brd = ((board*)((AppStateInfo*)ASI)->obj);
	unit*unit_ptr = nullptr;
	switch (((AppStateInfo*)ASI)->turn)
	{
	case player1:
		for (int i = FIELDCOUNT - 1; i >= 0; i--)
		{
			if (i == FIELDCOUNT - 1)
			{
				if (brd->tab[i][row].units)
				{
					if (brd->tab[i][row].units->owner == player1)
					{
						stdprint("Player 1 won", (AppStateInfo*&)ASI);
						playerwon((void*&)ASI);
						return;
					}
				}
			}
			else if (true)
			{
				if (brd->tab[i][row].units ? (brd->tab[i][row].units->owner == player1 ? true : false) : false)
				{
					if (brd->tab[i + 1][row].units == nullptr)
					{
						unit_ptr = brd->tab[i][row].units;
						brd->tab[i][row].units = nullptr;
						brd->tab[i + 1][row].units = unit_ptr;
						brd->tab[i][row].update((AppStateInfo*&)ASI);
						brd->tab[i + 1][row].update((AppStateInfo*&)ASI);
						i++;
						sth_done = true;
					}
				}
			}
		}
		break;
	case player2:
		for (int i = FIELDCOUNT - FIELDCOUNT; i < FIELDCOUNT; i++)
		{
			if (i == FIELDCOUNT - FIELDCOUNT)
			{
				if (brd->tab[i][row].units)
				{
					if (brd->tab[i][row].units->owner == player2)
					{
						stdprint("Player 2 won", (AppStateInfo*&)ASI);//TODO game won
						playerwon((void*&)ASI);
						return;
					}
				}
			}
			else if (true)
			{
				if (brd->tab[i][row].units ? (brd->tab[i][row].units->owner == player2 ? true : false) : false)
				{
					if (brd->tab[i - 1][row].units == nullptr)
					{
						unit_ptr = brd->tab[i][row].units;
						brd->tab[i][row].units = nullptr;
						brd->tab[i - 1][row].units = unit_ptr;
						brd->tab[i][row].update((AppStateInfo*&)ASI);
						brd->tab[i - 1][row].update((AppStateInfo*&)ASI);
						i--;
						sth_done = true;
					}
				}
			}
		}
		break;
	default:
		break;
	}
	sth_done ? ((AppStateInfo*)ASI)->moves_made++ : false;
	return;
}

void clickable::push_unit(void*&ASI)
{
	bool sth_done = false;
	int row = ((int*)(((AppStateInfo*)ASI)->other))[board_row_index];
	int column = ((int*)(((AppStateInfo*)ASI)->other))[board_column_index];
	board* brd = ((board*)((AppStateInfo*)ASI)->obj);
	unit*unit_ptr = nullptr;
	switch (((AppStateInfo*)ASI)->turn)
	{
	case player1:
		for (int i = column; i == column; i--)
		{
			if (i == FIELDCOUNT - 1)
			{
				if (brd->tab[i][row].units)
				{
					if (brd->tab[i][row].units->owner == player1)
					{
						stdprint("Player 1 won", (AppStateInfo*&)ASI);//TODO game won
					}
				}
			}
			else if (true)
			{
				if (brd->tab[i][row].units ? (brd->tab[i][row].units->owner == player1 ? true : false) : false)
				{
					if (brd->tab[i + 1][row].units == nullptr)
					{
						unit_ptr = brd->tab[i][row].units;
						brd->tab[i][row].units = nullptr;
						brd->tab[i + 1][row].units = unit_ptr;
						brd->tab[i][row].update((AppStateInfo*&)ASI);
						brd->tab[i + 1][row].update((AppStateInfo*&)ASI);
						i++;
						sth_done = true;
					}
				}
			}
		}
		break;
	case player2:
		for (int i = column; i == column; i++)
		{
			if (i == FIELDCOUNT - FIELDCOUNT)
			{
				if (brd->tab[i][row].units)
				{
					if (brd->tab[i][row].units->owner == player2)
					{
						stdprint("Player 2 won", (AppStateInfo*&)ASI);//TODO game won
					}
				}
			}
			else if (true)
			{
				if (brd->tab[i][row].units ? (brd->tab[i][row].units->owner == player2 ? true : false) : false)
				{
					if (brd->tab[i - 1][row].units == nullptr)
					{
						unit_ptr = brd->tab[i][row].units;
						brd->tab[i][row].units = nullptr;
						brd->tab[i - 1][row].units = unit_ptr;
						brd->tab[i][row].update((AppStateInfo*&)ASI);
						brd->tab[i - 1][row].update((AppStateInfo*&)ASI);
						i--;
						sth_done = true;
					}
				}
			}
		}
		break;
	default:
		break;
	}
	//sth_done ? ((AppStateInfo*)ASI)->moves_made++ : false; NEVER TRUE, because push_unit is used internally by merge_units so is never action that should be counted as a move
	return;
}

void clickable::merge_units(void*& ASI)
{
	int row = ((int*)(((AppStateInfo*)ASI)->other))[row_index];
	int column = ((int*)(((AppStateInfo*)ASI)->other))[column_index];
	board* brd = ((board*)((AppStateInfo*)ASI)->obj);
	unit*unit_ptr = nullptr;
	bool sth_done = false;//for ASI	
	bool did_sth = false;//for algrithm
	switch (((AppStateInfo*)ASI)->turn)
	{
	case player1:
		for (int i = FIELDCOUNT - 2; i >= 1; i--)
		{
			if (i == FIELDCOUNT - 1)
			{
				if (brd->tab[i][row].units)
				{
					stdprint("merge at the verge Right", (AppStateInfo*&)ASI);
				}
			}
			if (brd->tab[i][row].units ? (brd->tab[i][row].units->owner == player1 ? true : false) : false)
			{
				if (brd->tab[i - 1][row].units)
				{
					if ((brd->tab[i][row].units->owner == brd->tab[i - 1][row].units->owner))
					{
						brd->tab[i][row].units->merge_unit_B_into_A(brd->tab[i][row].units, brd->tab[i - 1][row].units);
						delete brd->tab[i - 1][row].units;
						brd->tab[i - 1][row].units = nullptr;
						brd->tab[i][row].update((AppStateInfo*&)ASI);
						brd->tab[i - 1][row].update((AppStateInfo*&)ASI);
						//i--;
						did_sth = true;
						sth_done = true;
						//continue;
					}
				}
			}
			if ((brd->tab[i - 1][row].units) && did_sth == true)
			{
				if (brd->tab[i - 1][row].units->owner == player1)
				{
					AppStateInfo internalASI = (AppStateInfo*)ASI;
					AppStateInfo *internalASIptr = &internalASI;
					internalASI.other = malloc(4 * sizeof(int));
					((int*)(internalASI.other))[board_row_index] = row;
					((int*)(internalASI.other))[board_column_index] = i - 1;
					push_unit((void*&)internalASIptr);
					sth_done = true;
				}

			}
		}
		break;
	case player2:
		for (int i = FIELDCOUNT - FIELDCOUNT + 1; i <= FIELDCOUNT - 2; i++)
		{
			if (i == FIELDCOUNT - FIELDCOUNT)
			{
				if (brd->tab[i][row].units)
				{
					stdprint("merge at the verge Left", (AppStateInfo*&)ASI);
				}
			}
			if (brd->tab[i][row].units ? (brd->tab[i][row].units->owner == player2 ? true : false) : false)
			{
				if (brd->tab[i + 1][row].units)
				{
					if ((brd->tab[i][row].units->owner == brd->tab[i + 1][row].units->owner))
					{
						brd->tab[i][row].units->merge_unit_B_into_A(brd->tab[i][row].units, brd->tab[i + 1][row].units);
						delete brd->tab[i + 1][row].units;
						brd->tab[i + 1][row].units = nullptr;
						brd->tab[i][row].update((AppStateInfo*&)ASI);
						brd->tab[i + 1][row].update((AppStateInfo*&)ASI);
						//i--;
						did_sth = true;
						sth_done = true;
						//continue;
					}
				}
			}
			if ((brd->tab[i + 1][row].units) && did_sth == true)
			{
				if (brd->tab[i + 1][row].units->owner == player2)
				{
					AppStateInfo internalASI = (AppStateInfo*)ASI;
					AppStateInfo *internalASIptr = &internalASI;
					internalASI.other = malloc(4 * sizeof(int));
					((int*)(internalASI.other))[board_row_index] = row;
					((int*)(internalASI.other))[board_column_index] = i + 1;
					push_unit((void*&)internalASIptr);
					sth_done = true;
				}

			}
		}
		break;
	default:
		break;
	}
	sth_done ? ((AppStateInfo*)ASI)->moves_made++ : false;
	return;
}

void clickable::split_units_down(void*& ASI)
{
	bool sth_done = false;
	int row = ((int*)(((AppStateInfo*)ASI)->other))[row_index];
	int column = ((int*)(((AppStateInfo*)ASI)->other))[column_index];
	board* brd = ((board*)((AppStateInfo*)ASI)->obj);
	unit*unit_ptr = nullptr;
	bool did_sth = false;
	switch (((AppStateInfo*)ASI)->turn)
	{
	case player1:
		for (int i = FIELDCOUNT - 1; i >= 0; i--)
		{
			if (row != FIELDCOUNT - 1)
			{
				if (brd->tab[i][row].units)
				{
					if (brd->tab[i][row].units->owner == player1)
					{
						if (brd->tab[i][row + 1].units == nullptr)
						{
							if (brd->tab[i][row].units->power > 1)
							{
								brd->tab[i][row].units->power--;
								brd->tab[i][row + 1].units = new unit("n-th-unit", sf::Vector2f(brd->tab[FIELDCOUNT - FIELDCOUNT][row + 1].getPosition().x + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2), brd->tab[FIELDCOUNT - FIELDCOUNT][row + 1].getPosition().y + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2)), player1, (AppStateInfo*&)ASI);
								brd->tab[i][row].update((AppStateInfo*&)ASI);
								brd->tab[i][row + 1].update((AppStateInfo*&)ASI);
								sth_done = true;
							}
						}
						break;
					}
				}
			}
		}
		break;
	case player2:
		for (int i = 0; i < FIELDCOUNT; i++)
		{
			if (row != FIELDCOUNT - 1)
			{
				if (brd->tab[i][row].units)
				{
					if (brd->tab[i][row].units->owner == player2)
					{
						if (brd->tab[i][row + 1].units == nullptr)
						{
							if (brd->tab[i][row].units->power > 1)
							{
								brd->tab[i][row].units->power--;
								brd->tab[i][row + 1].units = new unit("n-th-unit", sf::Vector2f(brd->tab[FIELDCOUNT - FIELDCOUNT][row + 1].getPosition().x + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2), brd->tab[FIELDCOUNT - FIELDCOUNT][row + 1].getPosition().y + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2)), player2, (AppStateInfo*&)ASI);
								brd->tab[i][row].update((AppStateInfo*&)ASI);
								brd->tab[i][row + 1].update((AppStateInfo*&)ASI);
								sth_done = true;
							}
						}
						break;
					}
				}
			}
		}
		break;
	default:
		break;
	}
	sth_done ? ((AppStateInfo*)ASI)->moves_made++ : false;
	return;
}

void clickable::split_units_up(void*& ASI)
{
	bool sth_done = false;//for ASI
	int row = ((int*)(((AppStateInfo*)ASI)->other))[row_index];
	int column = ((int*)(((AppStateInfo*)ASI)->other))[column_index];
	board* brd = ((board*)((AppStateInfo*)ASI)->obj);
	unit*unit_ptr = nullptr;
	bool did_sth = false;//FOR algorithm
	switch (((AppStateInfo*)ASI)->turn)
	{
	case player1:
		for (int i = FIELDCOUNT - 1; i >= 0; i--)
		{
			if (row != FIELDCOUNT - FIELDCOUNT)
			{
				if (brd->tab[i][row].units)
				{
					if (brd->tab[i][row].units->owner == player1)
					{
						if (brd->tab[i][row - 1].units == nullptr)
						{
							if (brd->tab[i][row].units->power > 1)
							{
								brd->tab[i][row].units->power--;
								brd->tab[i][row - 1].units = new unit("n-th-unit", sf::Vector2f(brd->tab[FIELDCOUNT - FIELDCOUNT][row - 1].getPosition().x + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2), brd->tab[FIELDCOUNT - FIELDCOUNT][row - 1].getPosition().y + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2)), player1, (AppStateInfo*&)ASI);
								brd->tab[i][row].update((AppStateInfo*&)ASI);
								brd->tab[i][row - 1].update((AppStateInfo*&)ASI);
								sth_done = true;
							}
						}
						break;
					}
				}
			}
		}
		break;
	case player2:
		for (int i = 0; i < FIELDCOUNT; i++)
		{
			if (row != FIELDCOUNT - FIELDCOUNT)
			{
				if (brd->tab[i][row].units)
				{
					if (brd->tab[i][row].units->owner == player2)
					{
						if (brd->tab[i][row - 1].units == nullptr)
						{
							if (brd->tab[i][row].units->power > 1)
							{
								brd->tab[i][row].units->power--;
								brd->tab[i][row - 1].units = new unit("n-th-unit", sf::Vector2f(brd->tab[FIELDCOUNT - FIELDCOUNT][row - 1].getPosition().x + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2), brd->tab[FIELDCOUNT - FIELDCOUNT][row - 1].getPosition().y + ((FIELD_SIZE_DEF - UNIT_SIZE_DEF) / 2)), player2, (AppStateInfo*&)ASI);
								brd->tab[i][row].update((AppStateInfo*&)ASI);
								brd->tab[i][row - 1].update((AppStateInfo*&)ASI);
								sth_done = true;
							}
						}
						break;
					}
				}
			}
		}
		break;
	default:
		break;
	}
	sth_done ? ((AppStateInfo*)ASI)->moves_made++ : false;
	return;
}

void clickable::result_update(void*&ASI)
{
	if (!(((AppStateInfo*&)(ASI))->resultBtn))
	{
		return;
	}
	(((AppStateInfo*&)(ASI))->resultBtn->obj)->sfstr = sf::String(RESULT_TITLE + std::to_string(((AppStateInfo*&)(ASI))->scoreP1) + ":" + std::to_string(((AppStateInfo*&)(ASI))->scoreP2));
	(((AppStateInfo*&)(ASI))->resultBtn->obj)->sftext.setString(((button*)(((AppStateInfo*&)(ASI))->resultBtn->obj))->sfstr);
}

void clickable::playerwon(void *&ASI)
{
	int who = ((AppStateInfo*&)ASI)->turn;
	switch (who)
	{
	case player1:
		((AppStateInfo*&)ASI)->scoreP1++;
		result_update(ASI);
		break;
	case player2:
		((AppStateInfo*&)ASI)->scoreP2++;
		result_update(ASI);
		break;
	default:
		break;
	}
	if (((AppStateInfo*&)ASI)->ini.result_instant_reset == (int)true)
	{
		newgame(ASI);
	}
	return;
}

#pragma endregion
