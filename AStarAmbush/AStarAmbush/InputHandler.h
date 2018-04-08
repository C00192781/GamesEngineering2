#pragma once
#pragma once

#include <SDL.h>
#include <iostream>
#include "EventListener.h"

class InputHandler
{
public:
	InputHandler(EventListener *e, SDL_Event * event);
	void HandleInput();
private:
	EventListener *m_eventListener;
	SDL_Event * m_event;
};