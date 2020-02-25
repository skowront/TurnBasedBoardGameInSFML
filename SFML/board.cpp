#pragma once

#include "stdafx.h"




//BOARD 
//all "magic" constants are adjusted for default window size to fit the positioning. To be precise they are margins and offset.
void board::board_core()
{
	name = "BRD";
	SetClicked(Eemptyfxno);
	shape.setPosition(sf::Vector2f(0, 0));
	shape.setFillColor(sf::Color::Transparent);
	shape.setSize(sf::Vector2f((float)sizex, (float)sizey));
	const int brd_btnsize=25;
	const int marginL=5;
	const int marginR=645;
	tab = new field*[yD];
	for (int i = 0; i < yD; ++i)
		tab[i] = new field[xD];
	for (int i = 0; i < yD; i++)
	{
		for (int j = 0; j < xD; j++)
		{
			tab[i][j].setSize(sf::Vector2f(FIELD_SIZE_DEF, FIELD_SIZE_DEF));
			tab[i][j].setPosition(sf::Vector2f(BRD_OFFSET + (5 + tab[i][j].getSize().x)*i, 5 + (5 + tab[i][j].getSize().y)*j));
			tab[i][j].setColor(sf::Color::White);
		}
	}
	player1btns = new button*[btncount];
	for (int i = 0; i < btncount; ++i)
		player1btns[i] = new button[xD];
	for (int i = 0; i < btncount; i++)
	{
		for (int j = 0; j < xD; j++)
		{
			player1btns[i][j].setSize(sf::Vector2f(brd_btnsize, brd_btnsize));
			player1btns[i][j].setPosition(sf::Vector2f((float)(marginL + (player1btns[i][j].getSize().x + 5)*i),(float)(5 + 7.5 + (5 + player1btns[i][j].getSize().y + (tab[i][j].getSize().y - player1btns[i][j].getSize().y))*j)));
			player1btns[i][j].setColor(sf::Color::White);
		}
	}
	player2btns = new button*[btncount];
	for (int i = 0; i < btncount; ++i)
		player2btns[i] = new button[xD];
	for (int i = 0; i < btncount; i++)
	{
		for (int j = 0; j < xD; j++)
		{
			player2btns[i][j].setSize(sf::Vector2f(brd_btnsize, brd_btnsize));
			player2btns[i][j].setPosition(sf::Vector2f((float)(marginR + (player2btns[i][j].getSize().x + 5)*i),(float)(5 + 7.5 + (5 + player2btns[i][j].getSize().y + (tab[i][j].getSize().y - player2btns[i][j].getSize().y))*j)));
			player2btns[i][j].setColor(sf::Color::White);
		}
	}
}

board::board()
{
	board_core();
}

board::board(std::string nam)
{
	name+= nam;
	board_core();
}

board::board(std::string nam, container *&theworld)
{
	board_core();
	name+= nam;
	world = theworld;
}

board::board(std::string nam, container *&theworld, int fx)
{
	board_core();
	name += nam;
	world = theworld;
	this->SetClicked(fx);
}

//all "magic" constants are adjusted for default window size to fit the positioning. To be precise they are margins and offset.
board::board(std::string nam, container*& theworld, int fx, int*fxtab,texture_data **&textures, texture_data*fields_bg,texture_data*units_blue,texture_data*units_red)
{
	board_core();
	for (int i = 0; i < yD; i++)
	{
		for (int j = 0; j < xD; j++)
		{
			tab[i][j].setSize(sf::Vector2f(FIELD_SIZE_DEF, FIELD_SIZE_DEF));
			tab[i][j].setPosition(sf::Vector2f(BRD_OFFSET + (5 + tab[i][j].getSize().x)*i, 5 + (5 + tab[i][j].getSize().y)*j));
			tab[i][j].setColor(sf::Color::White);
			if (&((fields_bg)->obj_texture))
			{
				this->tab[j][i].shape.setTexture(&((fields_bg)->obj_texture));
			}
		}
	}
	name += nam;
	world = theworld;
	this->SetClicked(fx);
	int iterator=0;
	for (int i =0; i < xD; i++)
	{
		iterator = BTNTYPESCOUNT - 1;
		for (int j = 0; j <BTNTYPESCOUNT; j++)
		{
			
			//this->player1btns[j][i].setColor(sf::Color(10+(10*iterator),0,0));
			this->player1btns[j][i].SetClicked(fxtab[iterator]);
			if (&((textures[iterator])->obj_texture))
			{
				this->player1btns[j][i].shape.setTexture(&((textures[iterator])->obj_texture));
			}
			iterator--;
		}
		
	}
	for (int i = 0; i < xD; i++)
	{
		iterator = 0;
		for (int j = 0; j <BTNTYPESCOUNT; j++)
		{
			
			//this->player2btns[j][i].setColor(sf::Color(10 + (10 * iterator), 0, 0));
			this->player2btns[j][i].SetClicked(fxtab[iterator]);
			if (&(textures[iterator])->obj_texture)
			{
				this->player2btns[j][i].shape.setTexture(&(textures[iterator])->obj_texture);
			}
			iterator++;
		}
		
	}

}


board::~board()
{
	for (int i = 0; i < yD; ++i)
	{
		if (tab[i])
		{
			delete[] tab[i];
		}
		else
		{
			return;
		}
	}
	delete[] tab;
	tab = nullptr;
	for (int i = 0; i < btncount; ++i)
	{
		if (player1btns[i])
		{
			delete[] player1btns[i];
		}
		else
		{
			return;
		}
	}
	delete[] player1btns;
	player1btns = nullptr;
	for (int i = 0; i < btncount; ++i)
	{
		if (player2btns[i])
		{
			delete[] player2btns[i];
		}
		else
		{
			return;
		}
	}
	delete[] player2btns;
	player2btns = nullptr;
}

void board::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	target.draw(shape, state);
	for (int i = 0; i < yD; i++)
	{
		for (int j = 0; j < xD; j++)
		{
			tab[i][j].draw(target,state);
		}
	}
	for (int i = 0; i < btncount; i++)
	{
		for (int j = 0; j < xD; j++)
		{
			player1btns[i][j].draw(target, state);
		}
	}
	for (int i = 0; i < btncount; i++)
	{
		for (int j = 0; j < xD; j++)
		{
			player2btns[i][j].draw(target, state);
		}
	}
}

void board::board_clicked(sf::Vector2f mouse_vec)
{

}

void board::info()
{

}

sf::FloatRect board::getGlobalBounds() const
{
	return shape.getGlobalBounds();
}

std::string board::getName()
{
	return name;
}

void board::setPosition(sf::Vector2f position)
{
	shape.setPosition(position);
	for (int i = 0; i < yD; i++)
	{
		for (int j = 0; j < xD; j++)
		{
			tab[i][j].setPosition(sf::Vector2f(tab[i][j].getPosition().x+position.x,tab[i][j].getPosition().y+position.y));
		}
	}
	for (int i = 0; i < btncount; i++)
	{
		for (int j = 0; j < xD; j++)
		{
			player1btns[i][j].setPosition(sf::Vector2f(player1btns[i][j].getPosition().x + position.x, player1btns[i][j].getPosition().y + position.y));
		}
	}
	for (int i = 0; i < btncount; i++)
	{
		for (int j = 0; j < xD; j++)
		{
			player2btns[i][j].setPosition(sf::Vector2f(player2btns[i][j].getPosition().x + position.x, player2btns[i][j].getPosition().y + position.y));
		}
	}
}
