#pragma once

// COMPONENT

#include "Component.h"

class ControlComponent : public Component
{
private:
	bool keyPressed;

public:
	ControlComponent() : keyPressed(false) {};

	bool getKeyPressed() { return keyPressed; }
	void setKeyPressed(bool isPressed) { keyPressed = isPressed; }

};