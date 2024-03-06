#include <SFML/Graphics.hpp>
#include "TileMap.hpp"

bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
{
    int Scale = 4;

    // load the tileset texture
    if (!MapTileset.loadFromFile(tileset))
        return false;

    // resize the vertex array to fit the level size
    MapVertices.setPrimitiveType(sf::Quads);
    MapVertices.resize(width * height * 4);

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // get the current tile number
            int TileNumber = tiles[i + j * width];

            // find its position in the tileset texture
            int tu = TileNumber % (MapTileset.getSize().x / tileSize.x);
            int tv = TileNumber / (MapTileset.getSize().x / tileSize.x);

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &MapVertices[(i + j * width) * 4];

            // define its 4 corners with doubled size
            quad[0].position = sf::Vector2f(i * tileSize.x * Scale, j * tileSize.y * Scale);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x * Scale, j * tileSize.y * Scale);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x * Scale, (j + 1) * tileSize.y * Scale);
            quad[3].position = sf::Vector2f(i * tileSize.x * Scale, (j + 1) * tileSize.y * Scale);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);


        }

    return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &MapTileset;

    // draw the vertex array
    target.draw(MapVertices, states);
}