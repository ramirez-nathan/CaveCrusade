#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable {
public:
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::VertexArray MapVertices;
    sf::Texture MapTileset;

private:
    
};

#endif // TILEMAP_HPP
