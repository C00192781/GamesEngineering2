#pragma once
#include <iostream>

// Receiver - performs the requests
class Receiver
{

public:
	void Action(std::string action);

private:
	void Fire();
	void Jump();
	
};
