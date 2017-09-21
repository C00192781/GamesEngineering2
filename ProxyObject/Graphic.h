#pragma once
// Real Subject (Definition) 
#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "IGraphic.h"

class Graphic : public IGraphic
{
public:
	Graphic();
	~Graphic();
	void Draw();
};
#endif 