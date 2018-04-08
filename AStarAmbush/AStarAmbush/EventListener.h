#pragma once

#ifndef _EVENTLISTENER_H
#define _EVENTLISTENER_H

class EventListener
{
public:
	EventListener() {};
	// Keyboard Input
	bool W = false;
	bool A = false;
	bool S = false;
	bool D = false;
	bool Space = false;
	bool LeftClick = false;
	bool RightClick = false;

};
#endif
