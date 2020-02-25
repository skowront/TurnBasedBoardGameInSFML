#include "stdafx.h"


Game::Game()
{
}

Game::~Game()
{
}

bool Game::Play()
{
	sf::RenderWindow window(sf::VideoMode(WINDOWSIZEX, WINDOWSIZEY), asi.ini.window_title, sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(144);
	LoadConfig();
	CreateInterface();
	//refresh loop
	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
				
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (MBreleased == false) { break; }
				UpdateMousePos(window);
				asi.obj ? (stdprint(hit_obj->getName() + " hit", asi_ptr)), true : false;
				try { HandleHit(); }
				catch (int ex) { if (ex == EXQUIT) { return false; } }
				break;

			case sf::Event::MouseButtonReleased:
				MBreleased = true;
			default:
				break;
			}
		}
		DrawWindow(window);
	}
	Cleanup();
	return false;
}

void Game::LoadConfig()
{
	try { asi.load_ini(CONFIG_PATH, asi_ptr); }
	catch (int ex) { if (ex == EXQUIT) { throw EXQUIT; } }
}

void Game::CreateInterface()
{
	asi.make_background(asi.world_root, asi_ptr);
	asi.make_menu(asi.world_root, asi_ptr);
}

void Game::UpdateMousePos(sf::RenderWindow&window)
{
	 MBreleased = false;
	mousePixelPos = sf::Mouse::getPosition(window);
	mouseWorldPos = window.mapPixelToCoords(mousePixelPos);
	asi.mouse_pos = mouseWorldPos;
	asi.mouse_pixel_pos = mousePixelPos;
	asi.clicked(asi.world_root, mousePixelPos, hit_obj, temp = false);

	asi.obj = hit_obj;
}

void Game::HandleHit()
{
	try
	{
		asi.obj ? hit_obj->clicked((void*&)asi_ptr), true : false;
		//check if moves made, and if turn switch needed, then deal if needed
		asi.moves_made >= asi.ini.moves_per_turn&&asi.turnbtn_container_ptr != nullptr ?
			asi.turnbtn_container_ptr->obj->turnbtn_clicked((void*&)asi_ptr), asi.moves_made = 0, true : false;
		asi.turnbtn_container_ptr->obj->turnbtn_update((void*&)asi_ptr);
	}
	catch (int except)
	{
		if (except == EXQUIT) { asi.world_root->StructuralRemove(asi.world_root, (void*&)asi_ptr); throw EXQUIT; }//cleanup and return
		else { stdprint("unknown exception", asi_ptr); }
	}
}

void Game::DrawWindow(sf::RenderWindow & window)
{
	asi.world_root->StructuralDraw(asi.world_root, window, rs);
	window.display();
}

void Game::Cleanup()
{
	asi.world_root->StructuralRemove(asi.world_root, (void*&)asi_ptr);
	asi.world_root = nullptr;
}

