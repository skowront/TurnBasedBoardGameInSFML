#include "stdafx.h"

clickableObject::clickableObject()
{

}

clickableObject::~clickableObject()
{
}

void clickableObject::clicked(void*& ASI)
{
	if (!this->function)
	{
		return;
	}
	(this->*function)(ASI);
}