#include "Climbing.h"
#include "Animation.h"

Climbing::Climbing()
{
	sheetRect[0].x = 0;
	sheetRect[0].y = 258;
	sheetRect[0].w = 48;
	sheetRect[0].h = 77;

	sheetRect[1].x = 48;
	sheetRect[1].y = 258;
	sheetRect[1].w = 48;
	sheetRect[1].h = 77;

	sheetRect[2].x = 96;
	sheetRect[2].y = 258;
	sheetRect[2].w = 48;
	sheetRect[2].h = 77;

	sheetRect[3].x = 144;
	sheetRect[3].y = 258;
	sheetRect[3].w = 48;
	sheetRect[3].h = 77;

	sheetRect[4].x = 192;
	sheetRect[4].y = 258;
	sheetRect[4].w = 48;
	sheetRect[4].h = 80;

	sheetRect[5].x = 240;
	sheetRect[5].y = 258;
	sheetRect[5].w = 48;
	sheetRect[5].h = 77;

	frameTotal = 6;
}
Climbing::~Climbing()
{

}

void Climbing::idle(Animation* a)
{
	std::cout << "Going from Climbing to Idling" << std::endl;
	a->setCurrent(new Idle());
	delete this;	
}