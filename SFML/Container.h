#pragma once

class object;
class clickableObject;

class container
{
public:
	container();
	container(clickableObject* ob, container* pnex, container*plis);
	~container();
	clickableObject *obj = nullptr;
	container *pnext = nullptr;
	container *plist = nullptr;

	//CONSTRUCTION
	void DrawPNext(container*&,sf::RenderWindow &window, sf::RenderStates &rs);
	void StructuralDraw(container*&,sf::RenderWindow &window, sf::RenderStates &rs);


	//USE
	container *getContainer(container*root, int indexL, int indexN);
	int getLenght(container*root);
	int getWidthAt(container*root, int depth);
	bool add_container_behind(container* &root, int indexL, int indexN, const int direction, container* cont);

	//DELETION
	void StructuralRemove(container*&root, void*&);
};
