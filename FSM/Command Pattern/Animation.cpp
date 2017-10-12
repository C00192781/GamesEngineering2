#include "Animation.h"
#include "Idle.h"
#include "Jumping.h"
#include "Climbing.h"


Animation::Animation()
{
	current = new Idle();
}

void Animation::idle()
{
	current->idle(this);
}

void Animation::jumping()
{
	current->jumping(this);
}

void Animation::climbing()
{
	current->climbing(this);
}

void Animation::animateCurrent()
{
	current->Animate();
	
}

SDL_Rect* Animation::getRect()
{
	return current->sheetRect;
}
//SDL_Rect* Animation::getCurrentRect()
//{
//	return current->currentRect;
//}

int Animation::getFrame()
{
	return current->frame;
}

int Animation::getFrameTotal()
{
	return current->frameTotal;
}


