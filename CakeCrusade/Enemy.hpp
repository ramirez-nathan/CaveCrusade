#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.hpp"

class Enemy : public Entity {
private:


public:
	void getKnockedBack();
	virtual void target() = 0;
};