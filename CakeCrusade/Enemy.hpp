#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.hpp"

class Enemy : public Entity {
public:
	Enemy(float h, float d, float def);
	virtual void attackMove() override;
	void getKnockedBack();
	void target();
};