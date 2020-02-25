
#pragma once
#include "Clickable.h"
#include "Object.h"
#include "ASI.h"

class AppStateInfo;

class clickableObject :public clickable, public object
{
public:
	clickableObject();
	~clickableObject();

	void clicked(void*& ASI);


};





