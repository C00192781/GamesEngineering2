#include "InputHandler.h"

InputHandler::InputHandler(EventListener * e, SDL_Event * event)
{
	m_eventListener = e; 
	m_event = event;
}

void InputHandler::HandleInput()
{
	while (SDL_PollEvent(m_event))
	{
		switch (m_event->type)
		{
		case SDL_MOUSEBUTTONDOWN:
			if (!m_event->key.repeat)
			{
				switch (m_event->button.button)
				{
				case SDL_BUTTON_LEFT:
					m_eventListener->LeftClick = true;
					break;
				case SDL_BUTTON_RIGHT:
					m_eventListener->RightClick = true;
					break;

				default:
					break;
				}
				break;
			}

		case SDL_MOUSEBUTTONUP:
			if (!m_event->key.repeat)
			{
				switch (m_event->button.button)
				{
				case SDL_BUTTON_LEFT:
					m_eventListener->LeftClick = false;
					break;
				case SDL_BUTTON_RIGHT:
					m_eventListener->RightClick = false;
					break;

				default:
					break;
				}
				break;
			}

		case SDL_KEYDOWN:
			if (!m_event->key.repeat)
			{
				switch (m_event->key.keysym.sym)
				{
				case SDLK_w:
					m_eventListener->W = true;
					break;

				case SDLK_a:
					m_eventListener->A = true;
					break;

				case SDLK_s:
					m_eventListener->S = true;
					break;

				case SDLK_d:
					m_eventListener->D = true;
					break;

				case SDLK_SPACE:
					m_eventListener->Space = true;
					break;

				default:
					break;
				}
				break;
			}

		case SDL_KEYUP:
			if (!m_event->key.repeat)
			{
				switch (m_event->key.keysym.sym)
				{
				case SDLK_w:
					m_eventListener->W = false;
					break;

				case SDLK_a:
					m_eventListener->A = false;
					break;

				case SDLK_s:
					m_eventListener->S = false;
					break;

				case SDLK_d:
					m_eventListener->D = false;
					break;

				case SDLK_SPACE:
					m_eventListener->Space = false;
					break;

				default:
					break;
				}
				break;
			}
		}
	}
}
