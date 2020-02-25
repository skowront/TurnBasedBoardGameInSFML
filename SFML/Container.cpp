#pragma once
#include "stdafx.h"

container::container()
{

}

container::container(clickableObject* ob, container* pnex, container*plis)
{
	obj = ob;
	pnext = pnex;
	plist = plis;
}


container::~container()
{
	if (obj)
	{
		delete obj;
		obj = nullptr;
	}
}

void container::DrawPNext(container *&root, sf::RenderWindow &window, sf::RenderStates &rs)
{
	container* ptr = root;
	if (!ptr)
	{
		return;
	}
	else
	{
		if (ptr->obj)
		{
			ptr->obj->draw(window, rs);
		}
		if (ptr->pnext)
		{
			DrawPNext(ptr->pnext, window, rs);
		}
	}
	return;
}

void container::StructuralDraw(container *&root, sf::RenderWindow &window, sf::RenderStates &rs)
{
	container*ptr = root;
	if (!ptr)
	{
		return;
	}
	else
	{
		while (ptr)
		{
			DrawPNext(ptr, window, rs);
			if (ptr->plist)
			{
				ptr = ptr->plist;
			}
			else
			{
				break;
			}
		}
	}
}


//USE
container* container::getContainer(container*root, int indexL, int indexN)
{
	container* ptr = root;
	for (int i = 0; i < indexL; i++)
	{
		if (!ptr)
		{
			return false;
		}
		else
		{
			if (ptr->plist)
			{
				ptr = ptr->plist;
			}
		}
	}
	for (int i = 0; i < indexN; i++)
	{
		if (!ptr)
		{
			return false;
		}
		else
		{
			if (ptr->pnext)
			{
				ptr = ptr->pnext;
			}
		}
	}
	return ptr;
}



int container::getLenght(container*root)
{
	int len = 0;
	auto ptr = root;
	if (!ptr)
	{
		return len;
	}
	else
	{
		while (ptr->plist)
		{
			ptr = ptr->plist;
			len++;
		}
	}
	return len;
}

int container::getWidthAt(container*root, int depth)
{
	int wid = 1;
	auto ptr = root;
	if (!ptr)
	{
		return 0;
	}
	else
	{
		ptr = getContainer(root, depth, 0);
		if (!ptr)
		{
			return 0;
		}
		else
		{
			while (ptr->pnext)
			{
				ptr = ptr->pnext;
				wid++;
			}
		}
	}
	return wid;
}



bool container::add_container_behind(container* &root, int indexL, int indexN, const int direction, container* cont)
{
	container* ptr = root;
	if (!ptr)
	{
		if (indexL == 0 && indexN == 0)
		{
			root = cont;
			return true;
		}
		return false;
	}
	getContainer(root, indexL, indexN);
	container*currentptr = root;
	container*temp_existing = nullptr;
	container*new_end = nullptr;
	switch (direction)
	{
	case down:
		currentptr = getContainer(root, indexL, indexN);
		if (!currentptr)
		{
			return false;
		}
		if (currentptr->plist)
		{
			temp_existing = currentptr->plist;
			new_end = cont->plist;
			while (new_end->plist)
			{
				new_end = new_end->plist;
			}
			new_end->plist = temp_existing;
			currentptr->plist = cont;
			return true;
			break;
		}
		else
		{
			currentptr->plist = cont;
			return true;
		}
		break;
	case right:
		currentptr = getContainer(root, indexL, indexN);
		if (!currentptr)
		{
			return false;
		}
		if (currentptr->pnext)
		{
			temp_existing = currentptr->pnext;
			new_end = cont->pnext;
			while (new_end->pnext)
			{
				new_end = new_end->pnext;
			}
			new_end->pnext = temp_existing;
			currentptr->pnext = cont;
			return true;
			break;
		}
		else
		{
			currentptr->pnext = cont;
			return true;
		}
		break;
	default:
		return false;
		break;

	}
}


//DELETION
void container::StructuralRemove(container*&root, void*&ASI)
{
	auto ptr = root;
	if (!ptr)
	{
		return;
	}
	else
	{
		if (ptr->pnext)
		{
			StructuralRemove(ptr->pnext, ASI);
		}
		if (ptr->plist)
		{
			StructuralRemove(ptr->plist, ASI);
		}
		if (ptr->obj)
		{
			stdprint("deleting " + ptr->obj->getName(), (AppStateInfo*&)ASI);
		}
		else
		{
			stdprint("deleting ", (AppStateInfo*&)ASI);
		}
		delete ptr;

		return;
	}
}
