#include "Jumping.h"
#include "Animation.h"

// Actually for Running

Jumping::Jumping()
{
	sheetRect[0].x = 0;
	sheetRect[0].y = 95;
	sheetRect[0].w = 48;
	sheetRect[0].h = 77;

	sheetRect[1].x = 48;
	sheetRect[1].y = 95;
	sheetRect[1].w = 48;
	sheetRect[1].h = 77;

	sheetRect[2].x = 96;
	sheetRect[2].y = 95;
	sheetRect[2].w = 48;
	sheetRect[2].h = 77;

	sheetRect[3].x = 144;
	sheetRect[3].y = 95;
	sheetRect[3].w = 48;
	sheetRect[3].h = 77;

	sheetRect[4].x = 192;
	sheetRect[4].y = 95;
	sheetRect[4].w = 48;
	sheetRect[4].h = 80;

	sheetRect[5].x = 240;
	sheetRect[5].y = 95;
	sheetRect[5].w = 48;
	sheetRect[5].h = 77;


	frameTotal = 6;
};
Jumping::~Jumping()
{

};

void Jumping::idle(Animation* a)
{
	std::cout << "Going from Running to Idling" << std::endl;
	a->setCurrent(new Idle());
	delete this;
}

void Jumping::Animate()
{

	/*currentRect = &sheetRect[frame / 10];
	frame++;
	std::cout << frame << std::endl;
	if (frame / 10 >= WALKING_ANIMATION_FRAMES)
	{
		frame = 0;
	}*/
}

