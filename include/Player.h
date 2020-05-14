#ifndef PLAYER_H
#define PLAYER_H

#include <camera.h>

class Player
{
	float posX;
	float posY;
	float posZ;
	Camera camera;
	
public:
	Player();
	Player(float _posX = 0, float _posY = 0, float _posZ = 0);
	~Player();
	void move();
};

#endif

