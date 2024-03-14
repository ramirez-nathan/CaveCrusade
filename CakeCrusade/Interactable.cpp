#include "Interactable.hpp"
#include "GameState.hpp"
#include "SoundFx.hpp"

SoundFx itemSound;

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
	if (ItemName == "Chest") {
		Sprite.scale(sf::Vector2f(4.5, 4.5));
	}
	else if (ItemName != "Chest") {
		Sprite.scale(sf::Vector2f(3, 3));
	}
	// wrap the hitbox around the player
	BoundingRectangle.setSize(sf::Vector2f(Size.x * (Sprite.getScale().x - 1.2), Size.y * (Sprite.getScale().y - 1.2)));
	// set hitbox origin to middle
	BoundingRectangle.setOrigin(BoundingRectangle.getSize().x / 2.f, BoundingRectangle.getSize().y / 2.f + 25);
}

void Interactable::update(const double deltaTime, Player& player, vector<unique_ptr<Enemy>>& enemies, int level[], GameState& state)
{
	if (!state.ItemsReadyToSpawn) {
		if (state.ChestIsOpened) {
			state.ItemsReadyToSpawn = true;
		}
	}
	if (state.ItemsReadyToSpawn && ItemName != "Chest") {
		SpriteX = 0;
		if (!IsTouched) {
			if (Math::didRectCollide(player.getHitBox().getGlobalBounds(), BoundingRectangle.getGlobalBounds())) {
				IsTouched = true;
				if (ItemName == "Red Heart") {
					player.changeHalfHearts(2);
					cout << "You picked up a Red Heart! Your amount of half hearts is: " << player.getHalfHearts() << "Your amount of gold half hearts is : " << player.getGoldHalfHearts() << endl;
				}
				else if (ItemName == "Gold Heart") {
					player.changeGoldHalfHearts(2);
					cout << "You picked up a Gold Heart! Your amount of half hearts is: " << player.getHalfHearts() << "Your amount of gold half hearts is : " << player.getGoldHalfHearts() << endl;
				}
				else if (ItemName == "Key") {
					state.PlayerHasKey = true;
					cout << "You picked up a Key!" << endl;
				}
				else if (ItemName == "Bow") {
					player.setBowState(true);
					player.changeAmmo(10);
				}
			}
		}
	}
	if (ItemName == "Chest") {
		if (enemies.size() == 0 && !state.ChestIsOpened) {
			chestAnimation();
			if (ChestAnimationComplete) {
				state.ChestIsOpened = true;
			}
			SpriteX = ChestSpriteX;
		}
	}
	Sprite.setTextureRect(sf::IntRect(SpriteX * getSizeX(), SpriteY * getSizeY(), getSizeX(), getSizeY()));
	BoundingRectangle.setPosition(Sprite.getPosition());
}

void Interactable::chestAnimation() {
	ChestAnimationComplete = false;
	if (ChestClock.getElapsedTime().asSeconds() > 0.20) {
		if (ChestSpriteX == 4) {
			ChestAnimationComplete = true;
			itemSound.loadSound("sound/sounds/pickupItem.wav");
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

void Interactable::drawInteractable(sf::RenderWindow& window, GameState& state) {
	//cout << (ItemName == "Chest" && (state.CurrLevelName == "1c" || state.CurrLevelName == "2c" || state.CurrLevelName == "3c" || state.CurrLevelName == "4b" || state.CurrLevelName == "5a")) << endl;
	if (ItemName == "Chest" && (state.CurrLevelName == "1c" || state.CurrLevelName == "2c" || state.CurrLevelName == "3c" || state.CurrLevelName == "4b" || state.CurrLevelName == "5a")) {
		window.draw(Sprite);
	}
	else if (state.ItemsReadyToSpawn && !IsTouched && ItemName != "Chest" && (state.CurrLevelName == "1c" || state.CurrLevelName == "2c" || state.CurrLevelName == "3c" || state.CurrLevelName == "4b" || state.CurrLevelName == "5a")) {
		window.draw(Sprite);
		//window.draw(BoundingRectangle);
	}
}