#pragma once
class Game : private clickableObject, private AppStateInfo
{

public:
	Game();
	~Game();
	bool Play();

private:
	sf::RenderStates rs;
	sf::Vector2i mousePixelPos; sf::Vector2f mouseWorldPos;
	bool temp = false;
	clickableObject*hit_obj = nullptr;
	AppStateInfo asi;
	AppStateInfo* asi_ptr = &asi;
	bool MBreleased = true;
	
	void LoadConfig();
	void CreateInterface();
	void UpdateMousePos(sf::RenderWindow&);
	void HandleHit();
	void DrawWindow(sf::RenderWindow& window);
	void Cleanup();
};

