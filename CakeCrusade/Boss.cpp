#include "Boss.hpp"
#include <iostream>

Boss::Boss(float h, float dmg, float def, float spd)
	:Enemy(h,dmg,def,spd) {}


void Boss::load() {
	//loadTexture("assets/enemies/gingerbread_boss.png"); //will be able to load this once we have the image decided on
	loadTexture("assets/enemies/Pink_Monster.png"); //image that will be changed later
	SpriteX = 0;
	SpriteY = 0;
	// change sprite scale
	Sprite.scale(sf::Vector2f(4, 4));
	// set origin at middle of sprite
	Sprite.setOrigin(Sprite.getLocalBounds().width / 2.f, Sprite.getLocalBounds().height / 2.f);
	// wrap the hitbox around the boss
	BoundingRectangle.setSize(sf::Vector2f(Size.y * Sprite.getScale().y, Size.x * Sprite.getScale().x));
	// set hitbox origin to middle
	BoundingRectangle.setOrigin(BoundingRectangle.getSize().x / 2.f, BoundingRectangle.getSize().y / 2.f);
}

void Boss::initialize() {
	BoundingRectangle.setFillColor(sf::Color::Transparent);
	BoundingRectangle.setOutlineColor(sf::Color::Red);
	BoundingRectangle.setOutlineThickness(1);

	Size = sf::Vector2i(32, 16);
}

void Boss::handleMovement(double deltaTime, sf::Vector2f& direction, int& spriteX, int& spriteY, int level[], vector<int>& walls) {
	sf::Vector2f Position = Sprite.getPosition();

	static double elapsedTime = 0.0;
	elapsedTime += deltaTime;
	
	if (elapsedTime >= 2000.0) {
		elapsedTime = 0.0;
		float posX = static_cast<float>(rand() % 1200);
		float posY = static_cast<float>(rand() % 500);

		sf::Vector2f NewPosition(posX, posY);


		int FuturePos = floor(NewPosition.y / 64) * 22 + floor(NewPosition.x / 64);
		if (!(std::find(walls.begin(), walls.end(), level[FuturePos]) != walls.end())) {
			Sprite.setPosition(NewPosition);
		}
	}
}





















/*
IM FREAKING OUT
LIKE INSANE AMOUNTS
COPIOUSLY
LIFE IS GR8
BUT ALSO SUCKS
LIKE BIG TIME
CRYING INTERNALLY
AND PROBABLY EXTERNALLY LATER
IM BREAKING
JUST LIKE MY CODE
.
.
.
...

ALL MY SUFFERING WILL BE OVER NEXT THURSDAY
NEXT SATURDAY IF I TAKE HIM UP ON THE MAKEUP QUIZ OFFER
WHAT IF I GET WORSE THAN 62.5% THO MAJOR OOF

IM HERE PHYSICALLY BUT MENTALLY IM ONLY IN CS MODE I KID U NOT
DID U KNOW THAT CTRL + "B" CAUSES A BUILD

IM LEARNING STUPID THINGS THAT DO NOT PLAY A BIG PART OF HOW MUCH I SHOULD BE UNDERSTANDING AT THIS POINT OF THE QUARTER

BUT THAT MEANS NOTHING IN TERMS OF THE PROJECT.AND I HATE TO SAY THIS BUT FOR THE GRADE IT DOES NOTHING. :(((

WOW HOW INSPIRATIONAL
BUT ARE YOU READY FOR THIS KICKER THAT MY PARTNER AND I DISCOVERED DURING DISCUSSION TODAY?!
drumrolllllllllll
0101010101010101010010101010011010010101010100101010

UNIT TESTING WHICH IS WORTH 20% OF THE GRADE FOR THE PROJECT HAS TO BE WRITTEN BY THE PERSON WHO WROTE THAT CLASS
WHICH MEANS THAT I GOTTA GET THIS BOSS CLASS DONE (WHICH MY TEAM ORIGINALLY WANTED TO SCRAP OUT DUE TO TIME CONCERN)
plus IM BEING DIRECTED TO TRY TO ADD ADDITIONAL MENU FUNCTIONS AS WELL (WHICH SHOCKER SHOCKER I HAVE LIKE NO EXPERIENCE ADDING THE UI SHIT ON HERE)\

SO LIKE THAT IS A GR8 IDEA BUT I DONT LIKE LYING. :(UGH) ANYWAYS MY MOTHER TAUGHT ME THAT HONESTY IS THE BEST POLICY. RAHHHHHH MY GOOD UPBRINGING IS BITING ME HERE


OHHHH YEAH THATS SUPER EASY ON HERE
I JUST HAVE TO CLICK ON 

I APPRECIATE THE SUPPORT AND ENTHUSIASM! WE LOVE THE ENERGY. CUZ I BE SLACKING AND LACKING IN THAT DEPARTMENT RECENTLY.
I LITERALLY HAVE NO IDEA WHAT IS GOING ON IN THIS CLASS RN
WHY IS HE TALKING ABT BUTTERFLIES IN HAWAII
LIKE WHAT
IDEK 
I CONCERNED


do you want me to show u what the peoples have done so far?
okie dokies*/
