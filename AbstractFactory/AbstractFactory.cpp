#include <iostream>
#include <vector>

using namespace std;

// ABSTRACT FACTORY
class Character {
public:
	Character() {}
	virtual ~Character() {}
	virtual void draw() = 0;
};



class Player : public Character {
public:
	void draw()
	{
		cout << "Draw Player" << endl;
	}
};

class Boss : public Character {
public:
	void draw()
	{
		cout << "Draw Boss" << endl;
	}
};



class Factory {
public:
	virtual Character* CreatePlayer() = 0;
	virtual Character* CreateOpponents() = 0;
};

class CharacterFactory : public Factory {
public:
	Character* CreatePlayer()
	{
		return new Player;
	}
	Character* CreateOpponents()
	{
		return new Boss;
	}

};

int main()
{
	Factory* factory = new CharacterFactory;
	vector<Character*> characters;
	characters.push_back(factory->CreatePlayer());
	characters.push_back(factory->CreateOpponents());

	for (int i = 0; i < characters.size(); i++)
	{
		characters[i]->draw();
	}

	system("PAUSE");
	return 0;
}