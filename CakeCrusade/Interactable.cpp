#include "Interactable.hpp"

Interactable::Interactable(string name)
	: ItemName(name)
{
}

void Interactable::initialize()
{
	BoundingRectangle.setFillColor(sf::Color::Transparent);
	BoundingRectangle.setOutlineColor(sf::Color::Yellow);
	BoundingRectangle.setOutlineThickness(1);
	if (ItemName == "Red Heart") {
		TexturePath = "assets/Objects/heart.png";
		Size = sf::Vector2i(16, 16);
	}
	else if (ItemName == "Gold Heart") {
		TexturePath = "assets/Objects/extra_heart.png";
		Size = sf::Vector2i(16, 16);
	}
	else if (ItemName == "Chest") {
		TexturePath = "assets/Tileset/chest.png";
		Size = sf::Vector2i(16, 32);
	}
	else if (ItemName == "Key") {
		TexturePath = "assets/Objects/key.png";
		Size = sf::Vector2i(16, 16);
	}
	else if (ItemName == "Bow") {
		TexturePath = "assets/Objects/bow.png";
		Size = sf::Vector2i(16, 16);
	}
}

void Interactable::load()
{
	if (!Texture.loadFromFile(TexturePath)) {
		std::cerr << "Failed to load texture from " << TexturePath << std::endl;
	}
	Sprite.setTexture(Texture);
	// grab the idle texture image from spritesheet
	Sprite.setTextureRect(sf::IntRect(SpriteX * getSizeX(), SpriteY * getSizeY(), getSizeX(), getSizeY()));
	// set origin at middle of sprite
	Sprite.setOrigin(Sprite.getLocalBounds().width / 2.f, Sprite.getLocalBounds().height / 2.f + 7);
	// change sprite scale
	Sprite.scale(sf::Vector2f(3, 3));
	// wrap the hitbox around the player
	BoundingRectangle.setSize(sf::Vector2f(Size.x * (Sprite.getScale().x - 1.2), Size.y * (Sprite.getScale().y - 1.2)));
	// set hitbox origin to middle
	BoundingRectangle.setOrigin(BoundingRectangle.getSize().x / 2.f, BoundingRectangle.getSize().y / 2.f + 13);
}

void Interactable::update(const double deltaTime, Player& player, vector<unique_ptr<Enemy>>& enemies, int level[])
{
	if (!ReadyToSpawn) {
		if (ChestIsOpened) {
			ReadyToSpawn = true;
		}
	}
	if (ReadyToSpawn) {
		if (!IsTouched) {
			if (Math::didRectCollide(player.getHitBox().getGlobalBounds(), BoundingRectangle.getGlobalBounds()) && ItemName != "Chest") {
				IsTouched = true;
				if (ItemName == "Red Heart") {
					player.changeHalfHearts(2);
				}
				else if (ItemName == "Gold Heart") {
					player.changeGoldHalfHearts(2);
				}
				else if (ItemName == "Key") {
					player.setKeyState(true);
				}
				else if (ItemName == "Bow") {
					player.setBowState(true);
					player.changeAmmo(10);
				}
			}
		}
		else if (ItemName == "Chest") {
			if (enemies.size() == 0) {
				chestAnimation();
				if (ChestAnimationComplete) {
					ChestIsOpened = true;
				}
			}
			SpriteX = ChestSpriteX;
		}
	}
	BoundingRectangle.setPosition(Sprite.getPosition());
}

void Interactable::chestAnimation() {
	if (ChestClock.getElapsedTime().asSeconds() > 0.20) {
		if (ChestSpriteX == 4) {
			ChestAnimationComplete = true;
		}
		else {
			ChestSpriteX++;
		}
		ChestClock.restart();
	}
}

bool Interactable::isTouched() {
	if (ItemName == "Chest") {
		return false;
	}
	else {
		if (IsTouched == true) {
			return true;
		}
	}
}

void Interactable::drawInteractable(sf::RenderWindow& window, string currLevelName) {
	if (ItemName == "Chest" && currLevelName == "1c" || currLevelName == "2c" || currLevelName == "3c" || currLevelName == "4b" || currLevelName == "5a") {
		window.draw(Sprite);
	}
	if (ReadyToSpawn && !IsTouched) {
		window.draw(Sprite);
		window.draw(BoundingRectangle);
	}
}