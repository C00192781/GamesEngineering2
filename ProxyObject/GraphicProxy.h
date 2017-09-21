#pragma once
#ifndef GRAPHIC_PROXY_H
#define GRAPHIC_PROXY_H
#include "Graphic.h"
#include "iGraphic.h"

// Proxy (Definition)
class GraphicProxy : public IGraphic
{
public:
	GraphicProxy();
	~GraphicProxy();
	void Draw();
private:
	Graphic* graphic;
	Graphic* getInstance(void);
};
#endif 
