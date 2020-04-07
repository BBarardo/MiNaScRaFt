#include "Player.h"


Player::Player(float _posX, float _posY, float _posZ):camera(Camera(glm::vec3(0.0f, 2.0f, 0.0f)))
{
	posX = _posX;
	posY = _posY;
	posZ = _posZ;
}

Player::~Player()
{
	
}

void Player::move()
{
	
}
